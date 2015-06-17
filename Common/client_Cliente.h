#ifndef CLIENT_CLIENTE_H_
#define CLIENT_CLIENTE_H_

#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include "client_SocketCliente.h"
#include "common_Protocolo.h"
#include "common_Imagen.h"

#define kSeparadorDireccion ':'
#define kMensajeFinDeSesion "X"
#define kRetornoOK 0
#define kRetornoError 1

using common::Protocolo;
using common::Imagen;
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
  Imagen recibirImagen(const std::string& idImagen);
  void enviarImagen(const Imagen& imagenAEnviar);
  void cerrarConeccion();
  const size_t realizarConsultas();
  void templateMatching(const std::string& idAreaDeVision,const Imagen& imagenAEnviar);

 private:
  SocketCliente skt;
  Protocolo protocolo;
  static const std::string obtenerDireccionIP(
      const std::string& direccionServidor);
  static const std::string obtenerPuerto(const std::string& direccionServidor);
};
}

#endif
