
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
                std::string clave;
                T significado;

                ClaveValor() {};
                ClaveValor(const std::string& c, const T& s) :
                    clave(c), significado(s) {};
            };

        private:

            struct Nodo {
                T valor;
                Nodo* hijos[256];
                bool esta;

                Nodo() : hijos(0), esta(false) {};
            };

            // Estructura auxiliar para el borrado
            // (en c++03 no la podemos meter como local en la funcion)
            struct Paso {
                Nodo* nodo;
                unsigned char siguiente;

                Paso(Nodo* n, unsigned char s) : nodo(n), siguiente(s) {};
            };

            Nodo* raiz_;
            ClaveValor minimo_;
            ClaveValor maximo_;

            /* Funciones auxiliares */
            Nodo& crearNodo() const;
            bool tieneHijos(const Nodo&) const;
            unsigned char menorHijo(const Nodo&) const;
            unsigned char mayorHijo(const Nodo&) const;
    };

    /****************************
     * Implementación
     ****************************/

    template<class T>
    DiccTrie<T>::DiccTrie() :
        raiz_(NULL) {}

    template<class T>
    DiccTrie<T>::~DiccTrie() {
        // Hay formas mas eficientes de hacer esto...
        while(raiz_ != NULL) {
            borrar(minimo_.clave);
        }
    }

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
            if(prox->hijos[(unsigned char) k[i]] == NULL) {
                nodo = crearNodo();
                prox->hijos[(unsigned char) k[i]] = &nodo;
            }
            prox = prox->hijos[(unsigned char) k[i]];
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
                if(prox->hijos[(unsigned char) k[i]] == NULL){
                    prox = prox->hijos[(unsigned char) k[i]];
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
            prox = prox->hijos[(unsigned char) k[i]];
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
            prox = prox->hijos[(unsigned char) k[i]];
            i++;
        }

        return prox->v;
    }

    template<class T>
    void DiccTrie<T>::borrar(const std::string& k) {
        // Tiene que estar definido
        assert(definido(k));

        unsigned int i = 0;
        Nodo* prox;
        aed2::Lista<Paso> camino;

        while(i < k.length() ) {
            camino.AgregarAdelante(Paso (prox, k[i]));
            prox = prox->hijos[(unsigned char) k[i]];
            i++;
        }

        prox->esta = false;
        while(camino.Longitud() and !prox->esta and !tieneHijos(*prox)) {
            Paso paso = camino.Primero();
            camino.Fin();

            delete prox;
            prox = paso.nodo;
            prox->hijos[paso.siguiente] = NULL;
        }

        if(!raiz_->esta and !tieneHijos(*raiz_)) {
            raiz_ = NULL;
        } else {
            // Recalcular el mínimo
            prox = raiz_;
            std::string s = "";

            while(!prox->esta) {
                unsigned char menor = menorHijo(*prox);
                s += menor;
                prox = prox->hijos[menor];
            }

            minimo_.clave = s;
            minimo_.significado = prox->valor;

            // Recalcular el máximo
            prox = raiz_;
            s = "";

            while(tieneHijos(*prox)) {
                unsigned char mayor = mayorHijo(*prox);
                s += mayor;
                prox = prox->hijos[mayor];
            }

            maximo_.clave = s;
            maximo_.significado = prox->valor;
        }
    }

    template<class T>
    struct DiccTrie<T>::ClaveValor DiccTrie<T>::maximo() const {
        assert(raiz_ != NULL);
        return maximo_;
    }

    template<class T>
    struct DiccTrie<T>::ClaveValor DiccTrie<T>::minimo() const {
        assert(raiz_ != NULL);
        return minimo_;
    }

    /****************************
     * Auxiliares
     ****************************/

    template<class T>
    struct DiccTrie<T>::Nodo& DiccTrie<T>::crearNodo() const {
        Nodo* p = new Nodo();
        return *p;
    }

    template<class T>
    bool DiccTrie<T>::tieneHijos(const Nodo& n) const {
        bool res = false;
        for(int i=0; i < 256; i++) {
            res |= n.hijos[i] != NULL;
        }
        return res;
    }

    template<class T>
    unsigned char DiccTrie<T>::menorHijo(const Nodo& n) const {
        assert(tieneHijos(n));
        unsigned int res = 256;

        for(unsigned int i=0; i < 256; i++) {
            if(n.hijos[i] != NULL and res > i) {
                res = i;
            }
        }
        return res;
    }

    template<class T>
    unsigned char DiccTrie<T>::mayorHijo(const Nodo& n) const {
        unsigned int res = 0;

        for(unsigned int i=0; i < 256; i++) {
            if(n.hijos[i] != NULL) {
                res = i;
            }
        }
        return res;
    }
}

#endif //TRIE_INCLUDED_H
