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

void Modelo_Observable::eliminarProducto(unsigned long int id){
	this->admin.eliminarProducto(id);
}

bool Modelo_Observable::actualizarAreasDeVision(){
	return this->admin.actualizarAreasDeVision();
}

void Modelo_Observable::eliminarAreaVision(unsigned long int idAV){
	this->admin.eliminarAreaVision(idAV);
}

void Modelo_Observable::altaProducto(std::string &nombre,std::string &descripcion,
													std::string &rutaImagenPPAL,std::list<std::string*> &rutaImagenes){
	this->admin.altaProducto(nombre,descripcion,rutaImagenPPAL,rutaImagenes);
}

void Modelo_Observable::modificarProducto(unsigned long int id,std::string &nombre,std::string &descripcion,std::string &rutaImagenPPAL,
											std::list<unsigned long int> idsAnteriores,std::list<std::string*> &rutaImagenesAgregar){
	this->admin.modificarProducto(id,nombre,descripcion,rutaImagenPPAL,idsAnteriores,rutaImagenesAgregar);
}

std::list<unsigned long int> Modelo_Observable::getIdsImagenes(unsigned long int id){
	return this->admin.getIdsImagenes(id);
}

std::string Modelo_Observable::getImagenConID(unsigned long int id){
	return (this->admin.getImagenConID(id));
}

void Modelo_Observable::altaAreaVision(const std::string &ubicacion,const std::string &capturador){
	this->admin.altaAreaVision(ubicacion,capturador);
}

void Modelo_Observable::modificarAreaVision(unsigned long int idAV,std::string& ubicacion,std::string& capturador){
	this->admin.modificarAreaVision(idAV,ubicacion,capturador);
}

unsigned long int Modelo_Observable::consultarStock(unsigned long int idProducto){
	return(this->admin.consultarStock(idProducto));
}

const std::list<AreaDeVision*>* Modelo_Observable::getAreasDeVision() const{
	return this->admin.getAreasDeVision();
}

const std::list<Producto*>* Modelo_Observable::getProductos() const {
	return this->admin.getProductos();
}
