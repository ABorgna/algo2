
#ifndef DB_INCLUDED_H
#define DB_INCLUDED_H

#include <assert.h>

#include "../aed2.h"

#include "dato.h"
#include "diccLog.h"
#include "diccTrie.h"
#include "tabla.h"

namespace tp3 {

    typedef aed2::Conj<Tabla>::Iterador itTablas;
    typedef aed2::Conj<Tabla>::const_Iterador itTablasConst;

    class DB {
        public:
            DB();

            void agregarTabla(Tabla&);

            void insertarEntrada(const NombreTabla&, const Registro&);
            void borrar(const NombreTabla&, const Campo&, const Dato&);

            bool hayTabla(const NombreTabla&) const;
            const Tabla& tabla(const NombreTabla&) const;
            itTablasConst tablas(const NombreTabla&) const;
            const Tabla& tablaMaxima() const;

            itRegistrosConst generarVistaJoin(const NombreTabla&,
                                              const NombreTabla&,
                                              const Campo&);
            bool hayJoin(const NombreTabla&, const NombreTabla&) const;
            Campo campoJoin(const NombreTabla&, const NombreTabla&) const;
            void borrarJoin(const NombreTabla&, const NombreTabla&);
            itRegistrosConst vistaJoin(const NombreTabla&, const NombreTabla&);

            aed2::Conj<Registro> buscar(const NombreTabla&, const Registro&);

        private:

            typedef struct OperacionJoin_t {
                bool esInsercion;
                bool enTablaB;
                Registro reg;
            } OperacionJoin;

            typedef struct VistaJoin_t {
                Campo campo;
                bool tipo;
                aed2::Lista<OperacionJoin> buffer;

                aed2::Conj<Registro> joins;
                DiccLog<unsigned int, itRegistros> joinsNat;
                DiccTrie<itRegistros> joinsString;

            } VistaJoin;

            aed2::Conj<Tabla> tablas_;
            DiccTrie<itTablas> tablasTree_;

            DiccTrie<DiccTrie<VistaJoin> > vistasJoin_;

            itTablas tablaMaxima_;
    };

}

#endif //DB_INCLUDED_H
