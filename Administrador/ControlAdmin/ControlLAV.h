/*
 * ControlLP.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLLAV_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLLAV_H_

#include "ModeloAdmin/admin_ModeloObservable.h"

class ControlLAV {
	Modelo_Observable *modelo;
public:
	ControlLAV();
	void setearModelo(Modelo_Observable *model);
	void actualizarAreasDeVision();
	virtual ~ControlLAV();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLLAV_H_ */
