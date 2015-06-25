#include "common_Video.h"
#include "common_Imagen.h"
#include <list>
#include <string>


#include <iostream>
#include <string>
#include "server_Servidor.h"
#define kCodigoRetornoExistoso 0
#define kCodigoRetornoErroneo 1

using server::Servidor;

int main(int argc, char* argv[]) {



	if (argc < 3)
		return kCodigoRetornoErroneo;

	Servidor server(argv[1],argv[2]);

	if (server.conectado())
		server.start();
	else
		return kCodigoRetornoErroneo;
	std::string rta("");
	while (rta != "q") {
		std::cin >> rta;
	}
	server.ignorarUsuarios();
	server.join();
	return kCodigoRetornoExistoso;
}

