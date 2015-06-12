/*
 * client_Data.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */
#include <iostream>
#include <vector>

#include "client_Data.h"

using common::Producto;
using common::AreaDeVision;
using common::Stock;
using std::vector;

Data::Data() {
	// TODO Auto-generated destructor stub
}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

void Data::agregarProducto(std::string nombre, std::string descripcion,
					unsigned long int id){
	Producto* nuevo = new Producto(id, nombre, descripcion, new std::list<Stock*>, 0, new std::list<unsigned long int>);
	this->productos.push_back(nuevo);
}

void Data::agregarAreaDeVision(std::string ubicacion, std::string tipoDeCapturador,
							   unsigned long int id){
	AreaDeVision* nueva = new AreaDeVision(id,ubicacion,tipoDeCapturador,new std::list<Producto*>());
	this->areasDeVision.push_back(nueva);
}

void Data::eliminarProductos(){
	std::vector<Producto*>::iterator it;
	for (it = this->productos.begin(); it != this->productos.end();++it){
		delete *(it);
	}
}

void Data::eliminarAreasDeVision(){
	std::vector<AreaDeVision*>::iterator it;
	for (it = this->areasDeVision.begin(); it != this->areasDeVision.end();++it){
		std::cout << (*it)->getId() << (*it)->getTipoDeCapturador() << (*it)->getUbicacion();
		delete *(it);
	}
}
