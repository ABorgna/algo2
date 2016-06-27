#include <string>
#include <iostream>

#include "../modulos/tabla.h"
#include "../mini_test.h"

namespace testsTabla
{
    tp3::Registro sampleCampos();
    aed2::Conj<tp3::Campo> sampleClaves();

    tp3::Registro sampleReg0();
    tp3::Registro sampleReg1();
    tp3::Registro sampleReg2();
    tp3::Registro sampleReg3();

    void constructor() {
        tp3::Registro campos = sampleCampos();
        aed2::Conj<tp3::Campo> claves = sampleClaves();

        tp3::Tabla t = tp3::Tabla("nombre", claves, campos);

        ASSERT_EQ(t.nombre(), "nombre");
        ASSERT(t.campos() == campos);

        tp3::Registro::Iterador it = campos.CrearIt();
        while(it.hayMas()) {
            tp3::Campo c = it.actual().clave;
            tp3::Dato d = it.actual().significado;

            ASSERT_EQ(t.esClave(c), claves.Pertenece(c));
            ASSERT(!t.esIndice(c));
            ASSERT_EQ(t.tipoCampo(c), d.isNat());

            it.avanzar();
        }

        ASSERT_EQ(t.accesos(), 0);
        ASSERT_EQ(t.cantidadRegistros(), 0);
        ASSERT(!t.registros().HaySiguiente());
    }

    void insertar() {
        tp3::Registro campos = sampleCampos();
        aed2::Conj<tp3::Campo> claves = sampleClaves();

        tp3::Tabla t = tp3::Tabla("nombre", claves, campos);

        t.agregarRegistro(sampleReg0());

        ASSERT_EQ(t.accesos(), 1);
        ASSERT_EQ(t.cantidadRegistros(), 1);
        ASSERT(t.registros().Siguiente() == sampleReg0());

        t.agregarRegistro(sampleReg1());
        t.agregarRegistro(sampleReg2());
        t.agregarRegistro(sampleReg3());

        ASSERT_EQ(t.accesos(), 4);
        ASSERT_EQ(t.cantidadRegistros(), 4);

        aed2::Conj<tp3::Registro> borrados;
        borrados = t.borrarRegistro("claveNat0", tp3::Dato(3));

        ASSERT_EQ(t.accesos(), 5);
        ASSERT_EQ(t.cantidadRegistros(), 3);
        ASSERT_EQ(borrados.Cardinal(), 1);
        ASSERT(borrados.CrearIt().Siguiente() == sampleReg3());

        borrados = t.borrarRegistro("claveStr0", tp3::Dato("no existe"));

        ASSERT_EQ(t.accesos(), 5);
        ASSERT_EQ(t.cantidadRegistros(), 3);
        ASSERT_EQ(borrados.Cardinal(), 0);

    }

    void indexar() {
        tp3::Registro campos = sampleCampos();
        aed2::Conj<tp3::Campo> claves = sampleClaves();

        // Indexar sobre vacío

        tp3::Tabla t = tp3::Tabla("nombre", claves, campos);

        ASSERT(!t.esIndice("claveNat0"));
        ASSERT(!t.esIndice("claveStr0"));

        t.indexar("claveNat0");

        ASSERT(t.esIndice("claveNat0"));
        ASSERT(!t.esIndice("claveStr0"));

        t.indexar("claveStr0");

        ASSERT(t.esIndice("claveNat0"));
        ASSERT(t.esIndice("claveStr0"));

        // Inserciones y max/min

        t.agregarRegistro(sampleReg0());

        ASSERT_EQ(t.maxNat(), 0);
        ASSERT_EQ(t.minNat(), 0);
        ASSERT_EQ(t.maxString(), "a");
        ASSERT_EQ(t.minString(), "a");

        t.agregarRegistro(sampleReg1());
        t.agregarRegistro(sampleReg2());
        t.agregarRegistro(sampleReg3());

        ASSERT_EQ(t.maxNat(), 3);
        ASSERT_EQ(t.minNat(), 0);
        ASSERT_EQ(t.maxString(), "d");
        ASSERT_EQ(t.minString(), "a");

        // Borrar indexados

        t.borrarRegistro("claveNat0", tp3::Dato(0));
        t.borrarRegistro("claveStr0", tp3::Dato("d"));

        ASSERT_EQ(t.cantidadRegistros(), 2);
        ASSERT_EQ(t.maxNat(), 2);
        ASSERT_EQ(t.minNat(), 1);
        ASSERT_EQ(t.maxString(), "c");
        ASSERT_EQ(t.minString(), "b");

        // Borrar inexistentes por indice

        t.borrarRegistro("claveNat0", tp3::Dato(0xDEADBEEF));
        t.borrarRegistro("claveStr0", tp3::Dato("no existe"));

        ASSERT_EQ(t.cantidadRegistros(), 2);


        // Indexar con registros indexados

        tp3::Tabla q = tp3::Tabla("nombre", claves, campos);

        q.agregarRegistro(sampleReg1());
        q.agregarRegistro(sampleReg2());
        q.agregarRegistro(sampleReg3());

        q.indexar("claveNat0");
        q.indexar("claveStr0");

        ASSERT_EQ(q.maxNat(), 3);
        ASSERT_EQ(q.minNat(), 1);
        ASSERT_EQ(q.maxString(), "d");
        ASSERT_EQ(q.minString(), "b");

        q.agregarRegistro(sampleReg0());

        ASSERT_EQ(q.maxNat(), 3);
        ASSERT_EQ(q.minNat(), 0);
        ASSERT_EQ(q.maxString(), "d");
        ASSERT_EQ(q.minString(), "a");

    }

