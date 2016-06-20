#include "db.h"

using namespace tp3;

DB::DB() {
    // TODO ...
    assert(false);
}

DB::~DB() {
    // TODO ...
    assert(false);
}

void DB::agregarTabla(Tabla&) {
    // TODO ...
    assert(false);
}

void DB::insertarEntrada(const NombreTabla&, const Registro&) {
    // TODO ...
    assert(false);
}

void DB::borrar(const NombreTabla&, const Campo&, const Dato&) {
    // TODO ...
    assert(false);
}

void DB::indexar(const NombreTabla&, const Campo&) {
    // TODO ...
    assert(false);
}

bool DB::hayTabla(const NombreTabla&) const {
    // TODO ...
    assert(false);
}

const Tabla& DB::tabla(const NombreTabla&) const {
    // TODO ...
    assert(false);
}

itTablasConst DB::tablas() const {
    // TODO ...
    assert(false);
}

const Tabla& DB::tablaMaxima() const {
    // TODO ...
    assert(false);
}

itRegistrosConst DB::generarVistaJoin(const NombreTabla&,
                                  const NombreTabla&,
                                  const Campo&) {
    // TODO ...
    assert(false);
}

bool DB::hayJoin(const NombreTabla&, const NombreTabla&) const {
    // TODO ...
    assert(false);
}

const Campo& DB::campoJoin(const NombreTabla&, const NombreTabla&) const {
    // TODO ...
    assert(false);
}

void DB::borrarJoin(const NombreTabla&, const NombreTabla&) {
    // TODO ...
    assert(false);
}

itRegistrosConst DB::vistaJoin(const NombreTabla&, const NombreTabla&) {
    // TODO ...
    assert(false);
}

aed2::Conj<Registro> DB::buscar(const NombreTabla&, const Registro&) const {
    // TODO ...
    assert(false);
}

/***************************************
 * Funciones auxiliares
 ***************************************/

Registro DB::combinarRegistros(const Registro&, const Registro&) {
    // TODO ...
    assert(false);
}

