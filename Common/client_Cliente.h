#ifndef CLIENT_CLIENTE_H_
#define CLIENT_CLIENTE_H_

#include <iostream>
#include <string.h>
#include <string>
#include "client_SocketCliente.h"
#include "common_Protocolo.h"

#include <cv.h>
#include <highgui.h>
#include "opencv.hpp"

#define kSeparadorDireccion ':'
#define kMensajeFinDeSesion "S"
#define kRetornoOK 0
#define kRetornoError 1

using common::Protocolo;
using client::SocketCliente;

namespace client {

class Cliente {
 public:
  Cliente(const std::string& direccionServidor,
          Protocolo protocolo = Protocolo());
  virtual ~Cliente();
  bool conectado() const;
  const std::string recibirMensaje();
  void enviarMensaje(const std::string& mensaje);
  void cerrarConeccion();
  const size_t realizarConsultas();

 private:
  client::SocketCliente skt;
  common::Protocolo protocolo;
  static const std::string obtenerDireccionIP(
      const std::string& direccionServidor);
  static const std::string obtenerPuerto(const std::string& direccionServidor);
};
}

#endif
