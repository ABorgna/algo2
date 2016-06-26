#include "db.h"

using namespace tp3;

DB::DB() {
}

void DB::agregarTabla(const Tabla& t) {
    NombreTabla nt = t.nombre();
    assert(!tablasTree_.definido(nt));
    itTablas it = tablas_.AgregarAtras(t);

    tablasTree_.definir(nt, it);

    if(tablas_.Longitud() == 1) {
        tablaMaxima_ = it;
    }
}

void DB::insertarEntrada(const NombreTabla& nt, const Registro& r) {
    assert(hayTabla(nt));
    Tabla& t = tabla(nt);

    // Insertar
    t.agregarRegistro(r);

    // Mantener la tabla maxima
    if(t.accesos() > tablaMaxima_.Siguiente().accesos()) {
        tablaMaxima_ = tablasTree_.obtener(nt);
    }

    // Agregar la operación a todos los joins
    itTablas it = tablas_.CrearIt();
    while(it.HaySiguiente()) {
        const Tabla& t2 = it.Siguiente();

        if(t2.nombre() != nt) {
            if(vistasJoin_.definido(nt)) {
                if(vistasJoin_.obtener(nt).definido(t2.nombre())) {
                    VistaJoin& v = vistasJoin_.obtener(nt).obtener(t2.nombre());
                    OperacionJoin op = {true, false, r};

                    v.buffer.AgregarAtras(op);
                }
            }

            if(vistasJoin_.definido(t2.nombre())) {
                if(vistasJoin_.obtener(t2.nombre()).definido(nt)) {
                    VistaJoin& v = vistasJoin_.obtener(t2.nombre()).obtener(nt);
                    OperacionJoin op = {true, true, r};

                    v.buffer.AgregarAtras(op);
                }
            }
        }

        it.Avanzar();
    }
}

void DB::borrar(const NombreTabla& nt, const Campo& c, const Dato& d) {
    assert(hayTabla(nt));
    Tabla& t = tabla(nt);
    aed2::Conj<Registro> rs;

    // Insertar
    rs = t.borrarRegistro(c,d);

    if(!rs.EsVacio()) {
        const Registro& r = rs.CrearIt().Siguiente();

        // Mantener la tabla maxima
        if(t.accesos() > tablaMaxima_.Siguiente().accesos()) {
            tablaMaxima_ = tablasTree_.obtener(nt);
        }

        // Agregar la operación a todos los joins
        itTablas it = tablas_.CrearIt();
        while(it.HaySiguiente()) {
            const Tabla& t2 = it.Siguiente();

            if(t2.nombre() != nt) {
                if(vistasJoin_.definido(nt)) {
                    if(vistasJoin_.obtener(nt).definido(t2.nombre())) {
                        VistaJoin& v =
                            vistasJoin_.obtener(nt).obtener(t2.nombre());
                        OperacionJoin op = {false, false, r};

                        v.buffer.AgregarAtras(op);
                    }
                }

                if(vistasJoin_.definido(t2.nombre())) {
                    if(vistasJoin_.obtener(t2.nombre()).definido(nt)) {
                        VistaJoin& v =
                            vistasJoin_.obtener(t2.nombre()).obtener(nt);
                        OperacionJoin op = {false, true, r};

                        v.buffer.AgregarAtras(op);
                    }
                }
            }

            it.Avanzar();
        }
    }
}

bool DB::hayTabla(const NombreTabla& nt) const {
    return tablasTree_.definido(nt);
}

const Tabla& DB::tabla(const NombreTabla& nt) const {
    assert(hayTabla(nt));
    return tablasTree_.obtener(nt).Siguiente();
}

Tabla& DB::tabla(const NombreTabla& nt) {
    assert(hayTabla(nt));
    return tablasTree_.obtener(nt).Siguiente();
}

itTablasConst DB::tablas() const {
    return tablas_.CrearIt();
}

const Tabla& DB::tablaMaxima() const {
    return tablaMaxima_.Siguiente();
}

