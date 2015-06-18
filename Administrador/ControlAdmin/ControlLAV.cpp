/*
 * ControlLP.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "ControlLAV.h"

ControlLAV::ControlLAV(){
	modelo = 0;
}

void ControlLAV::setearModelo(Modelo_Observable *model) {
	modelo = model;
}

void ControlLAV::actualizarAreasDeVision(){
	modelo->actualizarAreasDeVision();
}

ControlLAV::~ControlLAV() {
}

