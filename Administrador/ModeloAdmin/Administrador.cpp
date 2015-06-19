/*
 * Administrador.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "Administrador.h"
#include <iostream>
#include <sstream>
#include "common_CommandParser.h"

Administrador::Administrador() : admin("localhost","1037"){
	if (!admin.estaConectado())
		std::cerr << "NO ESTOY CONECTADO\n";
}

Administrador::~Administrador() {
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();
}

void Administrador::cerrarConeccion(){
	this->admin.cerrarConeccion();
}

bool Administrador::actualizarProductos(){
	if (this->admin.estaConectado()){
		protocolo.enviarMensaje(this->admin,"A|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->admin);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarProductos();

	CommandParser parser;
	parser.tokenize(respuesta);

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

			//std::cout << "Agregando Producto:" << id << " "
				//	  << nombre << " " << descripcion
					//  << " id Icono: " << idIcono << std::endl;
			argum+=4;//4 con icono
		}
	}catch (std::exception& e){
	}
	return true;
}

bool Administrador::actualizarAreasDeVision(){
	if (this->admin.estaConectado()){
		protocolo.enviarMensaje(this->admin,"B|");
	}
	std::string respuesta = protocolo.recibirMensaje(this->admin);

	if (respuesta == "error|\n")
		return false;

	this->data.eliminarAreasDeVision();

	CommandParser parser;

	parser.tokenize(respuesta);
	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::stringstream preguntarProductos("K|");
			preguntarProductos << id;
			std::list<Producto*>* productos;
			protocolo.enviarMensaje(this->admin,preguntarProductos.str());
			std::string respuestaProd = protocolo.recibirMensaje(this->admin);
			if (respuestaProd != "error|"){
				productos = new std::list<Producto*>();
				CommandParser parserProd;
				parserProd.tokenize(respuestaProd);
				unsigned int argumProd = 1;
				try{
					while(true){
						std::stringstream obtenerProductos;

						unsigned long int idProd;
						obtenerProductos << parserProd.getParametro(argumProd);
						obtenerProductos >> idProd;

						std::string nombreProd;
						obtenerProductos.str("");
						obtenerProductos << parserProd.getParametro(argumProd+1);
						nombreProd = obtenerProductos.str();

						unsigned long int CantProd;
						obtenerProductos.str("");
						obtenerProductos << parserProd.getParametro(argumProd+2);
						obtenerProductos >> CantProd;
						std::list<common::Stock*> *stockProd = new std::list<common::Stock*>;
						common::Stock* stockProducto = new common::Stock(CantProd,"listado");
						stockProd->push_back(stockProducto);

						argumProd += 3;

						Producto *producto = new Producto(idProd,nombreProd,"",stockProd,0,0);
						productos->push_back(producto);
					}
				}catch (std::exception& e){
				}
			}
			std::string ubicacion = parser.getParametro(argum+1);
			std::string tipo = parser.getParametro(argum+2);
			//icono
			this->data.agregarAreaDeVision(ubicacion,tipo,id,productos);

			argum+=3;
		}
	}catch (std::exception& e){
	}
	return true;
}

const std::list<AreaDeVision*>* Administrador::getAreasDeVision() const{
	return data.getAreasDeVision();
}

const std::list<Producto*>* Administrador::getProductos() const {
	return data.getProductos();
}
