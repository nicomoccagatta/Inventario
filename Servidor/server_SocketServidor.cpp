#include "server_SocketServidor.h"

using common::Socket;
#include <string>
using server::SocketServidor;

SocketServidor::SocketServidor(const std::string& puerto,
                               size_t maximoDeClientesAAtender) {
  addrinfo filtro = getFiltroDeDirecciones();
  addrinfo* direccionEscuchaServidor;
  // obtiene la direccion en la que se establecera la escucha
  getaddrinfo(NULL, puerto.c_str(), &filtro, &direccionEscuchaServidor);
  // si es valida intentara setear la escucha por el socket asociado
  if (direccionEscuchaServidor != NULL) {
    esperarConecciones(*direccionEscuchaServidor, maximoDeClientesAAtender);
    freeaddrinfo(direccionEscuchaServidor);
  }
}


const addrinfo SocketServidor::getFiltroDeDirecciones() {
  addrinfo filtro;
  memset(&filtro, 0, sizeof(struct addrinfo));
  filtro.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
  filtro.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
  filtro.ai_flags = AI_PASSIVE;     /* AI_PASSIVE for server           */
  return filtro;
}
