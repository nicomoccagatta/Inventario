#ifndef COMMON_PROTOCOLO_H_
#define COMMON_PROTOCOLO_H_
#include <string>
#include <string.h>
#include "common_Socket.h"
#define kFinalizadorPorDefecto "\n"
#define kRemplazoFinalizadorPorDefecto "\3"

namespace common {

class Protocolo {
 public:
  Protocolo(const std::string& finalizador = kFinalizadorPorDefecto,
            const std::string& remplazoFinalizador =
                kRemplazoFinalizadorPorDefecto);
  virtual ~Protocolo();
  const std::string getFinalizadorDeMensaje() const;
  void setFinalizadorMensaje(const std::string& finalizador);
  const std::string getRemplazoFinalizadorDeMensaje() const;
  void setRemplazoFinalizadorMensaje(const std::string& remplazoFinalizador);
  const std::string recibirMensaje(common::Socket& socket) const;
  void enviarMensaje(common::Socket& socket, const std::string mensaje) const;
  const std::string protocolizarMensaje(std::string mensaje) const;

 private:
  std::string finalizadorDeMensaje;
  std::string remplazoFinalizadorDeMensaje;
};
}
#endif
