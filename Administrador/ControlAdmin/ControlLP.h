/*
 * ControlLP.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLLP_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLLP_H_

#include "ModeloAdmin/admin_ModeloObservable.h"

class ControlLP {
	Modelo_Observable *modelo;
public:
	ControlLP();
	void setearModelo(Modelo_Observable *model);
	void actualizarProductos();
	virtual ~ControlLP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLLP_H_ */
