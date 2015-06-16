/*
 * common_Producto.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: leandro
 */

#include "common_Producto.h"

namespace common {

unsigned long int Producto::proximoID;

Producto::Producto(unsigned long int id,const std::string& nombre,const std::string& descripcion,std::list<Stock*>* stockHistorico,const unsigned long int idIcono,std::list<unsigned long int>* idsImagenes):id(id),nombre(nombre),descripcion(descripcion),stockHistorico(stockHistorico),idIcono(idIcono),idsImagenes(idsImagenes) {
	//llevo la cuenta de cual id sera el proximo
	if (Producto::proximoID<= id)
		Producto::proximoID=++id;
}

Producto::Producto(const std::string& nombre, const std::string& descripcion,const unsigned long int idIcono):id(Producto::proximoID++),nombre(nombre),descripcion(descripcion),stockHistorico(new std::list<Stock*>()),idIcono(idIcono),idsImagenes(new std::list<unsigned long int>) {
	time_t hora;
	time (&hora);
	stockHistorico->push_front(new Stock(0,std::string(asctime(localtime(&hora)))));
}

Producto::~Producto() {
	for (std::list<Stock*>::const_iterator it= stockHistorico->begin(); it != stockHistorico->end();++it)
		delete (*it);
	delete stockHistorico;
	delete idsImagenes;
}

const std::string& Producto::getNombre() const{
	return nombre;
}

const std::string& Producto::getDescripcion() const{
	return descripcion;
}

const unsigned long int Producto::getIdIcono() const{
	return idIcono;
}

void Producto::setNombre(const std::string& nombre){
	mutex.bloquear();
	this->nombre=nombre;
	mutex.desbloquear();
}

void Producto::setDescripcion(const std::string& descripcion){
	mutex.bloquear();
	this->descripcion=descripcion;
	mutex.desbloquear();
}

const unsigned long int Producto::getId() const{
	return id;
}

const unsigned long int Producto::getStock() const{
	return (* stockHistorico->begin())->getCantidad();
}

const std::list<Stock*>* const Producto::getStockHistorico() const{
	return stockHistorico;
}

void Producto::setIdIcono(const unsigned long int  idIcono){
	mutex.bloquear();
	this->idIcono=idIcono;
	mutex.desbloquear();
}

std::list<unsigned long int>* const Producto::getIdsImagenes() {
	return idsImagenes;
}

void Producto::actualizarStock(long int cantidad, std::string fecha){
	if (cantidad>0){
		mutex.bloquear();
		long int nuevoStock =((long int) getStock())+cantidad;
		if(nuevoStock > 0)
			stockHistorico->push_front(new Stock((unsigned long int)nuevoStock,fecha));
		else
			stockHistorico->push_front(new Stock(0,fecha));
		mutex.desbloquear();
	}
}

void Producto::inicializarCuentaId(){
	proximoID=0;
}

} /* namespace common */
