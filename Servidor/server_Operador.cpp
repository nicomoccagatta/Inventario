#include "server_Operador.h"
#include <list>
#include <string>

using server::Operador;
using server::Reserva;
using server::Turno;
using common::Protocolo;
using common::Socket;

Operador::Operador(const common::Socket& cliente,
                   const common::Protocolo& protocolo,
                   std::list<Turno*>& turnos)
    : cliente(cliente),
      protocolo(protocolo),
      turnos(turnos),
      realizarOperaciones(true) {}

Operador::~Operador() {/*delete this->cliente;*/
}

// Escucha las consultas de entrantes por el socket, las resuelve y reenvia la
// informacion correspondiente.
void Operador::atenderOperaciones() {
  this->realizarOperaciones = true;
  while (this->cliente.estaConectado() && this->realizarOperaciones) {
    std::string mensajeRecibido = this->protocolo.recibirMensaje(this->cliente);
    if (this->cliente.estaConectado())
      this->protocolo.enviarMensaje(this->cliente,
                                    this->realizarOperacion(mensajeRecibido));
  }
  this->cliente.cerrarConeccion();
}

// Obliga al operador a que finalice la tarea actual.
void Operador::detenerOperaciones() {
  if (this->realizarOperaciones) {
    this->cliente.abortarConeccion();
    // espero que se terminen las operaciones
    // solo la tarea en ejecucion
    // determianra feacientemente que se
    // cerro la coneccion.
    this->realizarOperaciones = false;
  }
}

// TAREA PRINCIPAL. A partir de un comando recibido resuelve que operacion debe
// realizar, al ejecuta y retorna el resultado.
const std::string Operador::realizarOperacion(std::string& comandoDeOperacion) {
  if (comandoDeOperacion.length() > 1) {
    if (strcmp(comandoDeOperacion.c_str(), kMensajeListarReservasDisponibles) ==
        0) {
      return this->listarReservasDisponibles();
    } else {
      char opcion = comandoDeOperacion[0];
      std::stringstream parseador;
      comandoDeOperacion = comandoDeOperacion.substr(
          kLargoMensajeOpcion,
          comandoDeOperacion.length() - (kLargoMensajeOpcion + 1));
      unsigned long int idDeCliente =
          Operador::extraerIdCliente(comandoDeOperacion);
      switch (opcion) {
        case kMensajeRegistrarReserva: {
          unsigned int idDeTurno = Operador::extraerIdTurno(comandoDeOperacion);
          unsigned int cantComensales =
              Operador::extraerCantComensales(comandoDeOperacion);
          return this->registrarReserva(idDeCliente, idDeTurno, cantComensales);
          break;
        }
        case kMensajeConsultarReserva: {
          return this->consultarReserva(idDeCliente);
          break;
        }
        case kMensajeBorrarReserva: {
          unsigned int idDeTurno = Operador::extraerIdTurno(comandoDeOperacion);
          return this->borrarReserva(idDeCliente, idDeTurno);
          break;
        }
      }
    }
  }
  return kMensajeError;
}

// Reune la informacion de todos los turnos que conoce y la retorna formateada.
const std::string Operador::listarReservasDisponibles() const {
  std::stringstream infoARetornar;
  for (std::list<Turno*>::const_iterator i = this->turnos.begin();
       i != this->turnos.end(); i++) {
    infoARetornar << Operador::idTurnoFormateado((*i)->getIdTurno())
                  << kMensajeDelimitadorCampos << (*i)->getFechaYHora()
                  << kMensajeDelimitadorCampos << "("
                  << (*i)->getReservasDisponibles() << ")" << std::endl;
  }
  return infoARetornar.str();
}

// Busca el turno solicitado, si lo encuentra intentara realizar la reserva
// retornando siempre el resultado de la operacion.
const std::string Operador::registrarReserva(
    const unsigned long int idCliente, const unsigned int idTurno,
    const unsigned int cantComensales) {
  for (std::list<Turno*>::iterator i = this->turnos.begin();
       i != this->turnos.end(); i++) {
    if ((*i)->getIdTurno() == idTurno) {
      if ((*i)->agregarReserva(idCliente, cantComensales))
        return kMensajeOK;
      else
        return kMensajeError;
    }
  }
  // recorrio todos los turnos y no existe el turno pedido.
  return kMensajeError;
}

// Reune toda la informacion de las reservas realizadas bajo el idCliente y la
// retorna formateada.
const std::string Operador::consultarReserva(const unsigned long int idCliente)
    const {
  std::stringstream infoARetornar;
  for (std::list<Turno*>::iterator i = this->turnos.begin();
       i != this->turnos.end(); i++) {
    unsigned int reservasHechasEnEsteTurno =
        (*i)->reservasRegistradas(idCliente);
    if (reservasHechasEnEsteTurno > 0)
      infoARetornar << idCliente << kMensajeDelimitadorCampos
                    << Operador::idTurnoFormateado((*i)->getIdTurno())
                    << kMensajeDelimitadorCampos << (*i)->getFechaYHora()
                    << kMensajeDelimitadorCampos << reservasHechasEnEsteTurno
                    << std::endl;
  }
  if (infoARetornar.str() != "")
    return infoARetornar.str();
  else
    return kMensajeError;
}

// Busca en los turnos que conoce el inidicado por idTurno, en caso de que
// exista le indica que elimine la reserva del cliente con idCliente.
const std::string Operador::borrarReserva(const unsigned long int idCliente,
                                          const unsigned int idTurno) {
  for (std::list<Turno*>::iterator i = this->turnos.begin();
       i != this->turnos.end(); i++) {
    if ((*i)->getIdTurno() == idTurno) {
      if ((*i)->borrarReserva(idCliente))
        return kMensajeOK;
      else
        return kMensajeError;
    }
  }
  // recorrio todos los turnos y no existe el turno pedido.
  return kMensajeError;
}

void Operador::run() { this->atenderOperaciones(); }

const common::Socket& Operador::getCliente() const { return this->cliente; }

unsigned long int Operador::extraerArgumentoDeComando(
    const std::string& comandoDeOperacion, const size_t numeroDeParametro) {
  std::stringstream parseador;
  parseador << comandoDeOperacion;
  unsigned long int valorArgumento = 0;
  for (size_t i = 0; i < numeroDeParametro; ++i) {
    // seteo a  cero para derminar si se obtuvo la
    // informacion o el argumento no estaba disponible.
    valorArgumento = 0;
    parseador >> valorArgumento;
  }
  return valorArgumento;
}

unsigned long int Operador::extraerIdCliente(
    const std::string& comandoDeOperacion) {
  return extraerArgumentoDeComando(comandoDeOperacion, kNroArgumentoIDCliente);
}

unsigned int Operador::extraerIdTurno(const std::string& comandoDeOperacion) {
  return extraerArgumentoDeComando(comandoDeOperacion, kNroArgumentoIDTurno);
}

unsigned int Operador::extraerCantComensales(
    const std::string& comandoDeOperacion) {
  return extraerArgumentoDeComando(comandoDeOperacion,
                                   kNroArgumentoCantComensales);
}

// Extiende la representacion del id del turno a 4 caracteres.
const std::string Operador::idTurnoFormateado(const unsigned int idTurno) {
  std::string representacionARetornar("");
  std::stringstream formateador;
  formateador << idTurno;
  for (size_t i = 0;
       i < kLargoRepresentacionIdTurno - formateador.str().length(); i++)
    representacionARetornar.append("0");
  representacionARetornar.append(formateador.str());
  return representacionARetornar;
}
