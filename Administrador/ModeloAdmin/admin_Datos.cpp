/*
 * admin_Datos.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "admin_Datos.h"
#include <iostream>
#include <vector>
using common::Producto;
using common::AreaDeVision;
using common::Stock;
using std::vector;

Datos::Datos() {
}

Datos::~Datos() {
}

void Datos::agregarProducto(std::string nombre, std::string descripcion,
					unsigned long int id, unsigned long int idIcono){
	Producto* nuevo = new Producto(id, nombre, descripcion, new std::list<Stock*>, idIcono, new std::list<unsigned long int>);
	this->productos.push_back(nuevo);
}

void Datos::agregarAreaDeVision(std::string ubicacion, std::string tipoDeCapturador,
							   unsigned long int id,std::list<Producto*>* listaProductos){
	AreaDeVision* nueva = new AreaDeVision(id,ubicacion,tipoDeCapturador,listaProductos);
	this->areasDeVision.push_back(nueva);
}

void Datos::eliminarProducto(unsigned long int idProd){
	std::list<Producto*>::iterator it = this->productos.begin();
	for (; it!=this->productos.end(); ++it){
		if ((*it)->getId() == idProd)
		{
			std::cerr << "Producto eliminadoo:" << (*it)->getNombre() << std::endl;
			this->productos.erase(it);
			it--;
		}
	}
}

void Datos::eliminarProductos(){
	std::list<Producto*>::iterator it;
	for (it = this->productos.begin(); it != this->productos.end();++it){
		delete *(it);
	}
	productos.clear();
}

void Datos::eliminarAreaVision(unsigned long int idAV){
	std::list<AreaDeVision*>::iterator it = this->areasDeVision.begin();
	for (; it!=this->areasDeVision.end() ; ++it )
		if ((*it)->getId() == idAV)
		{
			std::cerr << "Area de Vision eliminada:" << (*it)->getUbicacion() << std::endl;
			this->areasDeVision.erase(it);
			it--;
		}
}

void Datos::eliminarAreasDeVision(){
	std::list<AreaDeVision*>::iterator it;
	for (it = this->areasDeVision.begin(); it != this->areasDeVision.end();++it){
		//std::cout << (*it)->getId() << (*it)->getTipoDeCapturador() << (*it)->getUbicacion();
		delete *(it);
	}
	areasDeVision.clear();
}
