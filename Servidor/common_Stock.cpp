/*
 * common_Stock.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: leandro
 */

#include "common_Stock.h"

namespace common {

Stock::Stock(unsigned long int cantidad,std::string fecha): cantidad(cantidad),fecha(fecha) {}

const std::string Stock::getFecha()const{
	return fecha;
}

const unsigned long int Stock::getCantidad()const{
	return cantidad;
}

} /* namespace common */
