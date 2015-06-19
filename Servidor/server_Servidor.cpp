#include <string>
#include <list>
#include "server_Servidor.h"

using common::Protocolo;
using common::Socket;
using server::Servidor;
using server::Operador;

// Se instancia el objeto, obtiene la informacion relevante del archivo e
// intenta setear correctamente la escucha de clientes.
Servidor::Servidor(const std::string& puerto,
                   size_t maximoDeClientesAAtender, Protocolo protocolo)
    : skt(puerto, maximoDeClientesAAtender),
      atenderClientes(true),
      operadoresActivos(0),
      protocolo(protocolo) {
  //this->parser.parsearArchivoDinamicamente(*(this->turnos));
}

// Se persisten los datos sobre lso que se opero, se liberan los recursos y se
// destruye el objeto.
Servidor::~Servidor() {}


bool Servidor::conectado() const { return this->skt.estaConectado(); }

void Servidor::cerrarConeccion() {
  if (this->operadoresActivos > 0) this->ignorarUsuarios();
  this->skt.cerrarConeccion();
}

// Acepta una coneccion entrante si esta coenctado o un Socket desonectado en
// otro caso.
Socket Servidor::aceptarCliente() {
  if (this->skt.estaConectado()) {
    return this->skt.aceptarCliente();
  } else {
    return Socket();
  }
}

// TAREA PRINCIPAL.Se esperan las coneccioens de los clientes, si las mismas son
// validas se les asigna un operador que los atienda, se liberan los operadores
// inactivos
// hasta que se cierre la coneccion por la que se aceptan los clientes.
void Servidor::atenderUsuarios() {
  this->atenderClientes = true;
  std::list<Operador*> operadores;
  while (this->skt.estaConectado() && this->atenderClientes) {
    Socket clienteAceptado = this->aceptarCliente();
    // solo sigo si recibi un cliente en buenos terminos y no es que se aborto
    // la aceptacion.
    if (this->skt.estaConectado() && this->atenderClientes) {
      // si se esta en conedicioens de atender al cliente le asigno un operador
      // que lo atienda en otro hilo.
      Operador* operadorDeCliente =
          new Operador(clienteAceptado, this->protocolo, datos);
      operadorDeCliente->start();
      this->operadoresActivos++;
      // me guardo una referencia al operador para poder conocer el resultado y
      // unir los hilos.
      operadores.push_back(operadorDeCliente);
      // reviso y libero a los operadores a los que tengo referencia que estan
      // inactivos.
      this->limpiarOperadoresInactivos(operadores);
    }
  }
  // libero a los operadores activos restantes.
  while (this->operadoresActivos > 0) {
    std::list<Operador*>::iterator iterador = operadores.begin();
    this->detenerOperador(*iterador);
    operadores.remove(*iterador);
  }
  this->cerrarConeccion();
}

// Inidica al operador que termine las operaciones actuales, espera por las
// mismas, une los hilos, libera los recursos y retorna el resultado de las
// operaciones.
const void* Servidor::detenerOperador(Operador* const operadorADetener) {
  const void* resultadoOperaciones = NULL;
  operadorADetener->detenerOperaciones();
  resultadoOperaciones = operadorADetener->join();
  delete operadorADetener;
  this->operadoresActivos--;
  return resultadoOperaciones;
}

// Termina la coneccion actual por al que se aceptan nuevos clientes, indica que
// no e acepten mas lo que provocara que en la tarea principal se unana los
// hilos correspondientemente.
void Servidor::ignorarUsuarios() {
  if (this->atenderClientes) {
    this->skt.abortarConeccion();
    // espero que todas las operaciones terminen.
    // solo la tarea principal en ejecucion determianra
    // feacientemente que se cerro la
    // coneccion.
    this->atenderClientes = false;
  }
}

size_t Servidor::getCantidadOperadoresActivos() const {
  return this->operadoresActivos;
}

void Servidor::run() { this->atenderUsuarios(); }

// Revisa las referencias que tenga a lso operadores si alguno termino su tarea
// o se le cerro la coneccion, lo libera.
void Servidor::limpiarOperadoresInactivos(std::list<Operador*>& operadores) {
  std::list<Operador*>::iterator iterador = operadores.begin();
  while (iterador != operadores.end()) {
    Operador* operadoraChequear = *iterador;
    ++iterador;
    if (!operadoraChequear->getCliente().estaConectado()) {
      operadores.remove(operadoraChequear);
      this->detenerOperador(operadoraChequear);
    }
  }
}
