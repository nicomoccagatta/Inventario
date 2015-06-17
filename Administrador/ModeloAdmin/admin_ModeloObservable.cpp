/*
 * admin_ModeloObservable.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "admin_ModeloObservable.h"

Modelo_Observable::Modelo_Observable() {
}

Modelo_Observable::~Modelo_Observable() {
	this->admin.cerrarConeccion();
}

bool Modelo_Observable::actualizarProductos(){
	return this->admin.actualizarProductos();
}

bool Modelo_Observable::actualizarAreasDeVision(){
	return this->admin.actualizarAreasDeVision();
}

const std::list<AreaDeVision*>* Modelo_Observable::getAreasDeVision() const{
	return this->admin.getAreasDeVision();
}

const std::list<Producto*>* Modelo_Observable::getProductos() const {
	return this->admin.getProductos();
}
