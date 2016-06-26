
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

            Nodo* auxObtenerNodo(Nodo* n, const K& k);
            void BorrarNodoEHijos(Nodo* n);
            void auxBorrarNodo(Nodo* n, const K& k);
            void auxRecortar(Nodo* n);
            void auxPropagarBorrado(Nodo* n);
            Nodo* auxMinimoNodo(Nodo* n);
            Nodo* auxMaximoNodo(Nodo* n);
            const Nodo* auxObtenerNodo(const Nodo* n, const K& k) const;
            bool auxDefinidoNodo(Nodo* n, const K& k) const;
            void auxDefinirNodo(Nodo* n, const K& k, const T& v);
            void auxPropagarInsercion(Nodo* n);
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
        if( this->raiz_ != NULL ) {
            BorrarNodoEHijos(this->raiz_);
        }
    }

    template<class K, class T>
    void DiccLog<K, T>::BorrarNodoEHijos(typename DiccLog<K, T>::Nodo* n)
    {
        if( n->menor != NULL ) {
            BorrarNodoEHijos( n->menor );
        }
        if( n->mayor != NULL ) {
            BorrarNodoEHijos( n->mayor );
        }
        delete n;
    }

    template<class K, class T>
    void DiccLog<K, T>::definir(const K& k, const T& v)
    {
        if( this->raiz_ == NULL ) {
            this->raiz_ = new Nodo(k, v, NULL);
            this->maximo_ = this->raiz_;
            this->minimo_ = this->raiz_;
        }
        else {
            auxDefinirNodo(this->raiz_, k, v);
            if( k > this->maximo_->clave ) {
                this->maximo_ = auxMaximoNodo(this->raiz_);
            }
            if( k < this->minimo_->clave ) {
                this->minimo_ = auxMinimoNodo(this->raiz_);
            }
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
    void DiccLog<K, T>::auxDefinirNodo(typename DiccLog<K, T>::Nodo* n, const K& k, const T& v)
    {
        if( n->clave == k ) {
            n->valor = v;
        }
        else {
            if( k > n->clave ) {
                if( n->mayor == NULL ) {
                    n->mayor = new Nodo(k, v, n);
                    auxPropagarInsercion(n->mayor);
                }
                else {
                    auxDefinirNodo(n->mayor, k, v);
                }
            }
            else {
                if( n->menor == NULL ) {
                    n->menor = new Nodo(k, v, n);
                    auxPropagarInsercion(n->menor);
                }
                else {
                    auxDefinirNodo(n->menor, k, v);
                }
            }
        }
    }

    template<class K, class T>
    void DiccLog<K, T>::auxPropagarInsercion(typename DiccLog<K, T>::Nodo* n)
    {
    }

    template<class K, class T>
    bool DiccLog<K, T>::definido(const K& k) const
    {
        return auxDefinidoNodo(this->raiz_, k);
    }

    template<class K, class T>
    bool DiccLog<K, T>::auxDefinidoNodo(typename DiccLog<K, T>::Nodo* n, const K& k) const
    {
        if( n == NULL ) {
            return false;
        }
        else {
            if( k == n->clave ) {
                return true;
            }
            else {
                if( k > n->clave ) {
                    return auxDefinidoNodo(n->mayor, k);
                }
                else {
                    return auxDefinidoNodo(n->menor, k);
                }
            }
        }
    }

    template<class K, class T>
    const T& DiccLog<K, T>::obtener(const K& k) const
    {
        const typename DiccLog<K, T>::Nodo* n = auxObtenerNodo(this->raiz_, k);
        if( n == NULL)
            throw -1;
        return n->valor;
    }

    template<class K, class T>
    T& DiccLog<K, T>::obtener(const K& k)
    {
        typename DiccLog<K, T>::Nodo* n = auxObtenerNodo(this->raiz_, k);
        if( n == NULL)
            throw -1;
        return n->valor;
    }

    template<class K, class T>
    const typename DiccLog<K, T>::Nodo* DiccLog<K, T>::auxObtenerNodo(const typename DiccLog<K, T>::Nodo* n, const K& k) const
    {
        if( n == NULL ) {
            return NULL;
        }
        else {
            if( k == n->clave ) {
                return n;
            }
            else {
                if( k > n->clave ) {
                    return auxObtenerNodo(n->mayor, k);
                }
                else {
                    return auxObtenerNodo(n->menor, k);
                }
            }
        }
    }

    template<class K, class T>
    typename DiccLog<K, T>::Nodo* DiccLog<K, T>::auxObtenerNodo(typename DiccLog<K, T>::Nodo* n, const K& k)
    {
        if( n == NULL ) {
            return NULL;
        }
        else {
            if( k == n->clave ) {
                return n;
            }
            else {
                if( k > n->clave ) {
                    return auxObtenerNodo(n->mayor, k);
                }
                else {
                    return auxObtenerNodo(n->menor, k);
                }
            }
        }
    }

    template<class K, class T>
    void DiccLog<K, T>::borrar(const K& k)
    {
        auxBorrarNodo(this->raiz_, k);
    }

    template<class K, class T>
    void DiccLog<K, T>::auxBorrarNodo(typename DiccLog<K, T>::Nodo* n, const K& k)
    {
        if( k == n->clave ) {
            if( n->mayor != NULL && n->menor != NULL ) {
                typename DiccLog<K, T>::Nodo* n2 = auxMinimoNodo(n->mayor);
                n->clave = n2->clave;
                n->valor = n2->valor;
                auxRecortar(n2);
            }
            else {
                auxRecortar(n);
            }
        }
        else {
            if( k > n->clave ) {
                auxBorrarNodo(n->mayor, k);
            }
            else {
                auxBorrarNodo(n->menor, k);
            }
        }
    }

    template<class K, class T>
    void DiccLog<K, T>::auxRecortar(typename DiccLog<K, T>::Nodo* n)
    {
        typename DiccLog<K, T>::Nodo* ho = NULL;
        if( n->menor != NULL ) {
            ho = n->menor;
            ho->padre = n->padre;
        }
        if( n->mayor != NULL ) {
            ho = n->mayor;
            ho->padre = n->padre;
        }
        if( n->padre == NULL ) {
            this->raiz_ = ho;
        }
        else {
            auxPropagarBorrado(n);
            if( n->padre->menor == n ) {
                n->padre->menor = ho;
            }
            else {
                n->padre->mayor = ho;
            }
        }
        if( this->maximo_ == n ) {
            if( this->raiz_ == NULL ) {
                this->maximo_ = NULL;
            }
            else {
                this->maximo_ = auxMaximoNodo(this->raiz_);
            }
        }
        if( this->minimo_ == n ) {
            if( this->raiz_ == NULL ) {
                this->minimo_ = NULL;
            }
            else {
                this->minimo_ = auxMinimoNodo(this->raiz_);
            }
        }
        delete n;
    }

    template<class K, class T>
    void DiccLog<K, T>::auxPropagarBorrado(typename DiccLog<K, T>::Nodo* n)
    {
    }

    template<class K, class T>
    typename DiccLog<K, T>::Nodo* DiccLog<K, T>::auxMinimoNodo(typename DiccLog<K, T>::Nodo* n)
    {
        if( n->menor == NULL ) {
            return n;
        }
        else {
            return auxMinimoNodo(n->menor);
        }
    }

    template<class K, class T>
    typename DiccLog<K, T>::Nodo* DiccLog<K, T>::auxMaximoNodo(typename DiccLog<K, T>::Nodo* n)
    {
        if( n->mayor == NULL ) {
            return n;
        }
        else {
            return auxMaximoNodo(n->mayor);
        }
    }   
        
    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::maximo() const
    {
        if( this->maximo_ == NULL ) {
            throw -1;
        }
        return typename DiccLog<K, T>::ClaveValor(this->maximo_->clave, this->maximo_->valor);
    }
    
    template<class K, class T>
    typename DiccLog<K, T>::ClaveValor DiccLog<K, T>::minimo() const
    {
        if( this->minimo_ == NULL ) {
            throw -1;
        }
        return typename DiccLog<K, T>::ClaveValor(this->minimo_->clave, this->minimo_->valor);
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
    DiccLog<K,T>::Iterador::Iterador(DiccLog<K,T>* dicc, typename DiccLog<K,T>::Nodo* raiz) 
    : siguientes_(aed2::Lista<Nodo*>())
    {
        this->dicc = dicc;
        this->actual_ = raiz;
        if( this->actual_ != NULL ) {
            if( this->actual_->menor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->menor);
            }
            if( this->actual_->mayor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->mayor);
            }
        }
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
        if( this->actual_ == NULL ) {
            throw -1;
        }
        return DiccLog<K,T>::ClaveValor(this->actual_->clave, this->actual_->valor);
    }

    template<class K, class T>
    void DiccLog<K,T>::Iterador::avanzar() {
        if( this->actual_ == NULL ) {
            throw -1;
        }
        if(this->siguientes_.EsVacia()) {
            this->actual_ = NULL;
        }
        else {
            this->actual_ = this->siguientes_.Primero();
            this->siguientes_.Fin();
            if( this->actual_->menor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->menor);
            }
            if( this->actual_->mayor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->mayor);
            }
        }
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
    ) 
    : siguientes_(aed2::Lista<Nodo*>())
    {
        this->dicc = dicc;
        this->actual_ = raiz;
        if( this->actual_ != NULL ) {
            if( this->actual_->menor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->menor);
            }
            if( this->actual_->mayor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->mayor);
            }
        }
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
        if( this->actual_ == NULL ) {
            throw -1;
        }
        return DiccLog<K,T>::const_ClaveValor(this->actual_->clave, this->actual_->valor);
    }

    template<class K, class T>
    void DiccLog<K,T>::const_Iterador::avanzar() {
        if( this->actual_ == NULL ) {
            throw -1;
        }
        if(this->siguientes_.EsVacia()) {
            this->actual_ = NULL;
        }
        else {
            this->actual_ = this->siguientes_.Primero();
            this->siguientes_.Fin();
            if( this->actual_->menor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->menor);
            }
            if( this->actual_->mayor != NULL ) {
                this->siguientes_.AgregarAdelante(this->actual_->mayor);
            }
        }
    }
}

#endif //AVL_INCLUDED_H
