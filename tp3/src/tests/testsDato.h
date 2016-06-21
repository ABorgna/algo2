#include <string>
#include <iostream>

#include "../modulos/dato.h"
#include "../mini_test.h"

namespace testsDato
{
    void constructor() {
        tp3::Dato dN = tp3::Dato(42);
        tp3::Dato dS = tp3::Dato("asd");

        ASSERT(dN.isNat());
        ASSERT(!dN.isString());

        ASSERT(!dS.isNat());
        ASSERT(dS.isString());

        ASSERT_EQ(dN.getNat(), 42);
        ASSERT_EQ(dS.getString(), "asd");
    }

    void cmp() {
        tp3::Dato dN0 = tp3::Dato(0);
        tp3::Dato dN1 = tp3::Dato(42);
        tp3::Dato dN2 = tp3::Dato(42);
        tp3::Dato dS0 = tp3::Dato("");
        tp3::Dato dS1 = tp3::Dato("asd");
        tp3::Dato dS2 = tp3::Dato("asd");

        ASSERT(dN0 != dN1);
        ASSERT(dN1 == dN2);

        ASSERT(dS0 != dS1);
        ASSERT(dS1 == dS2);

        ASSERT(dN0 != dS0);
    }

    void ord() {
        tp3::Dato dN0 = tp3::Dato(0);
        tp3::Dato dN1 = tp3::Dato(42);
        tp3::Dato dN2 = tp3::Dato(42);
        tp3::Dato dS0 = tp3::Dato("");
        tp3::Dato dS1 = tp3::Dato("asd");
        tp3::Dato dS2 = tp3::Dato("asd");

        ASSERT(dN0 < dN1);
        ASSERT(!(dN1 < dN2));

        ASSERT(dS0 < dS1);
        ASSERT(!(dS1 < dS2));

        ASSERT(dN0 < dS0);
        ASSERT(!(dN2 > dS2));
    }

    void main(int, char**) {
        std::cout << "dato:" << std::endl;
        RUN_TEST( constructor );
        RUN_TEST( cmp );
        RUN_TEST( ord );
    }
}
