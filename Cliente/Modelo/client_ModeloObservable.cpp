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
	// TODO Auto-generated destructor stub
}

bool ModeloObservable::actualizarProductos(){
	return this->cliente.actualizarProductos();
}

bool ModeloObservable::actualizarAreasDeVision(){
	return this->cliente.actualizarAreasDeVision();
}
