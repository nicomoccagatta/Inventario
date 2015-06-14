/*
 * client_ModeloObservable.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#include "client_ModeloObservable.h"

ModeloObservable::ModeloObservable() {
	// TODO Auto-generated constructor stub

}

ModeloObservable::~ModeloObservable() {
	this->cliente.cerrarConeccion();
}

bool ModeloObservable::actualizarProductos(){
	return this->cliente.actualizarProductos();
}

bool ModeloObservable::actualizarAreasDeVision(){
	return this->cliente.actualizarAreasDeVision();
}

const std::list<AreaDeVision*>* ModeloObservable::getAreasDeVision() const{
	return this->cliente.getAreasDeVision();
}
