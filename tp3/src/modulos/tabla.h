
#ifndef TABLA_INCLUDED_H
#define TABLA_INCLUDED_H

#include <assert.h>

#include "../aed2.h"

#include "dato.h"
#include "diccLog.h"
#include "diccTrie.h"

namespace tp3 {

    typedef std::string NombreTabla;
    typedef aed2::Conj<Registro>::Iterador itRegistros;
    typedef aed2::Conj<Registro>::const_Iterador itRegistrosConst;

    class Tabla {
        private:

            aed2::Conj<Registro> registros_;

            bool hayIndiceNat_;
            Campo indiceNat_;
            DiccLog<unsigned int, aed2::Conj<itRegistros> > indicesNat_;

            bool hayIndiceString_;
            Campo indiceString_;
            DiccTrie<aed2::Conj<itRegistros> > indicesString_;

            const NombreTabla nombre_;
            const Registro campos_;
            const aed2::Conj<Campo> claves_;

            unsigned int accesos_;

        public:
            Tabla(const std::string& nombre,
                  const aed2::Conj<Campo>& claves,
                  const Registro& columnas);

            void agregarRegistro(const Registro&);
            aed2::Conj<Registro> borrarRegistro(const Registro&);
            void indexar(const Campo&);

            const NombreTabla nombre() const;
            bool esClave(const Campo&) const;
            bool esIndice(const Campo&) const;

            itRegistrosConst registros() const;
            const Registro campos() const;
            bool tipoCampo(const Campo&) const;

            unsigned int accesos() const;
            unsigned int maxNat() const;
            unsigned int minNat() const;
            std::string maxString() const;
            std::string minString() const;

            const aed2::Conj<Registro> buscar(const Registro&) const;

            unsigned int cantidadRegistros() const;
    };

}

#endif //TABLA_INCLUDED_H
