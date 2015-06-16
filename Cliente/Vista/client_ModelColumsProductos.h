/*
 * client_ModelColumsProductos.h
 *
 *  Created on: Jun 15, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_MODELCOLUMSPRODUCTOS_H_
#define CLIENTE_VISTA_CLIENT_MODELCOLUMSPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm/treemodel.h>

class ModelColumsProductos: public Gtk::TreeModel {
public:
	ModelColumsProductos();
	virtual ~ModelColumsProductos();
};

#endif /* CLIENTE_VISTA_CLIENT_MODELCOLUMSPRODUCTOS_H_ */
