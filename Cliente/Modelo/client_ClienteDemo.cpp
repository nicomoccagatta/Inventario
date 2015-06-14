/*
 * client_ClienteDemo.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#include <iostream>
#include <sstream>

#include "client_ClienteDemo.h"
#include "common_CommandParser.h"

ClienteDemo::ClienteDemo() : client("localhost","1037"){
	// TODO Auto-generated constructor stub

}

ClienteDemo::~ClienteDemo() {
	// TODO Auto-generated destructor stub
}

void ClienteDemo::cerrarConeccion(){
	this->client.cerrarConeccion();
}

bool ClienteDemo::actualizarProductos(){
	if (this->client.estaConectado()){
		//protocolo.enviarMensaje(this->client,"D|COCA|La mas rica|");
		//std::cout << protocolo.recibirMensaje(this->client);
		//protocolo.enviarMensaje(this->client,"D|PEPSI|feaaaaa|");
		//std::cout << protocolo.recibirMensaje(this->client);
		protocolo.enviarMensaje(this->client,"A");
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarProductos();

	CommandParser parser;

	//std::cout << respuesta << "\n";

	parser.tokenize(respuesta);

	/*unsigned int p=1;
	try{
		while (true){
			std::cout << parser.getParametro(p++);
		}
	}catch (std::exception& e){
	}*/

	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string nombre = parser.getParametro(argum+1);
			std::string descripcion = parser.getParametro(argum+2);
			//icono
			this->data.agregarProducto(nombre,descripcion,id);

			std::cout << "Agregando Producto:" << id << " " << nombre << " " << descripcion << std::endl;
			argum+=3;//4 con icono
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	return true;
}

bool ClienteDemo::actualizarAreasDeVision(){
	if (this->client.estaConectado()){
		//protocolo.enviarMensaje(this->client,"G|CLOSET|FOTO|");
		//std::cout << protocolo.recibirMensaje(this->client);
		//protocolo.enviarMensaje(this->client,"G|PASILLO|VIDEO|");
		//std::cout << protocolo.recibirMensaje(this->client);
		protocolo.enviarMensaje(this->client,"B");
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarAreasDeVision();

	CommandParser parser;

	//std::cout << respuesta << "\n";

	parser.tokenize(respuesta);

	unsigned int p=1;
	try{
		while (true){
			std::cout << parser.getParametro(p++);
		}
	}catch (std::exception& e){
	}

	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string ubicacion = parser.getParametro(argum+1);
			std::string tipo = parser.getParametro(argum+2);
			//icono
			this->data.agregarAreaDeVision(ubicacion,tipo,id);

			std::cout << "Agregando Area:" << id << " " << ubicacion << " " << tipo << std::endl;
			argum+=3;//4 con icono
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();
	return true;
}

const std::list<AreaDeVision*>* ClienteDemo::getAreasDeVision() const{
	return data.getAreasDeVision();
}
