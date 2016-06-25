
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
                    Iterador(DiccLog<K,T>* d, typename DiccLog<K,T>::Nodo* r);
                    Iterador(const typename DiccLog<K,T>::Iterador& otro);
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
                    const_Iterador(const DiccLog<K, T>* d, const typename DiccLog<K,T>::Nodo* r);
                    const_Iterador(const typename DiccLog<K, T>::const_Iterador& otro);
                    const_Iterador& operator = (const typename DiccLog<K, T>::Iterador& otro);

                    bool operator == (const typename DiccLog<K, T>::const_Iterador& otro) const;
                    bool operator != (const typename DiccLog<K, T>::const_Iterador& otro) const;

                    bool hayMas() const;
                    const_ClaveValor actual() const;
                    void avanzar();

                private:

                    const Nodo* actual_;
                    aed2::Lista<Nodo*> siguientes_;
                    const DiccLog<K,T>* dicc;
            };

        private:

            struct Nodo {

                Nodo(const K& k, const T& v, Nodo* p);

                K clave;
                T valor;

                Nodo* menor;
                Nodo* mayor;
                Nodo* padre;

                int fdb;
            };

            Nodo* raiz_;
            Nodo* minimo_;
            Nodo* maximo_;

            void auxDefinir(Nodo* n, const K& k, const T& v);
    };

    template<class K, class T>
    DiccLog<K, T>::DiccLog() 
    {
        raiz_ = NULL;
        minimo_ = NULL;
        maximo_ = NULL;
    }

    template<class K, class T>
    DiccLog<K, T>::~DiccLog()
    {
        if( this->raiz_ != NULL )
            delete this->raiz_;
    }

    template<class K, class T>
    void DiccLog<K, T>::definir(const K& k, const T& v)
    {
        if( this->raiz_ == NULL ) {
            this->raiz_ = new Nodo(k, v, NULL);
        }
        else {
            auxDefinir(this->raiz_, k, v);
        }
    }

    template<class K, class T>
    DiccLog<K, T>::Nodo::Nodo(const K& k, const T& v, typename DiccLog<K, T>::Nodo* p)
        : valor(v)
    {
        this->clave = k;
        this->menor = NULL;
        this->mayor = NULL;
        this->padre = p;
        this->fdb = 0;
    }
    
    template<class K, class T>
    void DiccLog<K, T>::auxDefinir(typename DiccLog<K, T>::Nodo* n, const K& k, const T& v)
    {
    }

    template<class K, class T>
    bool DiccLog<K, T>::definido(const K& k) const
    {
        if( this->raiz_ == NULL )
            return false;
        if( this->raiz_->clave == k )
            return true;
        return false;
    }

    template<class K, class T>
    const T& DiccLog<K, T>::obtener(const K& k) const
    {
        if( this->raiz_ == NULL ) throw -1;
        if( this->raiz_->clave == k )
            return this->raiz_->valor;
    }

    template<class K, class T>
    T& DiccLog<K, T>::obtener(const K& k)
    {
        if( this->raiz_ == NULL ) 
            throw -1;
        if( this->raiz_->clave == k )
            return this->raiz_->valor;
    }

    template<class K, class T>
    void DiccLog<K, T>::borrar(const K& k)
    {
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::maximo() const
    {
        if(maximo_ == NULL) throw -1;
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::minimo() const
    {
        if(minimo_ == NULL) throw -1;
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K, T>::Iterador DiccLog<K, T>::CrearIt()
    {
        return DiccLog<K, T>::Iterador(this, this->raiz_);
    }

    template<class K, class T>
    typename DiccLog<K, T>::const_Iterador DiccLog<K, T>::CrearIt() const
    {
        return DiccLog<K, T>::const_Iterador(this, this->raiz_);
    }

    template<class K, class T>
    bool DiccLog<K,T>::operator==(const DiccLog<K,T>& otro) const {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K,T>::operator!=(const DiccLog<K,T>& otro) const {
        return !(this->operator==(otro));
    }

    /************************
     * Iterador
     ************************/

    template<class K, class T>
    DiccLog<K,T>::Iterador::Iterador()
    {
        assert(false);
    }

    template<class K, class T>
    DiccLog<K,T>::Iterador::Iterador(DiccLog<K,T>* dicc, typename DiccLog<K,T>::Nodo* raiz) {
        this->dicc = dicc;
        this->actual_ = raiz;
        this->siguientes_ = aed2::Lista<Nodo*>();
    }

    template<class K, class T>
    DiccLog<K,T>::Iterador::Iterador(const typename DiccLog<K,T>::Iterador& otro) 
    {
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K,T>::Iterador& DiccLog<K,T>::Iterador::operator=(
            const typename DiccLog<K,T>::Iterador& otro) {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K,T>::Iterador::operator==(const typename DiccLog<K,T>::Iterador& otro) const {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K,T>::Iterador::operator!=(const typename DiccLog<K,T>::Iterador& otro) const {
        return !(this->operator==(otro));
    }

    template<class K, class T>
    bool DiccLog<K,T>::Iterador::hayMas() const {
        return this->actual_ != NULL;
    }

    template<class K, class T>
    typename DiccLog<K,T>::ClaveValor DiccLog<K,T>::Iterador::actual() const {
        if(this->actual_ == NULL)
            throw -1;
        assert(false);
    }

    template<class K, class T>
    void DiccLog<K,T>::Iterador::avanzar() {
        if(this->siguientes_.EsVacia())
            throw -1;
        assert(false);
    }

    /************************
     * Iterador constante
     ************************/

    template<class K, class T>
    DiccLog<K,T>::const_Iterador::const_Iterador() {
        assert(false);
    }

    template<class K, class T>
    DiccLog<K,T>::const_Iterador::const_Iterador(
            const DiccLog<K,T>* dicc, 
            const typename DiccLog<K,T>::Nodo* raiz
    ) {
        this->dicc = dicc;
        this->actual_ = raiz;
        this->siguientes_ = aed2::Lista<Nodo*>();
    }

    template<class K, class T>
    DiccLog<K,T>::const_Iterador::const_Iterador(
            const typename DiccLog<K,T>::const_Iterador& otro
    ) {
        assert(false);
    }

    template<class K, class T>
    typename DiccLog<K,T>::const_Iterador& DiccLog<K,T>::const_Iterador::operator=(
            const typename DiccLog<K,T>::Iterador& otro) {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K,T>::const_Iterador::operator==(
            const typename DiccLog<K,T>::const_Iterador& otro) const {
        assert(false);
    }

    template<class K, class T>
    bool DiccLog<K,T>::const_Iterador::operator!=(
            const typename DiccLog<K,T>::const_Iterador& otro) const {
        return !(this->operator==(otro));
    }

    template<class K, class T>
    bool DiccLog<K,T>::const_Iterador::hayMas() const {
        return this->actual_ != NULL;
    }

    template<class K, class T>
    typename DiccLog<K,T>::const_ClaveValor DiccLog<K,T>::const_Iterador::actual() const {
        assert(false);
    }

    template<class K, class T>
    void DiccLog<K,T>::const_Iterador::avanzar() {
        assert(false);
    }
}

#endif //AVL_INCLUDED_H
