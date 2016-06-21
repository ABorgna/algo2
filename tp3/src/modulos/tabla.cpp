#include "tabla.h"

using namespace tp3;

Tabla::Tabla(const std::string& nombre,
             const aed2::Conj<Campo>& claves,
             const Registro& columnas) :
        hayIndiceNat_(false),
        hayIndiceString_(false),
        nombre_(nombre),
        campos_(columnas),
        claves_(claves),
        accesos_(0) {

    assert(columnas.CantClaves() > 0);
    assert(claves.Cardinal() > 0);
}

void Tabla::agregarRegistro(const Registro& r) {
    itRegistros it = registros_.AgregarRapido(r);

    if(hayIndiceNat_) {
        assert(r.Definido(indiceNat_));
        assert(r.Significado(indiceNat_).isNat());

        unsigned int k = r.Significado(indiceNat_).getNat();

        assert(!esClave(indiceNat_) or !indicesNat_.definido(k));

        if(!indicesNat_.definido(k)) {
            indicesNat_.definir(k, aed2::Conj<itRegistros>());
        }

        indicesNat_.obtener(k).AgregarRapido(it);
    }

    if(hayIndiceString_) {
        assert(r.Definido(indiceString_));
        assert(r.Significado(indiceString_).isString());

        const std::string& k = r.Significado(indiceString_).getString();

        assert(!esClave(indiceString_) or !indicesString_.definido(k));

        if(!indicesString_.definido(k)) {
            indicesString_.definir(k, aed2::Conj<itRegistros>());
        }

        indicesString_.obtener(k).AgregarRapido(it);
    }

    accesos_++;
}

aed2::Conj<Registro> Tabla::borrarRegistro(const Campo& c, const Dato& d) {
    assert(esClave(c));
    assert(d.isNat() == tipoCampo(c));

    aed2::Conj<Registro> res;
    bool esta = false;
    itRegistros it;

    // Buscar
    if(hayIndiceNat_ and indiceNat_ == c) {
        if(indicesNat_.definido(d.getNat())) {
            const aed2::Conj<itRegistros>& its = indicesNat_.obtener(d.getNat());
            it = its.CrearIt().Siguiente();
            esta = true;
        }
    } else if(hayIndiceString_ and indiceString_ == c) {
        if(indicesString_.definido(d.getString())) {
            const aed2::Conj<itRegistros>& its = indicesString_.obtener(d.getString());
            it = its.CrearIt().Siguiente();
            esta = true;
        }
    } else {
        it = registros_.CrearIt();
        while(it.HaySiguiente() and it.Siguiente().Significado(c) != d) {
            it.Avanzar();
        }
        if(it.HaySiguiente()) {
            esta = true;
        }
    }

    // Borrar
    if(esta) {
        Registro r = it.Siguiente();
        res.AgregarRapido(r);

        // Borrar la entrada como índice nat
        if(hayIndiceNat_) {
            unsigned int k = r.Significado(indiceNat_).getNat();

            if(esClave(indiceNat_)) {
                indicesNat_.borrar(k);
            } else {
                // Buscar el registro en el conjunto
                const Campo& clave = claves_.CrearIt().Siguiente();

                aed2::Conj<itRegistros>::Iterador itIndex;
                itIndex = indicesNat_.obtener(k).CrearIt();

                while(itIndex.HaySiguiente()) {
                    const Dato& datoClave =
                        itIndex.Siguiente().Siguiente().Significado(clave);

                    if(datoClave == r.Significado(clave)) {
                        itIndex.EliminarSiguiente();
                        break;
                    }

                    itIndex.Avanzar();
                }
            }
        }

        // Borrar la entrada como índice string
        if(hayIndiceString_) {
            const std::string& k = r.Significado(indiceString_).getString();

            if(esClave(indiceString_)) {
                indicesString_.borrar(k);
            } else {
                // Buscar el registro en el conjunto
                const Campo& clave = claves_.CrearIt().Siguiente();

                aed2::Conj<itRegistros>::Iterador itIndex;
                itIndex = indicesString_.obtener(k).CrearIt();

                while(itIndex.HaySiguiente()) {
                    const Dato& datoClave =
                        itIndex.Siguiente().Siguiente().Significado(clave);

                    if(datoClave == r.Significado(clave)) {
                        itIndex.EliminarSiguiente();
                        break;
                    }

                    itIndex.Avanzar();
                }
            }
        }

        it.EliminarSiguiente();

        accesos_++;
    }

    return res;
}

