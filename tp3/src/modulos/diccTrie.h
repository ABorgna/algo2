
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
            ~DiccTrie();

            void definir(const std::string& k, const T& v);
            bool definido(const std::string& k) const;

            const T& obtener(const std::string& k) const;
            T& obtener(const std::string& k);

            void borrar(const std::string& k);

            DiccTrie<T>::ClaveValor maximo() const;
            DiccTrie<T>::ClaveValor minimo() const;

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
                bool esta;
            };

            Nodo* raiz_;
            ClaveValor minimo_;
            ClaveValor maximo_;

            /* Funciones auxiliares */
            Nodo& crearNodo() const;
            bool tieneHijos(const Nodo&) const;
            unsigned int menorHijo(const Nodo&) const;
            unsigned int mayorHijo(const Nodo&) const;
    };

    /****************************
     * Implementación
     ****************************/

    template<class T>
    DiccTrie<T>::DiccTrie() :
        raiz_(NULL) {}

    template<class T>
    void DiccTrie<T>::definir(const std::string& k, const T& v){
        unsigned int i=0;
        Nodo* prox;
        Nodo nodo;
        bool eraVacio = false;

        if(raiz_ == NULL) {
            nodo = crearNodo();
            raiz_ = &nodo;
            eraVacio = true;
        }

        prox = raiz_;

        while(i < k.length()) {
            if(prox->hijos[k[i]] == NULL) {
                nodo = crearNodo();
                prox->hijos[k[i]] = &nodo;
            }
            prox = prox->hijos[k[i]];
            i++;
        }

        // No tiene que estar definido
        assert(prox->valor == NULL);

        prox->valor = v;
        prox->esta = true;

        if(eraVacio or k < minimo_.clave) {
            minimo_.clave = k;
            minimo_.significado = v;
        }
        if(eraVacio or k > maximo_.clave) {
            maximo_.clave = k;
            maximo_.significado = v;
        }
    }

    template<class T>
    bool DiccTrie<T>::definido(const std::string& k) const {
        unsigned int i=0;
        Nodo* prox;

        if(raiz_ == NULL) {
            return false;
        } else {
            prox = raiz_;

            while(i < k.length()) {
                if(prox->hijos[k[i]] == NULL){
                    prox = prox->hijos[k[i]];
                } else {
                    return false;
                }
                i++;
            }
            return prox->esta;
        }
    }

    template<class T>
    const T& DiccTrie<T>::obtener(const std::string& k) const {
        // Tiene que estar definido
        assert(definido(k));

        unsigned int i = 0;
        Nodo* prox = raiz_;

        while(i < k.length()) {
            prox = prox->hijos[k[i]];
            i++;
        }

        return prox->v;
    }

    template<class T>
    T& DiccTrie<T>::obtener(const std::string& k) {
        // Tiene que estar definido
        assert(definido(k));

        unsigned int i = 0;
        Nodo* prox = raiz_;

        while(i < k.length()) {
            prox = prox->hijos[k[i]];
            i++;
        }

        return prox->v;
    }

    template<class T>
    void DiccTrie<T>::borrar(const std::string& k) {
        // Tiene que estar definido
        assert(definido(k));

        struct Paso {
            Nodo* nodo;
            char siguiente;
        };

        unsigned int i = 0;
        Nodo* prox;
        aed2::Lista<Paso> camino;

        while(i < k.length() ) {
            camino.AgregarAdelante(Paso (prox, k[i]));
            prox = prox->hijos[k[i]];
            i++;
        }

        prox->esta = false;
        while(camino.Cardinal() and !tieneHijos(*prox)) {
            Paso paso = camino.Primero();
            camino.Fin();

            free(prox);
            prox = paso.nodo;
            prox->hijos[paso.siguiente] = NULL;
        }

        // TODO: falta un cacho
    }

    template<class T>
    struct DiccTrie<T>::ClaveValor DiccTrie<T>::maximo() const {
    }

    template<class T>
    struct DiccTrie<T>::ClaveValor DiccTrie<T>::minimo() const {
    }

    /****************************
     * Auxiliares
     ****************************/

    template<class T>
    struct DiccTrie<T>::Nodo& DiccTrie<T>::crearNodo() const {
    }

    template<class T>
    bool DiccTrie<T>::tieneHijos(const Nodo&) const {
    }

    template<class T>
    unsigned int DiccTrie<T>::menorHijo(const Nodo&) const {
    }

    template<class T>
    unsigned int DiccTrie<T>::mayorHijo(const Nodo&) const {
    }
}

#endif //TRIE_INCLUDED_H
