#include <string>
#include "client_Cliente.h"

using client::Cliente;

int main(int argc, char* argv[]) {
  if (argc > 1) {
    std::string direccionServidor(argv[1]);
    Cliente clienteConsultante(direccionServidor);
    return clienteConsultante.realizarConsultas();
  }
  return 0;
}