itRegistrosConst DB::generarVistaJoin(const NombreTabla& nt1,
                                  const NombreTabla& nt2,
                                  const Campo& c) {
    assert(nt1 != nt2);
    assert(hayTabla(nt1));
    assert(hayTabla(nt2));
    assert(!hayJoin(nt1,nt2));

    const Tabla& t1 = tabla(nt1);
    const Tabla& t2 = tabla(nt2);
    bool recorreTabla1;

    assert(t1.campos().definido(c));
    assert(t2.campos().definido(c));
    assert(t1.esClave(c));
    assert(t2.esClave(c));

    const Tabla* tRecorro;
    const Tabla* tBusco;

    // Decidir que tabla recorrer y en cual buscar
    if(t1.esIndice(c) && t2.esIndice(c)) {
        if(t1.cantidadRegistros() < t2.cantidadRegistros()) {
            recorreTabla1 = true;
            tRecorro = &t1;
            tBusco = &t2;
        } else {
            recorreTabla1 = false;
            tRecorro = &t2;
            tBusco = &t1;
        }
    } else if(t1.esIndice(c)) {
        recorreTabla1 = true;
        tRecorro = &t1;
        tBusco = &t2;
    } else {
        recorreTabla1 = false;
        tRecorro = &t2;
        tBusco = &t1;
    }

    // Crear el join
    if(!vistasJoin_.definido(nt1)) {
        vistasJoin_.definir(nt1, DiccTrie<VistaJoin>());
    }
    vistasJoin_.obtener(nt1).definir(nt2, VistaJoin());
    VistaJoin& v = vistasJoin_.obtener(nt1).obtener(nt2);

    v.campo = c;
    v.tipo = t1.tipoCampo(c);

    // Popular el join recorriendo una tabla
    // y buscando los valores correspondientes en la otra
    itRegistrosConst it = tRecorro->registros();

    while(it.HaySiguiente()) {
        const Registro& rA = it.Siguiente();
        const Dato& d = rA.obtener(c);

        Registro crit;
        crit.definir(c,d);
        aed2::Conj<Registro> rs = tBusco->buscar(crit);

        // c es clave, por lo que rs tiene a lo sumo un elemento
        if(!rs.EsVacio()) {
            const Registro& rB = rs.CrearIt().Siguiente();
            Registro r;

            // Los valores de t1 pisan a los de t2
            if(recorreTabla1) {
                r = combinarRegistros(rA,rB);
            } else {
                r = combinarRegistros(rB,rA);
            }

            itRegistros itReg = v.joins.AgregarRapido(r);

            if(v.tipo) {
                v.joinsNat.definir(d.getNat(), itReg);
            } else {
                v.joinsString.definir(d.getString(), itReg);
            }
        }

        it.Avanzar();
    }

    return v.joins.CrearIt();
}

bool DB::hayJoin(const NombreTabla& nt1, const NombreTabla& nt2) const {
    return vistasJoin_.definido(nt1) and
           vistasJoin_.obtener(nt1).definido(nt2);
}

const Campo& DB::campoJoin(const NombreTabla& nt1, const NombreTabla& nt2) const {
    assert(hayJoin(nt1,nt2));
    return vistasJoin_.obtener(nt1).obtener(nt2).campo;
}

void DB::borrarJoin(const NombreTabla& nt1, const NombreTabla& nt2) {
    assert(hayJoin(nt1,nt2));

    vistasJoin_.obtener(nt1).borrar(nt2);
    if(vistasJoin_.obtener(nt1).vacio()) {
        vistasJoin_.borrar(nt1);
    }
}

itRegistrosConst DB::vistaJoin(const NombreTabla& nt1, const NombreTabla& nt2) {
    assert(hayJoin(nt1,nt2));

    VistaJoin& v = vistasJoin_.obtener(nt1).obtener(nt2);
    const Tabla& t1 = tabla(nt1);
    const Tabla& t2 = tabla(nt2);

    aed2::Lista<OperacionJoin>::const_Iterador it = v.buffer.CrearIt();
    while(it.HaySiguiente()) {
        const OperacionJoin& op = it.Siguiente();
        const Dato& d = op.reg.obtener(v.campo);

        if(op.esInsercion) {
            aed2::Conj<Registro> rs;

            Registro crit;
            crit.definir(v.campo,d);
            if(!op.enTablaB) {
                rs = t2.buscar(crit);
            } else {
                rs = t1.buscar(crit);
            }

            if(!rs.EsVacio()) {
                const Registro& rB = rs.CrearIt().Siguiente();
                Registro r;

                // Los valores de t1 pisan a los de t2
                if(!op.enTablaB) {
                    r = combinarRegistros(op.reg,rB);
                } else {
                    r = combinarRegistros(rB,op.reg);
                }

                itRegistros itReg = v.joins.AgregarRapido(r);

                if(v.tipo) {
                    v.joinsNat.definir(d.getNat(), itReg);
                } else {
                    v.joinsString.definir(d.getString(), itReg);
                }
            }
        } else {
            if(v.tipo) {
                unsigned int k = d.getNat();
                if(v.joinsNat.definido(k)){
                    v.joinsNat.obtener(k).EliminarSiguiente();
                    v.joinsNat.borrar(k);
                }
            } else {
                const std::string& k = d.getString();
                if(v.joinsString.definido(k)){
                    v.joinsString.obtener(k).EliminarSiguiente();
                    v.joinsString.borrar(k);
                }
            }
        }

        it.Avanzar();
    }
    v.buffer = aed2::Lista<OperacionJoin>();

    return v.joins.CrearIt();
}

aed2::Conj<Registro> DB::buscar(const NombreTabla& nt, const Registro& r) const {
    assert(hayTabla(nt));
    const Tabla& t = tabla(nt);
    return t.buscar(r);
}

/***************************************
 * Funciones auxiliares
 ***************************************/

Registro DB::combinarRegistros(const Registro& r1, const Registro& r2) {
    Registro res;
    Registro::const_Iterador it;

    it = r2.CrearIt();
    while(it.hayMas()) {
        const Campo& c = it.actual().clave;
        const Dato& d = it.actual().significado;

        res.definir(c,d);

        it.avanzar();
    }

    it = r1.CrearIt();
    while(it.hayMas()) {
        const Campo& c = it.actual().clave;
        Dato d = it.actual().significado;

        res.definir(c,d);

        it.avanzar();
    }

    return res;
}

