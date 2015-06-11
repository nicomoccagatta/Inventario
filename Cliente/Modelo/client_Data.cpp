/*
 * client_Data.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */
#include <vector>

#include "client_Data.h"

using common::Producto;
using common::AreaDeVision;
using std::vector;

Data::Data() {
	// TODO Auto-generated destructor stub
}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

void Data::agregarProducto(std::string nombre, std::string descripcion,
					unsigned long int id){
	Producto* nuevo = new Producto(nombre, descripcion, NULL, id);
	this->productos.push_back(nuevo);
}

void Data::agregarAreaDeVision(std::string ubicacion, std::string tipoDeCapturador,
							   unsigned long int id){
	AreaDeVision* nueva = new AreaDeVision(ubicacion,tipoDeCapturador,NULL,id);
	this->areasDeVision.push_back(nueva);
}

void Data::eliminarProductos(){
	for (unsigned int i=0; i < this->productos.size();++i){
		delete this->productos[i];
	}
}

void Data::eliminarAreasDeVision(){
	for (unsigned int i=0; i < this->areasDeVision.size();++i){
		delete this->areasDeVision[0];
	}
}
