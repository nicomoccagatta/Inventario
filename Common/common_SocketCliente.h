#ifndef CLIENT_SOCKETCLIENTE_H_
#define CLIENT_SOCKETCLIENTE_H_
#include <string>
#include "common_Socket.h"
using common::Socket;

namespace client {

class SocketCliente : public common::Socket {
 public:
  SocketCliente(const std::string& ipServidor,
                const std::string& puertoServidor);
  virtual ~SocketCliente();

 private:
  static addrinfo* listarDirecciones(const std::string& hostname,
                                     const std::string& servicename,
                                     const addrinfo& filtro);
  static const addrinfo getFiltroDeDirecciones();
};
}
#endif /* CLIENT_SOCKETCLIENTE_H_ */
