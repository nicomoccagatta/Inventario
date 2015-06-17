/*
 * VistaListadoProductos.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaListadoProductos.h"

void VistaListadoProductos::update(){
	std::cout << "update" <<std::endl;
}

void VistaListadoProductos::setearAtributos(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo){
	this->vista = vista;
	model = modelo;
	productos = model->getProductos();
}

void VistaListadoProductos::run(){
	std::list<Producto*>::const_iterator lit (productos->begin()), lend(productos->end());
	  for(;lit!=lend;++lit)
		  std::cout << "Nombre Producto: " <<(*lit)->getNombre() << ' ' << std::endl;
}

VistaListadoProductos::~VistaListadoProductos() {
}

