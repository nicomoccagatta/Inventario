#include <time.h>
#include "server_Servidor.h"
#include "server_BaseDeDatos.h"
#include <iostream>
#include <list>
#include <string>

using server::Servidor;
using server::BaseDeDatos;

int main(int argc, char* argv[]) {
//  if (argc < 3) return 0;
  Servidor server;
  if (server.conectado())
    server.start();
  else
    return 0;
  std::string rta("");
  while (rta != "q") {
    std::cin >> rta;
  }
  server.ignorarUsuarios();
  server.join();
  return 0;
}
