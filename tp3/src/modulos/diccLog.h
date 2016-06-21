
#ifndef AVL_INCLUDED_H
#define AVL_INCLUDED_H

#include <assert.h>

#include "../aed2.h"

namespace tp3 {

    template<class K, class T>
    class DiccLog {
        private:
            struct Nodo;

        public:
            struct ClaveValor;
            struct const_ClaveValor;
            class Iterador;
            class const_Iterador;

            DiccLog();
            ~DiccLog();

            void definir(const K& k, const T& v);
            bool definido(const K& k) const;

            const T& obtener(const K& k) const;
            T& obtener(const K& k);

            void borrar(const K& k);

            DiccLog<K,T>::ClaveValor maximo() const;
            DiccLog<K,T>::ClaveValor minimo() const;

            DiccLog<K,T>::Iterador CrearIt();
            DiccLog<K,T>::const_Iterador CrearIt() const;

            bool operator == (const DiccLog<K, T>& otro) const;
            bool operator != (const DiccLog<K, T>& otro) const;

            struct ClaveValor {
                const K& clave;
                T& significado;

                ClaveValor(const K& c, T& s) :
                    clave(c), significado(s) {};
            };

            struct const_ClaveValor {
                const K& clave;
                const T& significado;

                const_ClaveValor(const K& c, const T& s) :
                    clave(c), significado(s) {};
            };

            class Iterador {
                public:

                    Iterador();
                    Iterador(const typename DiccLog<K, T>::Iterador& otro);
                    Iterador& operator = (const typename DiccLog<K, T>::Iterador& otro);

                    bool operator == (const typename DiccLog<K, T>::Iterador& otro) const;
                    bool operator != (const typename DiccLog<K, T>::Iterador& otro) const;

                    bool hayMas() const;
                    ClaveValor actual() const;
                    void avanzar();

                private:

                    Nodo* actual_;
                    aed2::Lista<Nodo*> siguientes_;
                    DiccLog<K,T>* dicc;
            };

            class const_Iterador {
                public:

                    const_Iterador();
                    const_Iterador(const typename DiccLog<K, T>::Iterador& otro);
                    const_Iterador& operator = (const typename DiccLog<K, T>::Iterador& otro);

                    bool operator == (const typename DiccLog<K, T>::const_Iterador& otro) const;
                    bool operator != (const typename DiccLog<K, T>::const_Iterador& otro) const;

                    bool hayMas() const;
                    const_ClaveValor actual() const;
                    void avanzar();

                private:

                    Nodo* actual_;
                    aed2::Lista<Nodo*> siguientes_;
                    DiccLog<K,T>* dicc;
            };

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

    template<class K, class T>
    DiccLog<K, T>::DiccLog() 
    {
        assert(false);
    }

    template<class K, class T>
    DiccLog<K, T>::~DiccLog()
    {
        assert(false);
    }

    template<class K, class T>
    void DiccLog<K, T>::definir(const K& k, const T& v)
    {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K, T>::definido(const K& k) const
    {
        assert(false);
    }

    template<class K, class T>
    const T& DiccLog<K, T>::obtener(const K& k) const
    {
        assert(false);
    }

    template<class K, class T>
    T& DiccLog<K, T>::obtener(const K& k)
    {
        assert(false);
    }

    template<class K, class T>
    void DiccLog<K, T>::borrar(const K& k)
    {
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::maximo() const
    {
        assert(false);
    }
    
    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::minimo() const
    {
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K, T>::Iterador DiccLog<K, T>::CrearIt()
    {
        assert(false);
    }

    
}

#endif //AVL_INCLUDED_H
