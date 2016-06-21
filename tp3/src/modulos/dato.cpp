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

bool Dato::operator==(const tp3::Dato& other) const {
    if(isNat() != other.isNat()) return false;

    if(isNat()){
        return getNat() == other.getNat();
    } else {
        return getString() == other.getString();
    }
}

bool Dato::operator!=(const tp3::Dato& other) const {
    return !(this->operator==(other));
}

bool Dato::operator>(const tp3::Dato& other) const {
    if(isNat() != other.isNat()) return isString();

    if(isNat()){
        return getNat() > other.getNat();
    } else {
        return getString() > other.getString();
    }
}

bool Dato::operator<(const tp3::Dato& other) const {
    return !(this->operator>(other) || this->operator==(other));
}

