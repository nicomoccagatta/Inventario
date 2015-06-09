/*
 * common_Producto.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: leandro
 */

#include "common_Producto.h"

namespace common {

unsigned long int Producto::proximoID;

Producto::Producto(std::string nombre, std::string descripcion, std::list<Stock*>* stockHistorico ,unsigned long int id):nombre(nombre),descripcion(descripcion),stockHistorico(stockHistorico),id(id) {
	//llevo la cuenta de cual id sera el proximo
	if (Producto::proximoID<= id)
		Producto::proximoID=++id;
}

Producto::Producto(std::string nombre, std::string descripcion):nombre(nombre),descripcion(descripcion),stockHistorico(new std::list<Stock*>()),id(Producto::proximoID++){
	time_t hora;
	time (&hora);
	stockHistorico->push_front(new Stock(0,std::string(asctime(localtime(&hora)))));
}

Producto::~Producto() {
	for (std::list<Stock*>::const_iterator it= stockHistorico->begin(); it != stockHistorico->end();++it)
		delete (*it);
	delete stockHistorico;
}

const std::string Producto::getNombre() const{
	return nombre;
}

const std::string Producto::getDescripcion() const{
	return descripcion;
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

void Producto::actualizarStock(long int cantidad, std::string fecha){
	long int nuevoStock =((long int) getStock())+cantidad;
	if(nuevoStock > 0)
		stockHistorico->push_front(new Stock((unsigned long int)nuevoStock,fecha));
	else
		stockHistorico->push_front(new Stock(0,fecha));
}

void Producto::inicializarCuentaId(){
	proximoID=0;
}

} /* namespace common */
