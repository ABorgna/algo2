
#ifndef TRIE_INCLUDED_H
#define TRIE_INCLUDED_H

#include <assert.h>

#include "../aed2.h"

namespace tp3 {

    template<class T>
    class DiccTrie {
        private:
            struct Nodo;

        public:
            struct ClaveValor;
            class Iterador;

            DiccTrie();

            void definir(const std::string& k, const T& v);
            bool definido(const std::string& k) const;

            const T& obtener(const std::string& k) const;
            T& obtener(const std::string& k);

            void borrar(const std::string& k);

            DiccTrie<T>::ClaveValor maximo();
            DiccTrie<T>::ClaveValor minimo();

            struct ClaveValor {
                const std::string& clave;
                const T& significado;

                ClaveValor(const std::string& c, const T& s) :
                    clave(c), significado(s) {};
            };

        private:

            struct Nodo {
                T valor;
                Nodo* hijos[256];
            };

            Nodo* raiz_;
            ClaveValor minimo_;
            ClaveValor maximo_;

    };

}

#endif //TRIE_INCLUDED_H