void Tabla::indexar(const Campo& c) {
    assert(campos_.Definido(c));
    itRegistros it = registros_.CrearIt();

    if(tipoCampo(c)) {
        assert(!hayIndiceNat_);

        indiceNat_ = c;
        hayIndiceNat_ = true;

        while(it.HaySiguiente()) {
            unsigned int k = it.Siguiente().Significado(c).getNat();

            if(!indicesNat_.definido(k)) {
                indicesNat_.definir(k, aed2::Conj<itRegistros>());
            }

            indicesNat_.obtener(k).AgregarRapido(it);

            it.Avanzar();
        }

    } else {
        assert(!hayIndiceString_);

        indiceString_ = c;
        hayIndiceString_ = true;

        while(it.HaySiguiente()) {
            const std::string& k = it.Siguiente().Significado(c).getString();

            if(!indicesString_.definido(k)) {
                indicesString_.definir(k, aed2::Conj<itRegistros>());
            }

            indicesString_.obtener(k).AgregarRapido(it);

            it.Avanzar();
        }
    }
}

const NombreTabla Tabla::nombre() const {
    return nombre_;
}

bool Tabla::esClave(const Campo& c) const {
    assert(campos_.Definido(c));
    return claves_.Pertenece(c);
}

bool Tabla::esIndice(const Campo& c) const {
    assert(campos_.Definido(c));

    if(tipoCampo(c)) {
        return hayIndiceNat_ and indiceNat_ == c;
    } else {
        return hayIndiceString_ and indiceString_ == c;
    }
}

itRegistrosConst Tabla::registros() const {
    return registros_.CrearIt();
}

const Registro Tabla::campos() const {
    return campos_;
}

bool Tabla::tipoCampo(const Campo& c) const {
    assert(campos_.Definido(c));
    return campos_.Significado(c).isNat();
}

unsigned int Tabla::accesos() const {
    return accesos_;
}

unsigned int Tabla::maxNat() const {
    return indicesNat_.maximo().clave;
}

unsigned int Tabla::minNat() const {
    return indicesNat_.minimo().clave;
}

std::string Tabla::maxString() const {
    return indicesString_.maximo().clave;
}

std::string Tabla::minString() const {
    return indicesString_.minimo().clave;
}

const aed2::Conj<Registro> Tabla::buscar(const Registro& crit) const {
    aed2::Conj<Registro> res;

    if(hayIndiceString_ and crit.Definido(indiceString_) and esClave(indiceString_)) {
        const Campo& c = indiceString_;
        const std::string& k = crit.Significado(c).getString();

        if(indicesString_.definido(k)) {
            const Registro& r = indicesString_.obtener(k).CrearIt().Siguiente().Siguiente();
            Registro::const_Iterador it = crit.CrearIt();
            bool igual = true;

            while(it.HaySiguiente()) {
                const Campo& c = it.SiguienteClave();
                if(r.Definido(c)) {
                    igual &= it.SiguienteSignificado() == r.Significado(c);
                }
                it.Avanzar();
            }
            if(igual) {
                res.AgregarRapido(r);
            }
        }
    } else if(hayIndiceNat_ and crit.Definido(indiceNat_) and esClave(indiceNat_)) {
        const Campo& c = indiceNat_;
        unsigned int k = crit.Significado(c).getNat();

        if(indicesNat_.definido(k)) {
            const Registro& r = indicesNat_.obtener(k).CrearIt().Siguiente().Siguiente();
            Registro::const_Iterador it = crit.CrearIt();
            bool igual = true;

            while(it.HaySiguiente()) {
                const Campo& c = it.SiguienteClave();
                if(r.Definido(c)) {
                    igual &= it.SiguienteSignificado() == r.Significado(c);
                }
                it.Avanzar();
            }
            if(igual) {
                res.AgregarRapido(r);
            }
        }
    } else {
        // Busqueda lineal sobre los registros
        itRegistrosConst it = registros_.CrearIt();

        while(it.HaySiguiente()) {
            const Registro& r = it.Siguiente();
            Registro::const_Iterador itReg = crit.CrearIt();
            bool igual = true;

            while(it.HaySiguiente()) {
                const Campo& c = itReg.SiguienteClave();
                if(r.Definido(c)) {
                    igual &= itReg.SiguienteSignificado() == r.Significado(c);
                }
                it.Avanzar();
            }
            if(igual) {
                res.AgregarRapido(r);
            }

            it.Avanzar();
        }
    }

    return res;
}

unsigned int Tabla::cantidadRegistros() const {
    return registros_.Cardinal();
}

