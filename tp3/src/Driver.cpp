#include "Driver.h"

bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

bool aed2::operator != (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return !(c1 == c2);
}

using namespace aed2;

////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver() {
    db = tp3::DB();
}

Driver::~Driver() {
}

// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves) {
    assert(!db.hayTabla(nombre));
    assert(!columnas.EsVacio());
    assert(!claves.EsVacio());

    tp3::Tabla* t = new tp3::Tabla(nombre, claves, colsToRegistro(columnas));

    db.agregarTabla(*t);
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro) {
    assert(db.hayTabla(tabla));

    db.insertarEntrada(tabla, registroToRegistroTp3(registro));
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor) {
    assert(db.hayTabla(tabla));

    db.borrar(tabla, columna, datoToDatoTp3(valor));
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);
    return registroToCols(t.campos());
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);
    const tp3::Registro campos = t.campos();
    aed2::Conj<NombreCampo> res;

    aed2::Dicc<tp3::Campo, tp3::Dato>::const_Iterador it = campos.CrearIt();

    while(it.HaySiguiente()) {
        const tp3::Campo c = it.SiguienteClave();
        if(t.esClave(c)) {
            res.AgregarRapido(c);
        }
        it.Avanzar();
    }

    return res;
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);
    return itRegsConstToRegistros(t.registros());
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);
    return t.accesos();
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);

    assert(t.cantidadRegistros());
    assert(t.esIndice(columna));

    if(t.tipoCampo(columna)) {
        return Driver::Dato(t.minNat());
    } else {
        return Driver::Dato(t.minString());
    }
}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const {
    assert(db.hayTabla(tabla));

    const tp3::Tabla t = db.tabla(tabla);

    assert(t.cantidadRegistros());
    assert(t.esIndice(columna));

    if(t.tipoCampo(columna)) {
        return Driver::Dato(t.maxNat());
    } else {
        return Driver::Dato(t.maxString());
    }
}

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const {
    assert(db.hayTabla(tabla));

    return regsTp3ToRegistros(db.buscar(tabla, registroToRegistroTp3(criterio)));
}

aed2::Conj<NombreTabla> Driver::tablas() const {
    aed2::Conj<NombreTabla> res;
    tp3::itTablasConst tablas = db.tablas();

    while(tablas.HaySiguiente()) {
        res.AgregarRapido(tablas.Siguiente().nombre());
        tablas.Avanzar();
    }

    return res;
}

const NombreTabla Driver::tablaMaxima() const {
    assert(db.tablas().HaySiguiente());
    return db.tablaMaxima().nombre();
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));
    const tp3::Tabla t = db.tabla(tabla);
    tp3::Registro::const_Iterador it = t.campos().CrearIt();

    while(it.HaySiguiente()) {
        const tp3::Campo& c = it.SiguienteClave();
        bool esNat = it.SiguienteSignificado().isNat();

        if(esNat && t.esIndice(c)) return true;

        it.Avanzar();
    }
    return false;
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));
    const tp3::Tabla t = db.tabla(tabla);
    tp3::Registro::const_Iterador it = t.campos().CrearIt();

    while(it.HaySiguiente()) {
        const tp3::Campo& c = it.SiguienteClave();
        bool esString = it.SiguienteSignificado().isString();

        if(esString && t.esIndice(c)) return true;

        it.Avanzar();
    }
    return false;
}

const NombreCampo& Driver::campoIndiceNat(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));
    assert(tieneIndiceNat(tabla));
    const tp3::Tabla t = db.tabla(tabla);
    tp3::Registro::const_Iterador it = t.campos().CrearIt();

    while(it.HaySiguiente()) {
        const tp3::Campo& c = it.SiguienteClave();
        bool esNat = it.SiguienteSignificado().isNat();

        if(esNat && t.esIndice(c)) return c;

        it.Avanzar();
    }

    // Deberia terminar antes
    assert(false);
}

const NombreCampo& Driver::campoIndiceString(const NombreTabla& tabla) const {
    assert(db.hayTabla(tabla));
    assert(tieneIndiceString(tabla));
    const tp3::Tabla t = db.tabla(tabla);
    tp3::Registro::const_Iterador it = t.campos().CrearIt();

    while(it.HaySiguiente()) {
        const tp3::Campo& c = it.SiguienteClave();
        bool esString = it.SiguienteSignificado().isString();

        if(esString && t.esIndice(c)) return c;

        it.Avanzar();
    }

    // Deberia terminar antes
    assert(false);
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo) {
    assert(db.hayTabla(tabla));
    assert(!tieneIndiceNat(tabla));
    assert(db.tabla(tabla).campos().Definido(campo));
    assert(db.tabla(tabla).tipoCampo(campo));

    db.indexar(tabla, campo);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo) {
    assert(db.hayTabla(tabla));
    assert(!tieneIndiceString(tabla));
    assert(db.tabla(tabla).campos().Definido(campo));
    assert(!db.tabla(tabla).tipoCampo(campo));

    db.indexar(tabla, campo);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const {
    return db.hayJoin(tabla1, tabla2);
}

const NombreCampo& Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const {
    return db.campoJoin(tabla1, tabla2);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo) {
    db.generarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) {
    db.borrarJoin(tabla1, tabla2);
}

Driver::Registro unir(const Driver::Registro& reg1, const Driver::Registro& reg2, const NombreCampo& clave) {
    // TODO ...
    assert(false);
}

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const {
    // TODO ...
    assert(false);
}

/***************************************
 * Funciones auxiliares
 ***************************************/

tp3::Registro Driver::colsToRegistro(const aed2::Conj<Columna>&) const {
    // TODO ...
    assert(false);
}

aed2::Conj<Columna> Driver::registroToCols(const tp3::Registro&) const {
    // TODO ...
    assert(false);
}

aed2::Conj<Driver::Registro> Driver::itRegsConstToRegistros(const tp3::itRegistrosConst&) const {
    // TODO ...
    assert(false);
}

aed2::Conj<Driver::Registro> Driver::regsTp3ToRegistros(const aed2::Conj<tp3::Registro>&) const {
    // TODO ...
    assert(false);
}

tp3::Registro Driver::registroToRegistroTp3(const Driver::Registro&) const {
    // TODO ...
    assert(false);
}

tp3::Dato Driver::datoToDatoTp3(const Driver::Dato&) const {
    // TODO ...
    assert(false);
}

