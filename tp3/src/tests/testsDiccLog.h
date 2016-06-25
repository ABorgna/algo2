#include <string>
#include <iostream>

#include "../modulos/diccLog.h"
#include "../mini_test.h"

namespace testsDiccLog
{
    void constructor() {
        tp3::DiccLog<std::string, int> d;

        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asd"));

        ASSERT_RAISE(d.obtener("asd"));
        ASSERT_RAISE(d.maximo());
        ASSERT_RAISE(d.minimo());
    }

    void definirSimple() {
        tp3::DiccLog<std::string, int> d;

        d.definir("asd",22);

        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asdf"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("asd"), 22);

        d.definir("asd",44);

        ASSERT(!d.definido(""));
        ASSERT(!d.definido("asdf"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("asd"), 44);

        d.definir("aoe",8);

        ASSERT(!d.definido("a"));
        ASSERT(!d.definido("aoeu"));
        ASSERT(d.definido("aoe"));
        ASSERT(d.definido("asd"));
        ASSERT_EQ(d.obtener("aoe"), 8);
        ASSERT_EQ(d.obtener("asd"), 44);

        d.borrar("asd");

        ASSERT(!d.definido("asd"));
        ASSERT(d.definido("aoe"));
        ASSERT_EQ(d.obtener("aoe"), 8);

        d.borrar("aoe");

        ASSERT(!d.definido(""));
        ASSERT(!d.definido("aoe"));

        d.definir("",0);

        ASSERT(d.definido(""));
    }

    void maxMin() {
        tp3::DiccLog<std::string, int> d;

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
        tp3::DiccLog<std::string, int> d1;
        tp3::DiccLog<std::string, int> d2;

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

    void iteradores() {
        tp3::DiccLog<std::string, int> d;
        tp3::DiccLog<std::string, int>::Iterador itV;
        tp3::DiccLog<std::string, int>::const_Iterador itC;

        itV = d.CrearIt();
        itC = d.CrearIt();

        ASSERT(!itV.hayMas());
        ASSERT(!itC.hayMas());

        d.definir("asd",1);
        itV = d.CrearIt();
        itC = d.CrearIt();

        ASSERT(itV.hayMas());
        ASSERT(itC.hayMas());
        ASSERT_EQ(itV.actual().clave, "asd");
        ASSERT_EQ(itC.actual().clave, "asd");
        ASSERT_EQ(itV.actual().significado, 1);
        ASSERT_EQ(itC.actual().significado, 1);

        itV.avanzar();
        itC.avanzar();

        ASSERT(!itV.hayMas());
        ASSERT(!itC.hayMas());

        // Mantiene el actual si se agregan otros
        itV = d.CrearIt();
        itC = d.CrearIt();

        d.definir("c",3);
        d.definir("b",2);

        ASSERT_EQ(itV.actual().clave, "asd");
        ASSERT_EQ(itC.actual().clave, "asd");
        ASSERT_EQ(itV.actual().significado, 1);
        ASSERT_EQ(itC.actual().significado, 1);

        // No nos importa el orden en que recorre,
        // pero si recorre todos, la suma total debe ser 6
        int acumV = 0;
        int acumC = 0;

        itV = d.CrearIt();
        itC = d.CrearIt();

        ASSERT(itV.hayMas());
        ASSERT(itC.hayMas());

        acumV += itC.actual().significado;
        acumC += itC.actual().significado;
        itV.avanzar();
        itC.avanzar();

        ASSERT(itV.hayMas());
        ASSERT(itC.hayMas());

        acumV += itC.actual().significado;
        acumC += itC.actual().significado;
        itV.avanzar();
        itC.avanzar();

        ASSERT(itV.hayMas());
        ASSERT(itC.hayMas());

        acumV += itC.actual().significado;
        acumC += itC.actual().significado;
        itV.avanzar();
        itC.avanzar();

        ASSERT(!itV.hayMas());
        ASSERT(!itC.hayMas());

        ASSERT_EQ(acumV,6);
        ASSERT_EQ(acumC,6);
    }

    void iteradoresOperators() {
        tp3::DiccLog<std::string, int> d;
        tp3::DiccLog<std::string, int>::Iterador itV1;
        tp3::DiccLog<std::string, int>::Iterador itV2;
        tp3::DiccLog<std::string, int>::const_Iterador itC1;
        tp3::DiccLog<std::string, int>::const_Iterador itC2;

        d.definir("a",1);
        d.definir("b",2);
        d.definir("c",3);
        d.definir("d",4);

        itV1 = d.CrearIt();
        itV2 = d.CrearIt();
        itC1 = d.CrearIt();
        itC2 = d.CrearIt();

        ASSERT(itV1 == itV2);
        ASSERT(itC1 == itC2);

        itV1.avanzar();
        itC1.avanzar();

        ASSERT(itV1 != itV2);
        ASSERT(itC1 != itC2);

        itV2.avanzar();
        itC2.avanzar();

        ASSERT(itV1 == itV2);
        ASSERT(itC1 == itC2);

        itV1.avanzar();
        itC1.avanzar();
        itV2 = itV1;
        itC2 = itC1;

        ASSERT(itV1 == itV2);
        ASSERT(itC1 == itC2);
    }

    void main(int, char **) {
        std::cout << "******** diccLog *******" << std::endl;
        RUN_TEST( constructor );
        // RUN_TEST( definirSimple );
        // RUN_TEST( maxMin );
        // RUN_TEST( eq );
        // RUN_TEST( iteradores );
        // RUN_TEST( iteradoresOperators );
    }
}
