## Cambios respecto a la especificación

- Los nodos de diccTrie ahora tienen un bool `esta` para saber si tienen un valor válido.
    Cambiaron un cacho los algoritmos.

- DB ahora tiene una fn `indexar` para poder crear un índice en una tabla.
    El tema es que no tiene una función que devuelva una tabla mutable,
    como para correr `indexar` directamente ahí.
    TODO: agregar un `tabla(nt)` no const ?

