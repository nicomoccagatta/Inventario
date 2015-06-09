#ifndef SERVER_OPERADOR_H_
#define SERVER_OPERADOR_H_
#include <iostream>
#include <string>
#include <list>
#include "common_Thread.h"
#include "common_Socket.h"
#include "common_Protocolo.h"
#include "server_Turno.h"
#define kMensajeOK "ok"
#define kMensajeError "error"
#define kMensajeListarReservasDisponibles "L\n"
#define kMensajeRegistrarReserva 'R'
#define kMensajeConsultarReserva 'C'
#define kMensajeBorrarReserva 'B'
#define kLargoMensajeOpcion 2
#define kMensajeDelimitadorCampos '\t'
#define kLargoRepresentacionIdTurno 4
#define kNroArgumentoIDCliente 1
#define kNroArgumentoIDTurno 2
#define kNroArgumentoCantComensales 3

namespace server {

class Operador : public Thread {
 public:
  Operador(const common::Socket& cliente, const common::Protocolo& protocolo,
           std::list<Turno*>& turnos);
  virtual ~Operador();
  void run();
  void atenderOperaciones();
  void detenerOperaciones();
  const common::Socket& getCliente() const;

 private:
  common::Socket cliente;
  const common::Protocolo& protocolo;
  std::list<Turno*>& turnos;
  bool realizarOperaciones;
  const std::string realizarOperacion(std::string& comandoDeOperacion);
  const std::string listarReservasDisponibles() const;
  const std::string registrarReserva(const unsigned long int idCliente,
                                     const unsigned int idTurno,
                                     const unsigned int cantComensales);
  const std::string consultarReserva(const unsigned long int idCliente) const;
  const std::string borrarReserva(const unsigned long int idCliente,
                                  const unsigned int idTurno);
  static unsigned long int extraerArgumentoDeComando(
      const std::string& comandoDeOperacion, const size_t numeroArgumento);
  static unsigned long int extraerIdCliente(
      const std::string& comandoDeOperacion);
  static unsigned int extraerIdTurno(const std::string& comandoDeOperacion);
  static unsigned int extraerCantComensales(
      const std::string& comandoDeOperacion);
  static const std::string idTurnoFormateado(const unsigned int idTurno);
};
}

#endif
