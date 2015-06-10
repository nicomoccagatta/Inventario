#include <string>
#include "client_Cliente.h"

using common::Protocolo;
using client::SocketCliente;
using client::Cliente;

// Se instancia el objeto y se intenta conectar al servidor con al direccion
// indicada.
Cliente::Cliente(const std::string& direccionServidor, Protocolo protocolo)
    : skt(obtenerDireccionIP(direccionServidor),
          obtenerPuerto(direccionServidor)),
      protocolo(protocolo) {}

Cliente::~Cliente() {}

const std::string Cliente::recibirMensaje() {
  if (this->skt.estaConectado())
    return this->protocolo.recibirMensaje(this->skt);
  else
    return "";
}

void Cliente::enviarMensaje(const std::string& mensaje) {
  if (this->skt.estaConectado())
    this->protocolo.enviarMensaje(this->skt, mensaje);
}

bool Cliente::conectado() const { return this->skt.estaConectado(); }

void Cliente::cerrarConeccion() { this->skt.cerrarConeccion(); }

const size_t Cliente::realizarConsultas() {
  // seguira la ejecucion solo si se pudo setear y conectar al servidor
  // correctamente.
  if (skt.estaConectado()) {
    std::string mensajeAEnviar;
    while (skt.estaConectado()) {
      getline(std::cin, mensajeAEnviar);
      if (strcmp(mensajeAEnviar.c_str(), kMensajeFinDeSesion) != 0) {
        enviarMensaje(mensajeAEnviar);
        std::string mensajeRecibido = recibirMensaje();
        if (skt.estaConectado())
          std::cout << mensajeRecibido;
        else
          return 1;
      } else {
        // si el usuario ingreso el mensaje de finalizacion cierro la
        // coneccion y la aplicacion.
        cerrarConeccion();
      }
    }
    cerrarConeccion();
    return kRetornoOK;
  }
  return kRetornoError;
}

const std::string Cliente::obtenerDireccionIP(
    const std::string& direccionServidor) {
  std::stringstream parseadorDeArgumentos(direccionServidor);
  std::string direccionIP;
  getline(parseadorDeArgumentos, direccionIP, kSeparadorDireccion);
  return direccionIP;
}

const std::string Cliente::obtenerPuerto(const std::string& direccionServidor) {
  std::stringstream parseadorDeArgumentos(direccionServidor);
  std::string direccionIP;
  getline(parseadorDeArgumentos, direccionIP, kSeparadorDireccion);
  std::string puerto;
  parseadorDeArgumentos >> puerto;
  return puerto;
}
