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
#include "common_Imagen.h"

using common::Imagen;

ClienteDemo::ClienteDemo() : client("localhost","1037"){
	if (!client.estaConectado())
		std::cerr << "NO ESTOY CONECTADO\n";

}

ClienteDemo::~ClienteDemo() {
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();
}

void ClienteDemo::cerrarConeccion(){
	this->client.cerrarConeccion();
}

bool ClienteDemo::actualizarProductos(){
	if (this->client.estaConectado()){
		protocolo.enviarMensaje(this->client,"A|");
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

			unsigned long int idIcono;
			ss.clear();
			ss.flush();
			ss.str("");
			ss << parser.getParametro(argum+3);
			ss >> idIcono;
			this->data.agregarProducto(nombre,descripcion,id, idIcono);

			std::cout << "Agregando Producto:" << id << " "
					  << nombre << " " << descripcion
					  << " id Icono: " << idIcono << std::endl;
			argum+=4;//4 con icono
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
		protocolo.enviarMensaje(this->client,"B|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarAreasDeVision();

	CommandParser parser;

	//std::cout << respuesta << "\n";

	parser.tokenize(respuesta);
/*
	unsigned int p=1;
	try{
		while (true){
			std::cout << parser.getParametro(p++);
		}
	}catch (std::exception& e){
	}
*/
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
			argum+=3;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	return true;
}

const std::list<AreaDeVision*>* ClienteDemo::getAreasDeVision() const{
	return data.getAreasDeVision();
}

const std::list<Producto*>* ClienteDemo::getProductos() const {
	return data.getProductos();
}

void ClienteDemo::enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	Imagen img(rutaDeImagen);

	img.mostrarImagen();

	std::stringstream ss;
	std::string msje = "M|" + fecha;

	ss << "M|" << idArea << kMensajeDelimitadorCampos << fecha << kMensajeDelimitadorCampos;
	this->protocolo.enviarMensaje(this->client,ss.str());

	std::cerr << this->protocolo.recibirMensaje(this->client);

	this->protocolo.enviarImagen(this->client, img);

	std::cerr << this->protocolo.recibirMensaje(this->client);

	/*
	if (this->protocolo.recibirMensaje(this->client) == kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		this->protocolo.enviarImagen(this->client, img);
	}
	else{
		std::cerr << "NO LLEGO NADA\n";
	}
	if (this->protocolo.recibirMensaje(this->client) == kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		std::cerr << "LLEGO PIOLA\n";
	}else{
		std::cerr << "NO LLEGO NADA\n";
	}
	*/


}
