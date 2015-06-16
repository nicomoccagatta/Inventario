#ifndef COMMON_PRODUCTO_H_
#define COMMON_PRODUCTO_H_

#include <list>
#include <vector>
#include <string>
#include <time.h>
#include "common_Stock.h"
#include "common_Mutex.h"

namespace common {

class Producto {
public:
	Producto(unsigned long int id,const std::string& nombre,const std::string& descripcion,std::list<Stock*>* stockHistorico,const unsigned long int idIcono,std::list<unsigned long int>* idsImagenes);
	Producto(const std::string& nombre, const std::string& descripcion,const unsigned long int idIcono);
	virtual ~Producto();
	const std::string& getNombre() const;
	const std::string& getDescripcion() const;
	void setNombre(const std::string& nombre);
	void setDescripcion(const std::string& descripcion);
	const unsigned long int getId() const;
	const unsigned long int getStock() const;
	const std::list<Stock*>* const getStockHistorico() const;
	const unsigned long int getIdIcono() const;
	void setIdIcono(const unsigned long int idIcono);
	std::list<unsigned long int>* const getIdsImagenes();
	void actualizarStock(long int cantidad, std::string fecha);
	static void inicializarCuentaId();



private:
	unsigned long int id;
	std::string nombre;
	std::string descripcion;
	std::list<Stock*>* stockHistorico;
	unsigned long int idIcono;
	std::list<unsigned long int>* idsImagenes;
	Mutex mutex;
	static unsigned long int proximoID;
};

} /* namespace common */

#endif /* COMMON_PRODUCTO_H_ */
