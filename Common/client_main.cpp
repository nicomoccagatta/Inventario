#include <string>
#include <iostream>
#include "client_Cliente.h"

using client::Cliente;

int main(int argc, char* argv[]) {
	std::cout<<"Cliente"<<std::endl;
  if (argc > 1) {
    std::string direccionServidor(argv[1]);
    Cliente clienteConsultante(direccionServidor);
    return clienteConsultante.realizarConsultas();
  }
  return 0;
}


