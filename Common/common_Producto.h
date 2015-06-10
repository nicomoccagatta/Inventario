#ifndef COMMON_PRODUCTO_H_
#define COMMON_PRODUCTO_H_

#include <list>
#include <string>
#include <time.h>
#include "common_Stock.h"
#include "common_Mutex.h"

namespace common {

class Producto {
public:
	Producto(std::string nombre, std::string descripcion,std::list<Stock*>* stockHistorico,unsigned long int id);
	Producto(std::string nombre, std::string descripcion);
	virtual ~Producto();
	const std::string getNombre() const;
	const std::string getDescripcion() const;
	void setNombre(const std::string& nombre);
	void setDescripcion(const std::string& descripcion);
	const unsigned long int getId() const;
	const unsigned long int getStock() const;
	const std::list<Stock*>* const getStockHistorico() const;
	void actualizarStock(long int cantidad, std::string fecha);
	static void inicializarCuentaId();

private:
	std::string nombre;
	std::string descripcion;
	std::list<Stock*>* stockHistorico;
	unsigned long int id;
	Mutex mutex;
	static unsigned long int proximoID;
};

} /* namespace common */

#endif /* COMMON_PRODUCTO_H_ */