    void buscar() {
        tp3::Registro campos = sampleCampos();
        aed2::Conj<tp3::Campo> claves = sampleClaves();

        tp3::Tabla t = tp3::Tabla("nombre", claves, campos);

        t.agregarRegistro(sampleReg0());
        t.agregarRegistro(sampleReg1());
        t.agregarRegistro(sampleReg2());
        t.agregarRegistro(sampleReg3());

        // Buscar sin indices, un registro

        tp3::Registro crit0;
        crit0.definir("claveNat0", tp3::Dato(0));

        const aed2::Conj<tp3::Registro> res0 = t.buscar(crit0);

        ASSERT_EQ(res0.Cardinal(), 1);

        const tp3::Registro res0_r0 = res0.CrearIt().Siguiente();

        ASSERT_EQ(res0_r0.obtener("claveNat0").getNat(), 0);
        ASSERT_EQ(res0_r0.obtener("claveNat1").getNat(), 0);
        ASSERT_EQ(res0_r0.obtener("claveStr0").getString(), "a");
        ASSERT_EQ(res0_r0.obtener("claveStr1").getString(), "0");

        // Buscar sin indices, varios registros

        tp3::Registro crit1;
        crit1.definir("str2", tp3::Dato("asd"));

        const aed2::Conj<tp3::Registro> res1 = t.buscar(crit1);

        ASSERT_EQ(res1.Cardinal(), 2);

        aed2::Conj<tp3::Registro>::const_Iterador it1 = res1.CrearIt();
        const tp3::Registro res1_r0 = it1.Siguiente();
        it1.Avanzar();
        const tp3::Registro res1_r1 = it1.Siguiente();

        ASSERT_EQ(res1_r0.obtener("claveNat0").getNat(), 1);
        ASSERT_EQ(res1_r1.obtener("claveNat0").getNat(), 2);

        // Buscar sin resultados

        tp3::Registro crit2;
        crit2.definir("str2", tp3::Dato("no existe"));

        const aed2::Conj<tp3::Registro> res2 = t.buscar(crit2);

        ASSERT_EQ(res2.Cardinal(), 0);

        // Buscar indexados

        t.indexar("claveNat0");
        t.indexar("claveStr0");

        tp3::Registro crit3;
        crit3.definir("claveStr0", tp3::Dato("a"));

        const aed2::Conj<tp3::Registro> res3 = t.buscar(crit3);

        ASSERT_EQ(res3.Cardinal(), 1);

        const tp3::Registro res3_r0 = res3.CrearIt().Siguiente();

        ASSERT_EQ(res3_r0.obtener("claveNat0").getNat(), 0);

        // Buscar indexados sin resultado

        tp3::Registro crit4;
        crit4.definir("claveNat0", tp3::Dato(0xDEADBEEF));

        const aed2::Conj<tp3::Registro> res4 = t.buscar(crit4);

        ASSERT_EQ(res4.Cardinal(), 0);

    }

    void main(int, char**) {
        std::cout << "******** tabla *********" << std::endl;
        RUN_TEST( constructor );
        RUN_TEST( insertar );
        RUN_TEST( indexar );
        RUN_TEST( buscar );
    }

    /* Auxiliares */

    tp3::Registro sampleCampos() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(48));
        r.definir("claveNat1", tp3::Dato(99));
        r.definir("nat2", tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("aoeu"));
        r.definir("claveStr1", tp3::Dato("hrlo"));
        r.definir("str2", tp3::Dato(""));

        return r;
    }

    aed2::Conj<tp3::Campo> sampleClaves() {
        aed2::Conj<tp3::Campo> claves;

        claves.AgregarRapido("claveNat0");
        claves.AgregarRapido("claveNat1");
        claves.AgregarRapido("claveStr0");
        claves.AgregarRapido("claveStr1");

        return claves;
    }

    tp3::Registro sampleReg0() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(0));
        r.definir("claveNat1", tp3::Dato(0));
        r.definir("nat2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("a"));
        r.definir("claveStr1", tp3::Dato("0"));
        r.definir("str2",      tp3::Dato(""));

        return r;
    }

    tp3::Registro sampleReg1() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(1));
        r.definir("claveNat1", tp3::Dato(2));
        r.definir("nat2",      tp3::Dato(0));

        r.definir("claveStr0", tp3::Dato("b"));
        r.definir("claveStr1", tp3::Dato("1"));
        r.definir("str2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg2() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(2));
        r.definir("claveNat1", tp3::Dato(4));
        r.definir("nat2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("c"));
        r.definir("claveStr1", tp3::Dato("2"));
        r.definir("str2",      tp3::Dato("asd"));

        return r;
    }


    tp3::Registro sampleReg3() {
        tp3::Registro r;

        r.definir("claveNat0", tp3::Dato(3));
        r.definir("claveNat1", tp3::Dato(8));
        r.definir("nat2",      tp3::Dato(42));

        r.definir("claveStr0", tp3::Dato("d"));
        r.definir("claveStr1", tp3::Dato("3"));
        r.definir("str2",      tp3::Dato("aoe"));

        return r;
    }



}
