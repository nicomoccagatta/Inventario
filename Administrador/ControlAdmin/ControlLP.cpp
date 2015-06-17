/*
 * ControlLP.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "ControlLP.h"

ControlLP::ControlLP(){
	modelo = 0;
}

void ControlLP::setearModelo(Modelo_Observable *model) {
	modelo = model;
}

void ControlLP::actualizarProductos(){
	modelo->actualizarProductos();
}

ControlLP::~ControlLP() {
}

