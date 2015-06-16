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
	this->cliente.cerrarConeccion();
}

bool ModeloObservable::actualizarProductos(){
	return this->cliente.actualizarProductos();
}

bool ModeloObservable::actualizarAreasDeVision(){
	return this->cliente.actualizarAreasDeVision();
}

const std::list<AreaDeVision*>* ModeloObservable::getAreasDeVision() const{
	return this->cliente.getAreasDeVision();
}

const std::list<Producto*>* ModeloObservable::getProductos() const {
	return this->cliente.getProductos();
}
/*
Template Matching foto
M|ID|FECHA|altoIMAGEN|anchoIMAGEN|tamanioIMAGEN|\n
ok|\n
BYTESIMAGEN
ok|\n ó error|\n
*/
void ModeloObservable::enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	this->cliente.enviarFotoTemplateMatching(idArea, fecha, rutaDeImagen);
}
