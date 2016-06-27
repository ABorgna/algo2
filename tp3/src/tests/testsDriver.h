#include <string>
#include <iostream>

#include "../Driver.h"
#include "../mini_test.h"

namespace testsDriver
{
    void ejemplo_simple()
    {
      aed2::Driver bd;
      ASSERT_EQ(bd.tablas().Cardinal(), 0);

      aed2::Conj<aed2::Columna> columnas_personas;

      aed2::Columna columna_dni;
      columna_dni.nombre = "DNI";
      columna_dni.tipo = aed2::NAT;

      aed2::Columna columna_nombre;
      columna_nombre.nombre = "nombre";
      columna_nombre.tipo = aed2::STR;

      aed2::Columna columna_apellido;
      columna_apellido.nombre = "apellido";
      columna_apellido.tipo = aed2::STR;

      columnas_personas.Agregar( columna_dni );
      columnas_personas.Agregar( columna_nombre );
      columnas_personas.Agregar( columna_apellido );

      aed2::Conj<aed2::NombreCampo> columnas_clave_personas;
      columnas_clave_personas.Agregar("DNI");

      bd.crearTabla("personas", columnas_personas, columnas_clave_personas);
      ASSERT_EQ(bd.tablas().Cardinal(), 1);

      aed2::Driver::Registro persona;
      persona.Definir("DNI", aed2::Driver::Dato(1));
      persona.Definir("nombre", aed2::Driver::Dato("Juan"));
      persona.Definir("apellido", aed2::Driver::Dato("Perez"));

      bd.insertarRegistro("personas", persona);

      // ...
    }

    void main(int, char**)
    {
        std::cout << "******** driver ********" << std::endl;
        RUN_TEST( ejemplo_simple );
    }
}
