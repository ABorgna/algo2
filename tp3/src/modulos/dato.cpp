#include "dato.h"

using namespace tp3;

Dato::Dato(unsigned int n) :
    esNat_(true),
    valorNat_(n) {
}

Dato::Dato(const std::string& s) :
    esNat_(false),
    valorString_(s),
    valorNat_(0) {
}

Dato::Dato(const Dato& otro) :
    esNat_(otro.isNat()),
    valorString_(otro.isNat() ? "" : otro.getString()),
    valorNat_(otro.isNat() ? otro.getNat() : 0) {
}

bool Dato::isNat() const {
    return esNat_;
}

bool Dato::isString() const {
    return !esNat_;
}

unsigned int Dato::getNat() const {
    assert(esNat_);
    return valorNat_;
}

const std::string& Dato::getString() const {
    assert(!esNat_);
    return valorString_;
}

bool operator == (const Dato& c1, const Dato& c2) {
    if(c1.isNat() != c2.isNat()) return false;

    if(c1.isNat()){
        return c1.getNat() == c2.getNat();
    } else {
        return c1.getString() == c2.getString();
    }
}

bool operator > (const Dato& c1, const Dato& c2) {
    if(c1.isNat() != c2.isNat()) return c1.isString();

    if(c1.isNat()){
        return c1.getNat() > c2.getNat();
    } else {
        return c1.getString() > c2.getString();
    }
}

