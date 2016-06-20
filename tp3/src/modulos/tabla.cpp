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

void Tabla::indexar(const Campo&) {
    // TODO
    assert(false);
}

const NombreTabla Tabla::nombre() const {
    // TODO
    assert(false);
}

bool Tabla::esClave(const Campo&) const {
    // TODO
    assert(false);
}

bool Tabla::esIndice(const Campo&) const {
    // TODO
    assert(false);
}

itRegistrosConst Tabla::registros() const {
    // TODO
    assert(false);
}

const Registro Tabla::campos() const {
    // TODO
    assert(false);
}

bool Tabla::tipoCampo(const Campo&) const {
    // TODO
    assert(false);
}

unsigned int Tabla::accesos() const {
    // TODO
    assert(false);
}

unsigned int Tabla::maxNat() const {
    // TODO
    assert(false);
}

unsigned int Tabla::minNat() const {
    // TODO
    assert(false);
}

std::string Tabla::maxString() const {
    // TODO
    assert(false);
}

std::string Tabla::minString() const {
    // TODO
    assert(false);
}

const aed2::Conj<Registro> Tabla::buscar(const Registro&) const {
    // TODO
    assert(false);
}

unsigned int Tabla::cantidadRegistros() const {
    // TODO
    assert(false);
}

