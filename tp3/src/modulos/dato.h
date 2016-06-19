
#ifndef DATO_INCLUDED_H
#define DATO_INCLUDED_H

#include "../aed2.h"
#include <string.h>

namespace tp3 {

    typedef std::string NombreTabla;
    typedef std::string Campo;

    enum TipoCampo { NAT, STR };

    class Dato {
        private:
            //TipoCampo tipo;
    };

    typedef aed2::Dicc<Campo, Dato> Registro;

}

#endif //DATO_INCLUDED_H
