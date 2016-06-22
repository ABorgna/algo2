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
        // TODO
    }

    void main(int, char**) {
        std::cout << "******** tabla *********" << std::endl;
        RUN_TEST( constructor );
        RUN_TEST( insertar );
        RUN_TEST( indexar );
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
