#include <time.h>
#include "server_Servidor.h"
#include "server_BaseDeDatos.h"
#include "common_Imagen.h"
#include <iostream>
#include <list>
#include <string>


#include "opencv.hpp"
#include <cv.h>
#include <highgui.h>

using namespace cv;

using server::Servidor;
using server::BaseDeDatos;
using common::Imagen;

int main(int argc, char* argv[]) {
//  if (argc < 3) return 0; no se si ams adelante va a haber que agarrar argumentos, lo dejo.
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

