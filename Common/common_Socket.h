#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

#define kLargoBuffer 255
#define kNumeroMaximoDeClientesAEscuchar 20

namespace common {

class Socket {
 public:
  explicit Socket(int skt = -1);
  Socket(const Socket& skt);
  virtual ~Socket();
  bool estaConectado() const;
  void conectarConDireccion(const addrinfo& direccionAConectar);
  void esperarConecciones(const addrinfo& direccionAEscuchar,
                          size_t maximoDeClientesAEscuchar =
                              kNumeroMaximoDeClientesAEscuchar);
  Socket aceptarCliente();
  void enviarMensaje(const std::string& mensaje);
  std::string recibirMensajeFinalizado(const std::string& finalizador);
  void enviarBytes(const unsigned char* const bytesAEnviar, const unsigned long int cantidadDeBytesAEnviar);
  unsigned char* const recibirBytesDinamicos(const unsigned long int cantidadDeBytesARecibir);
  void abortarConeccion();
  void cerrarConeccion();

 private:
  char* buffer;
  bool coneccionExitosa;
  addrinfo direccionVinculada;
  size_t elementosEnBuffer;
  int skt;
  std::string corrimientoBuffer(const std::string& finalizador);
};
}
#endif
