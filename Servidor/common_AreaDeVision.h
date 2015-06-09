#ifndef COMMON_AREADEVISION_H_
#define COMMON_AREADEVISION_H_

#include <list>
#include <string>
#include "common_Producto.h"

using common::Producto;

namespace common {

class AreaDeVision {
public:
	AreaDeVision(std::string ubicacion, std::string tipoDeCapturador, std::list<Producto*>* productosDetectados ,unsigned long int id);
	AreaDeVision(std::string ubicacion, std::string tipoDeCapturador);
	virtual ~AreaDeVision();
	const std::string getUbicacion() const;
	const std::string getTipoDeCapturador() const;
	const unsigned long int getId() const;
	const std::list<Producto*>* const getProductosDetectados() const;
	void actualizarDeteccion(std::list<Producto*>* productosDetectados);
	static void inicializarCuentaId();

private:
	std::string ubicacion;
	std::string tipoDeCapturador;
	const std::list<Producto*>* productosDetectados;
	unsigned long int id;
	void liberarRecursosProductos();
	static unsigned long int proximoID;
};

} /* namespace common */

#endif /* COMMON_AREADEVISION_H_ */
