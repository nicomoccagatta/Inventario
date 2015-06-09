#ifndef SOCKETSERVIDOR_H_
#define SOCKETSERVIDOR_H_
#include <string>
#include "common_Socket.h"
using common::Socket;

namespace server {

class SocketServidor : public common::Socket {
 public:
  SocketServidor(const std::string& puerto, size_t maximoDeClientesAAtender);
  virtual ~SocketServidor();

 private:
  static const addrinfo getFiltroDeDirecciones();
};
}
#endif /* SOCKETSERVIDOR_H_ */
