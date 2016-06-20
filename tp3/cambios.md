## Cambios respecto a la especificación

- Los nodos de diccTrie ahora tienen un bool `esta` para saber si tienen un valor válido.
    Cambiaron un cacho los algoritmos.

- DB ahora tiene una fn `indexar` para poder crear un índice en una tabla.
    El tema es que no tiene una función que devuelva una tabla mutable,
    como para correr `indexar` directamente ahí.
    TODO: agregar un `tabla(nt)` no const ?

- Tabla::borrarRegistro siempre siempre borraba todo el conjunto de valores
    indexados en indices[T]_, por mas que el índice no sea clave.
    Ahora checkea ese caso y busca y borra linealmente en el conjunto.

- Le agregamos operadores != a Lista, Dicc y Conj de la cátedra.
    Dicc usa != de K en su implementación, lo que no nos permitía
    hacer un diccionario de registros.

