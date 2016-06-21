
#ifndef DATO_INCLUDED_H
#define DATO_INCLUDED_H

#include <assert.h>
#include <string.h>

#include "../aed2.h"

namespace tp3 {
    typedef std::string Campo;

    class Dato {
        public:
            Dato(unsigned int n);
            Dato(const std::string& s);
            Dato(const Dato& otro);

            bool isNat() const;
            bool isString() const;

            unsigned int getNat() const;
            const std::string& getString() const;

            bool operator == (const Dato& other) const;
            bool operator != (const Dato& other) const;
            bool operator > (const Dato& other) const;
            bool operator < (const Dato& other) const;

        private:
            bool esNat_;
            std::string valorString_;
            unsigned int valorNat_;

            Dato();
    };

    typedef aed2::Dicc<Campo, Dato> Registro;

}

#endif //DATO_INCLUDED_H
