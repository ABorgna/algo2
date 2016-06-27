
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
            DiccTrie(const DiccTrie<T>& otro);
            ~DiccTrie();
            DiccTrie& operator = (DiccTrie<T> otro);

            void definir(const std::string& k, const T& v);
            bool definido(const std::string& k) const;

            const T& obtener(const std::string& k) const;
            T& obtener(const std::string& k);

            void borrar(const std::string& k);

            bool vacio() const;

            DiccTrie<T>::ClaveValor maximo() const;
            DiccTrie<T>::ClaveValor minimo() const;

            bool operator == (const DiccTrie<T>& other) const;

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

                Nodo() : esta(false) {
                    // En c++03 no se puede usar initalization lists
                    // con arreglos...
                    for(int i=0; i<256; i++) {
                        hijos[i] = NULL;
                    }
                };

                Nodo(const Nodo& otro) :
                    valor(otro.valor),
                    esta(otro.esta) {

                    for(int i=0; i<256; i++) {
                        if(otro.hijos[i] != NULL) {
                            hijos[i] = new Nodo(*otro.hijos[i]);
                        } else {
                            hijos[i] = NULL;
                        }
                    }
                };

                bool operator == (
                        const typename DiccTrie<T>::Nodo& other) const;
                bool operator != (
                        const typename DiccTrie<T>::Nodo& other) const;
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
            bool tieneHijos(const Nodo&) const;
            unsigned char menorHijo(const Nodo&) const;
            unsigned char mayorHijo(const Nodo&) const;
    };

    template <class T>
    bool operator == (const DiccTrie<T>&, const DiccTrie<T>&);

    template <class T>
    bool operator != (const DiccTrie<T>&, const DiccTrie<T>&);

    /****************************
     * Implementación
     ****************************/

    template<class T>
    DiccTrie<T>::DiccTrie() :
        raiz_(NULL) {}

    template<class T>
    DiccTrie<T>::DiccTrie(const DiccTrie<T>& otro) :
        raiz_(NULL),
        minimo_(otro.minimo_),
        maximo_(otro.maximo_)
    {
        if(otro.raiz_ != NULL) {
            this->raiz_ = new Nodo(*otro.raiz_);
        }
    }

    template<class T>
    DiccTrie<T>& DiccTrie<T>::operator= (DiccTrie<T> otro) {
        Nodo* swapTmp;

        swapTmp = raiz_;
        raiz_ = otro.raiz_;
        otro.raiz_ = swapTmp;

        maximo_ = otro.maximo_;
        minimo_ = otro.minimo_;

        return *this;
    }

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
            raiz_ = new Nodo();
            eraVacio = true;
        }

        prox = raiz_;

        while(i < k.length()) {
            if(prox->hijos[(unsigned char) k[i]] == NULL) {
                prox->hijos[(unsigned char) k[i]] = new Nodo();
            }
            prox = prox->hijos[(unsigned char) k[i]];
            i++;
        }

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
                if(prox->hijos[(unsigned char) k[i]] != NULL){
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

        return prox->valor;
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

        return prox->valor;
    }

    template<class T>
    void DiccTrie<T>::borrar(const std::string& k) {
        // Tiene que estar definido
        assert(definido(k));

        unsigned int i = 0;
        Nodo* prox = raiz_;
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
            delete raiz_;
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
    bool DiccTrie<T>::vacio() const {
        return raiz_ == NULL;
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

    template <class T>
    bool DiccTrie<T>::operator == (const DiccTrie<T>& other) const {
        if((raiz_ == NULL) xor (other.raiz_ == NULL)) return false;
        return raiz_ == NULL or *raiz_ == *other.raiz_;
    }

    template <class T>
    bool operator == (const DiccTrie<T>& t1, const DiccTrie<T>& t2) {
        return t1.operator==(t2);
    }

    template <class T>
    bool operator != (const DiccTrie<T>& t1, const DiccTrie<T>& t2) {
        return !(t1.operator==(t2));
    }

    template <class T>
    bool DiccTrie<T>::Nodo::operator==(
            const typename DiccTrie<T>::Nodo& other) const {
        if(esta != other.esta) return false;
        if(esta and valor != other.valor) return false;

        for(int i=0; i<256; i++) {
            if((hijos[i] == NULL) xor (other.hijos[i] == NULL)) return false;
            if(hijos[i] != NULL and *hijos[i] != *other.hijos[i]) return false;
        }
        return true;
    }

    template <class T>
    bool DiccTrie<T>::Nodo::operator!=(
            const typename DiccTrie<T>::Nodo& other) const {
        return !(this->operator==(other));
    }
}

#endif //TRIE_INCLUDED_H
