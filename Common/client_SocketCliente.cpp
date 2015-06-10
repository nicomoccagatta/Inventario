#include <string>
#include "client_SocketCliente.h"
using common::Socket;
using client::SocketCliente;

SocketCliente::SocketCliente(const std::string& ipServidor,
                             const std::string& puertoServidor) {
  if (ipServidor != "" && puertoServidor != "") {
    addrinfo filtroDeDirecciones = getFiltroDeDirecciones();
    addrinfo* listaDeDireccionesAccesibles =
        listarDirecciones(ipServidor, puertoServidor, filtroDeDirecciones);
    addrinfo* informacionDeDireccion = listaDeDireccionesAccesibles;
    // intento conectar un socket en alguna de las direcciones validas que
    // obtuve.
    for (; informacionDeDireccion != NULL && !estaConectado();
         informacionDeDireccion = (informacionDeDireccion->ai_next))
      conectarConDireccion(*informacionDeDireccion);
    freeaddrinfo(listaDeDireccionesAccesibles);
  }
}

SocketCliente::~SocketCliente() {}

const addrinfo SocketCliente::getFiltroDeDirecciones() {
  struct addrinfo filtro;
  memset(&filtro, 0, sizeof(struct addrinfo));
  filtro.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
  filtro.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
  filtro.ai_flags = 0;              /* None  */
  return filtro;
}

addrinfo* SocketCliente::listarDirecciones(const std::string& hostname,
                                           const std::string& servicename,
                                           const addrinfo& filtro) {
  struct addrinfo* listaDeDirecciones;
  int resultadoBusqueda = getaddrinfo(
      hostname.c_str(), servicename.c_str(), &filtro,
      &listaDeDirecciones);  // pido todas las conecciones que pueda.
  if (resultadoBusqueda != 0)
    return NULL;
  else
    return listaDeDirecciones;
}
