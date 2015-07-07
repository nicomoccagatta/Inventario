/*
 * client_ModeloObservable.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#include "client_ModeloObservable.h"

ModeloObservable::ModeloObservable(const char* ip, const char* puerto) :
	cliente(ip,puerto), enviador(&cliente) {
	//actualizador.setParametros(this, &mutexData);
	//actualizador.start();
	enviador.start();
}

ModeloObservable::~ModeloObservable() {
	//actualizador.matar();
	//actualizador.join(); //Puede llegar a tardar los 30 segundos que esta durmiendo...
	enviador.matar();
	std::cerr << "JOINEO ENVIADOR\n";
	enviador.join();
	std::cerr << "ENVIADOR JOINEADO\n";
	this->cliente.cerrarConeccion();
}

bool ModeloObservable::actualizarDatos(){
	bool aux = this->cliente.actualizarProductos() &&
			this->cliente.actualizarAreasDeVision();
	std::cerr << "NOTIFICANDOOO\n";
	this->notify();
	return aux;
}

bool ModeloObservable::actualizarProductos(){
	return this->cliente.actualizarProductos();
}

bool ModeloObservable::actualizarAreasDeVision(){
	return this->cliente.actualizarAreasDeVision();
}

const std::list<AreaDeVision*>* ModeloObservable::getAreasDeVision(){
	return this->cliente.getAreasDeVision();
}

const std::list<Producto*>* ModeloObservable::getProductos(){
	return this->cliente.getProductos();
}

std::string ModeloObservable::getImagenConId(unsigned long int id){
	return this->cliente.getImagenConId(id);
}

void ModeloObservable::enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	this->enviador.agregarImagen(idArea,fecha,rutaDeImagen, TEMPLATE_MATCHING);
}

void ModeloObservable::enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	this->enviador.agregarImagen(idArea,fecha,rutaDeImagen, FEATURE_MATCHING);
}

void ModeloObservable::enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeImagen, int intervaloSegs){
	this->enviador.agregarVideo(idArea,fechaInicio,rutaDeImagen, TEMPLATE_MATCHING,intervaloSegs);
}

void ModeloObservable::enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeImagen, int intervaloSegs){
	this->enviador.agregarVideo(idArea,fechaInicio,rutaDeImagen, FEATURE_MATCHING,intervaloSegs);
}
