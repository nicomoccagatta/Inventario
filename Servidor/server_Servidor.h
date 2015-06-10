#ifndef SERVER_SERVIDOR_H_
#define SERVER_SERVIDOR_H_
#include <list>
#include <string>
#include "common_Protocolo.h"
#include "common_Thread.h"
#include "server_Operador.h"
#include "server_SocketServidor.h"
#include "server_BaseDeDatos.h"
#define kNumeroMaximoDeClientes 20
#define kPuertoDefault "1037"

using common::Protocolo;

namespace server {

class Servidor : public Thread {
 public:
  Servidor(const std::string& puerto= kPuertoDefault,
           size_t maximoDeClientesAAtender = kNumeroMaximoDeClientes,
           Protocolo protocolo = Protocolo());
  virtual ~Servidor();
  bool conectado() const;
  Socket aceptarCliente();
  void cerrarConeccion();
  void atenderUsuarios();
  const void* detenerOperador(Operador* const operadorADetener);
  void ignorarUsuarios();
  size_t getCantidadOperadoresActivos() const;
  void run();

 private:
  SocketServidor skt;
  bool atenderClientes;
  size_t operadoresActivos;
  Protocolo protocolo;
  BaseDeDatos datos;
  void limpiarOperadoresInactivos(std::list<Operador*>& operadores);
};
}

#endif
