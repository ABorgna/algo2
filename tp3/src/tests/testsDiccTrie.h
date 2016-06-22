#include <string>
#include <iostream>

#include "../modulos/diccTrie.h"
#include "../mini_test.h"

namespace testsDiccTrie
{
    void constructor() {
        tp3::DiccTrie<unsigned int> d;

        ASSERT(d.vacio());
        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asd"));
    }

    void definirSimple() {
        tp3::DiccTrie<unsigned int> d;

        d.definir("asd",22);

        ASSERT(!d.vacio());
        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asdf"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("asd"), 22);

        d.definir("asd",44);

        ASSERT(!d.vacio());
        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asdf"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("asd"), 44);

        d.definir("aoe",8);

        ASSERT(!d.vacio());
        ASSERT(!d.definido("a"));
        ASSERT(!d.definido("aoeu"));
        ASSERT(d.definido("aoe"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("aoe"), 8);
        ASSERT_EQ(d.obtener("asd"), 44);

        d.borrar("asd");

        ASSERT(!d.vacio());
        ASSERT(!d.definido("asd"));
        ASSERT(d.definido("aoe"));
        ASSERT_EQ(d.obtener("aoe"), 8);

        d.borrar("aoe");

        ASSERT(d.vacio());
        ASSERT(!d.definido(""));
        ASSERT(!d.definido("aoe"));

        d.definir("",0);

        ASSERT(!d.vacio());
        ASSERT(d.definido(""));
    }

    void maxMin() {
        tp3::DiccTrie<unsigned int> d;

        d.definir("asd",44);

        ASSERT_EQ(d.maximo().clave, "asd");
        ASSERT_EQ(d.maximo().significado, 44);
        ASSERT_EQ(d.minimo().clave, "asd");
        ASSERT_EQ(d.minimo().significado, 44);

        d.definir("a", 88);

        ASSERT_EQ(d.maximo().clave, "asd");
        ASSERT_EQ(d.maximo().significado, 44);
        ASSERT_EQ(d.minimo().clave, "a");
        ASSERT_EQ(d.minimo().significado, 88);

        d.definir("asdf", 22);

        ASSERT_EQ(d.maximo().clave, "asdf");
        ASSERT_EQ(d.maximo().significado, 22);
        ASSERT_EQ(d.minimo().clave, "a");
        ASSERT_EQ(d.minimo().significado, 88);

        d.borrar("asdf");

        ASSERT_EQ(d.maximo().clave, "asd");
        ASSERT_EQ(d.maximo().significado, 44);
        ASSERT_EQ(d.minimo().clave, "a");
        ASSERT_EQ(d.minimo().significado, 88);

        d.definir("azz", 8);

        ASSERT_EQ(d.maximo().clave, "azz");
        ASSERT_EQ(d.maximo().significado, 8);
        ASSERT_EQ(d.minimo().clave, "a");
        ASSERT_EQ(d.minimo().significado, 88);
    }

    void eq() {
        tp3::DiccTrie<unsigned int> d1;
        tp3::DiccTrie<unsigned int> d2;

        ASSERT(d1 == d1);

        ASSERT(d1 == d2);
        ASSERT(!(d1 != d2));

        d1.definir("asd", 44);

        ASSERT(d1 != d2);

        d2.definir("asd", 88);

        ASSERT(d1 != d2);

        d1.definir("a",8);
        d2.definir("a",8);

        ASSERT(d1 != d2);

        d2.definir("asd",44);

        ASSERT(d1 == d2);
        ASSERT(d2 == d2);
    }

    void main(int, char**) {
        std::cout << "******** trie **********" << std::endl;
        RUN_TEST( constructor );
        RUN_TEST( definirSimple );
        RUN_TEST( maxMin );
        RUN_TEST( eq );
    }
}
