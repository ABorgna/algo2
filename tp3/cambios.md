## Cambios respecto a la especificación

- Los nodos de diccTrie ahora tienen un bool `esta` para saber si tienen un valor válido.
    Cambiaron un cacho los algoritmos.

- El conjunto de tablas de DB se cambia a una aed2::Lista, pues `siguiente()` del iterador
    de conjuntos solo devuelve objetos inmutables, y necesitamos poder acceder rápido a las tablas.

- Tabla::borrarRegistro siempre siempre borraba todo el conjunto de valores
    indexados en indices[T]_, por mas que el índice no sea clave.
    Ahora checkea ese caso y busca y borra linealmente en el conjunto.

- Le agregamos operadores != a Lista, Dicc y Conj de la cátedra.
    Dicc usa != de K en su implementación, lo que no nos permitía
    hacer un diccionario de registros.

- Agregamos DiccTrie::vacio() para poder eliminar tries de DB::vistasJoin_ al borrar joins

- En DB::VistaJoin no se borraba el buffer de operaciones despues de procesarlas

- DiccTrie::CrearNodo es el constructor de nodo

- DiccLog jamas actualizaba maximo y minimo en los algoritmos
