#include "common_Protocolo.h"
#include <string>

using common::Protocolo;
using common::Socket;

Protocolo::Protocolo(const std::string& finalizador,
                     const std::string& remplazoFinalizador)
    : finalizadorDeMensaje(finalizador),
      remplazoFinalizadorDeMensaje(remplazoFinalizador) {}

Protocolo::~Protocolo() {}

const std::string Protocolo::getFinalizadorDeMensaje() const {
  return this->finalizadorDeMensaje;
}

void Protocolo::setFinalizadorMensaje(const std::string& finalizador) {
  this->finalizadorDeMensaje = finalizador;
}

const std::string Protocolo::getRemplazoFinalizadorDeMensaje() const {
  return this->remplazoFinalizadorDeMensaje;
}

void Protocolo::setRemplazoFinalizadorMensaje(
    const std::string& remplazoFinalizador) {
  this->remplazoFinalizadorDeMensaje = remplazoFinalizador;
}

const std::string Protocolo::recibirMensaje(common::Socket& skt) const {
  return this->protocolizarMensaje(
      skt.recibirMensajeFinalizado(this->finalizadorDeMensaje));
}
void Protocolo::enviarMensaje(common::Socket& skt, std::string mensaje) const {
  skt.enviarMensaje(this->protocolizarMensaje(mensaje));
}

const std::string Protocolo::protocolizarMensaje(std::string mensaje) const {
  if (mensaje == "") return kFinalizadorPorDefecto;
  unsigned int i;
  for (i = 0; i < mensaje.length() - 1; i++) {
    // si encuentro uno de los caracateres a remplazar, lo reemplazo.
    if (mensaje[i] == this->getRemplazoFinalizadorDeMensaje()[0]) {
      mensaje[i] = this->getFinalizadorDeMensaje()[0];
    } else {
      // si hay finalizadoes en el mensaje y no son el ultimo caracter, los
      // remplazo
      if (mensaje[i] == this->getFinalizadorDeMensaje()[0] &&
          i < (mensaje.length() - 1)) {
        mensaje[i] = this->getRemplazoFinalizadorDeMensaje()[0];
      }
    }
  }
  // si el mensaje no termina con el finalizador correspondiente lo agrego.
  if (mensaje[i] != this->getFinalizadorDeMensaje()[0]) {
    return mensaje.append(this->getFinalizadorDeMensaje());
  }
  return mensaje;
}
