
#ifndef AVL_INCLUDED_H
#define AVL_INCLUDED_H

#include <assert.h>

#include "../aed2.h"

namespace tp3 {

    template<class K, class T>
    class DiccLog {
        public:

            struct ClaveValor {
                const K& clave;
                const T& significado;

                ClaveValor(const K& c, const T& s) :
                    clave(c), significado(s) {};
            };

            DiccLog();

            void definir(const K& k, const T& v);
            bool definido(const K& k) const;

            const T& obtener(const K& k) const;
            T& obtener(const K& k);

            void borrar(const K& k);

            DiccLog<K,T>::ClaveValor maximo();
            DiccLog<K,T>::ClaveValor minimo();

        private:

            struct Nodo {
                K clave;
                T valor;

                Nodo* menor;
                Nodo* mayor;
                Nodo* padre;

                unsigned int fdb;
            };

            Nodo* raiz_;
            Nodo* minimo_;
            Nodo* maximo_;

    };

}

#endif //AVL_INCLUDED_H
