#include <string>
#include <iostream>

#include "../modulos/db.h"
#include "../mini_test.h"

namespace testsDB
{
    tp3::Registro sampleCampos0();
    tp3::Registro sampleCampos1();
    aed2::Conj<tp3::Campo> sampleClaves0();
    aed2::Conj<tp3::Campo> sampleClaves1();

    tp3::Registro sampleReg0_0();
    tp3::Registro sampleReg0_1();
    tp3::Registro sampleReg0_2();
    tp3::Registro sampleReg0_3();

    tp3::Registro sampleReg1_0();
    tp3::Registro sampleReg1_1();
    tp3::Registro sampleReg1_2();
    tp3::Registro sampleReg1_3();

    tp3::Tabla sampleTabla0();
    tp3::Tabla sampleTabla1();

    void constructor_y_tablas() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();

        ASSERT(!db.hayTabla("tabla0"));

        db.agregarTabla(t0);

        ASSERT(db.hayTabla("tabla0"));
        ASSERT(!db.hayTabla("tabla1"));
        ASSERT_EQ(db.tabla("tabla0").nombre(), "tabla0");
        ASSERT_EQ(db.tablaMaxima().nombre(), "tabla0");

        db.agregarTabla(t1);

        ASSERT(db.hayTabla("tabla1"));
        ASSERT_EQ(db.tabla("tabla1").nombre(), "tabla1");

    }

    void tablas_maximas() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();

        db.agregarTabla(t0);
        db.agregarTabla(t1);

        db.insertarEntrada("tabla1", sampleReg1_0());
        db.insertarEntrada("tabla1", sampleReg1_1());

        ASSERT_EQ(db.tablaMaxima().nombre(), "tabla1");

        db.insertarEntrada("tabla0", sampleReg0_0());
        db.insertarEntrada("tabla0", sampleReg0_1());
        db.insertarEntrada("tabla0", sampleReg0_2());

        ASSERT_EQ(db.tablaMaxima().nombre(), "tabla0");

        db.borrar("tabla1", "claveStr0", tp3::Dato("a"));
        db.borrar("tabla1", "claveStr0", tp3::Dato("b"));

        ASSERT_EQ(db.tablaMaxima().nombre(), "tabla1");
    }

    void buscar() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();

        db.agregarTabla(t0);
        db.agregarTabla(t1);

        db.insertarEntrada("tabla0", sampleReg0_0());
        db.insertarEntrada("tabla0", sampleReg0_1());
        db.insertarEntrada("tabla0", sampleReg0_2());
        db.insertarEntrada("tabla0", sampleReg0_3());

        db.insertarEntrada("tabla1", sampleReg1_0());
        db.insertarEntrada("tabla1", sampleReg1_1());
        db.insertarEntrada("tabla1", sampleReg1_2());
        db.insertarEntrada("tabla1", sampleReg1_3());

        tp3::Registro crit;

        crit.definir("str1_2", tp3::Dato("asd"));

        aed2::Conj<tp3::Registro> res = db.buscar("tabla1", crit);

        ASSERT_EQ(res.Cardinal(), 2);

    }

    void crear_joins_simple() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();

        db.agregarTabla(t0);
        db.agregarTabla(t1);

        ASSERT(!db.hayJoin("tabla0","tabla1"));
        ASSERT(!db.hayJoin("tabla1","tabla0"));

        tp3::itRegistrosConst it0;
        it0 = db.generarVistaJoin("tabla0","tabla1", "claveNat0");

        ASSERT(db.hayJoin("tabla0","tabla1"));
        ASSERT(!db.hayJoin("tabla1","tabla0"));
        ASSERT_EQ(db.campoJoin("tabla0","tabla1"), "claveNat0");
        ASSERT(!it0.HaySiguiente());

        it0 = db.generarVistaJoin("tabla1","tabla0", "claveStr0");

        ASSERT(db.hayJoin("tabla0","tabla1"));
        ASSERT(db.hayJoin("tabla1","tabla0"));
        ASSERT_EQ(db.campoJoin("tabla0","tabla1"), "claveNat0");
        ASSERT_EQ(db.campoJoin("tabla1","tabla0"), "claveStr0");
        ASSERT(!it0.HaySiguiente());

        tp3::itRegistrosConst it1;
        it1 = db.vistaJoin("tabla0", "tabla1");

        ASSERT(!it1.HaySiguiente());

        it1 = db.vistaJoin("tabla1", "tabla0");

        ASSERT(!it1.HaySiguiente());

        db.borrarJoin("tabla0", "tabla1");

        ASSERT(!db.hayJoin("tabla0","tabla1"));
    }

    void crear_joins_con_datos() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();

        db.agregarTabla(t0);
        db.agregarTabla(t1);

        db.insertarEntrada("tabla0", sampleReg0_0());
        db.insertarEntrada("tabla0", sampleReg0_1());
        db.insertarEntrada("tabla0", sampleReg0_2());
        db.insertarEntrada("tabla0", sampleReg0_3());

        db.insertarEntrada("tabla1", sampleReg1_0());
        db.insertarEntrada("tabla1", sampleReg1_1());
        db.insertarEntrada("tabla1", sampleReg1_2());
        db.insertarEntrada("tabla1", sampleReg1_3());

        tp3::itRegistrosConst it0;
        it0 = db.generarVistaJoin("tabla0","tabla1", "claveNat0");

        ASSERT(it0.HaySiguiente());

        tp3::itRegistrosConst it1;
        it1 = db.vistaJoin("tabla0", "tabla1");

        ASSERT(it1.HaySiguiente());

        tp3::Registro r = it1.Siguiente();

        ASSERT(r.definido("claveNat0"));
        ASSERT(r.definido("nat0_2"));
        ASSERT(r.definido("nat1_2"));
    }

    void operaciones_con_joins() {
        tp3::DB db;
        tp3::Tabla t0 = sampleTabla0();
        tp3::Tabla t1 = sampleTabla1();
        tp3::itRegistrosConst it0;
        tp3::itRegistrosConst it1;

        db.agregarTabla(t0);
        db.agregarTabla(t1);

        db.generarVistaJoin("tabla0","tabla1", "claveNat0");
        db.generarVistaJoin("tabla1","tabla0", "claveStr0");

        db.insertarEntrada("tabla0", sampleReg0_0());

        it0 = db.vistaJoin("tabla0","tabla1");
        it1 = db.vistaJoin("tabla1","tabla0");

        ASSERT(!it0.HaySiguiente());
        ASSERT(!it1.HaySiguiente());

        db.insertarEntrada("tabla1", sampleReg1_0());

        it0 = db.vistaJoin("tabla0","tabla1");
        it1 = db.vistaJoin("tabla1","tabla0");

        ASSERT(it0.HaySiguiente());
        ASSERT(it1.HaySiguiente());
        ASSERT_EQ(it0.Siguiente().obtener("claveNat0").getNat(), 0);
        ASSERT_EQ(it1.Siguiente().obtener("claveNat0").getNat(), 0);

        it0.Avanzar();
        it1.Avanzar();

        ASSERT(!it0.HaySiguiente());
        ASSERT(!it1.HaySiguiente());

        db.insertarEntrada("tabla0", sampleReg0_1());
        db.insertarEntrada("tabla0", sampleReg0_2());
        db.insertarEntrada("tabla1", sampleReg1_1());
        db.insertarEntrada("tabla1", sampleReg1_2());

        db.borrar("tabla0", "claveNat0", tp3::Dato(0));
        db.borrar("tabla1", "claveStr0", tp3::Dato("b"));

        db.insertarEntrada("tabla0", sampleReg0_3());
        db.insertarEntrada("tabla1", sampleReg1_3());

        db.borrar("tabla0", "claveNat0", tp3::Dato(3));

        it0 = db.vistaJoin("tabla0","tabla1");
        it1 = db.vistaJoin("tabla1","tabla0");

        ASSERT(it0.HaySiguiente());
        ASSERT(it1.HaySiguiente());
        ASSERT_EQ(it0.Siguiente().obtener("claveNat0").getNat(), 2);
        ASSERT_EQ(it1.Siguiente().obtener("claveNat0").getNat(), 2);
    }

    void main(int, char**) {
        std::cout << "******** DB ************" << std::endl;
        RUN_TEST( constructor_y_tablas );
        RUN_TEST( tablas_maximas );
        RUN_TEST( buscar );
        RUN_TEST( crear_joins_simple );
        RUN_TEST( crear_joins_con_datos );
        RUN_TEST( operaciones_con_joins );
    }


    /* Auxiliares */

    tp3::Registro sampleCampos0() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(48));
        r.definir("claveNat1", tp3::Dato(99));
        r.definir("nat0_2", tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("aoeu"));
        r.definir("claveStr1", tp3::Dato("hrlo"));
        r.definir("str0_2", tp3::Dato(""));

        return r;
    }

    tp3::Registro sampleCampos1() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(48));
        r.definir("claveNat1", tp3::Dato(99));
        r.definir("nat1_2", tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("aoeu"));
        r.definir("claveStr1", tp3::Dato("hrlo"));
        r.definir("str1_2", tp3::Dato(""));

        return r;
    }

    aed2::Conj<tp3::Campo> sampleClaves0() {
        aed2::Conj<tp3::Campo> claves;

        claves.AgregarRapido("claveNat0");
        claves.AgregarRapido("claveNat1");
        claves.AgregarRapido("claveStr0");
        claves.AgregarRapido("claveStr1");

        return claves;
    }

    aed2::Conj<tp3::Campo> sampleClaves1() {
        aed2::Conj<tp3::Campo> claves;

        claves.AgregarRapido("claveNat0");
        claves.AgregarRapido("claveNat1");
        claves.AgregarRapido("claveStr0");
        claves.AgregarRapido("claveStr1");

        return claves;
    }

    tp3::Registro sampleReg0_0() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(0));
        r.definir("claveNat1", tp3::Dato(0));
        r.definir("nat0_2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("a"));
        r.definir("claveStr1", tp3::Dato("0"));
        r.definir("str0_2",      tp3::Dato(""));

        return r;
    }

    tp3::Registro sampleReg0_1() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(1));
        r.definir("claveNat1", tp3::Dato(2));
        r.definir("nat0_2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("b"));
        r.definir("claveStr1", tp3::Dato("1"));
        r.definir("str0_2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg0_2() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(2));
        r.definir("claveNat1", tp3::Dato(4));
        r.definir("nat0_2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("c"));
        r.definir("claveStr1", tp3::Dato("2"));
        r.definir("str0_2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg0_3() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(3));
        r.definir("claveNat1", tp3::Dato(8));
        r.definir("nat0_2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("d"));
        r.definir("claveStr1", tp3::Dato("3"));
        r.definir("str0_2",      tp3::Dato("aoe"));

        return r;
    }

    tp3::Registro sampleReg1_0() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(0));
        r.definir("claveNat1", tp3::Dato(0));
        r.definir("nat1_2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("a"));
        r.definir("claveStr1", tp3::Dato("0"));
        r.definir("str1_2",      tp3::Dato(""));

        return r;
    }

    tp3::Registro sampleReg1_1() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(1));
        r.definir("claveNat1", tp3::Dato(2));
        r.definir("nat1_2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("b"));
        r.definir("claveStr1", tp3::Dato("1"));
        r.definir("str1_2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg1_2() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(2));
        r.definir("claveNat1", tp3::Dato(4));
        r.definir("nat1_2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("c"));
        r.definir("claveStr1", tp3::Dato("2"));
        r.definir("str1_2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg1_3() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(3));
        r.definir("claveNat1", tp3::Dato(8));
        r.definir("nat1_2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("d"));
        r.definir("claveStr1", tp3::Dato("3"));
        r.definir("str1_2",      tp3::Dato("aoe"));

        return r;
    }

    tp3::Tabla sampleTabla0() {
        tp3::Registro campos = sampleCampos0();
        aed2::Conj<tp3::Campo> claves = sampleClaves0();

        tp3::Tabla t = tp3::Tabla("tabla0", claves, campos);

        return t;
    }

    tp3::Tabla sampleTabla1() {
        tp3::Registro campos = sampleCampos1();
        aed2::Conj<tp3::Campo> claves = sampleClaves1();

        tp3::Tabla t = tp3::Tabla("tabla1", claves, campos);

        return t;
    }
}
