#include "server_Operador.h"
#include <list>
#include <string>

using server::Operador;
using common::Protocolo;
using common::Socket;

Operador::Operador(const common::Socket& cliente, const common::Protocolo& protocolo,
		  BaseDeDatos& datos)
    : cliente(cliente),
      protocolo(protocolo),
      datos(datos),
      realizarOperaciones(true) {}

Operador::~Operador() {}


void Operador::run() { this->atenderOperaciones(); }

const common::Socket& Operador::getCliente() const { return this->cliente; }

// Escucha las consultas de entrantes por el socket, las resuelve y reenvia la
// informacion correspondiente.
void Operador::atenderOperaciones() {
  this->realizarOperaciones = true;
  while (this->cliente.estaConectado() && this->realizarOperaciones) {
    std::string mensajeRecibido = this->protocolo.recibirMensaje(this->cliente);
    if (this->cliente.estaConectado()){
    	std::string mensajeAResponder(this->realizarOperacion(mensajeRecibido));
		if (mensajeAResponder != kRespuestaNula)
				this->protocolo.enviarMensaje(this->cliente,mensajeAResponder);
    }
  }
  this->cliente.cerrarConeccion();
}


// Obliga al operador a que finalice la tarea actual.
void Operador::detenerOperaciones() {
  if (this->realizarOperaciones) {
    this->cliente.abortarConeccion();
    // espero que se terminen las operaciones
    // solo la tarea en ejecucion
    // determianra feacientemente que se
    // cerro la coneccion.
    this->realizarOperaciones = false;
  }
}

// TAREA PRINCIPAL. A partir de un comando recibido resuelve que operacion debe
// realizar, al ejecuta y retorna el resultado.
const std::string Operador::realizarOperacion(std::string& comandoDeOperacion) {
  if (comandoDeOperacion.length() > 1) {
	  switch (comandoDeOperacion[0]) {
		case kIndicadorComandoListarProductos: {
		  return listarProductos();
		  break;
		}
		case kIndicadorComandoListarAreasDeVision: {
		  return listarAreasDeVision();
		  break;
		}
		case kIndicadorComandoDetalleProducto: {
		  return detallarProducto(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoAltaProducto: {
		  return altaProducto(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoModificacionProducto: {
		  return modificacionProducto(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoBajaProducto: {
		  return bajaProducto(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoAltaAreaDeVision: {
		  return altaAreaDeVision(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoModificacionAreaDeVision: {
		  return modificacionAreaDeVision(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoBajaAreaDeVision: {
		  return bajaAreaDeVision(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoStockGeneral: {
		  return stockGeneral();
		  break;
		}
		case kIndicadorComandoStockAreaDeVision: {
		  return stockAreaDeVision(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoStockHistoricoProducto: {
		  return stockHistoricoProducto(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoAltaImagen: {
		  return altaImagen(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoSolicitudImagen: {
		  return enviarImagen(comandoDeOperacion);
		  break;
		}
		case kIndicadorComandoBajaImagen: {
		  return bajaImagen(comandoDeOperacion);
		  break;
		}
	  }
    }
  return kMensajeError;
}

const std::string Operador::listarProductos()const{
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getNombre() << kMensajeDelimitadorCampos <<(*it)->getDescripcion() << kMensajeDelimitadorCampos<< (*it)->getIdIcono() << kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::listarAreasDeVision()const{
	const std::list<AreaDeVision*>* listaAreasDeVision = datos.getAreasDeVision();
	if (listaAreasDeVision->size()==0){
		return kMensajeError;
	} else {
		std::stringstream acumulador;
		for(std::list<AreaDeVision*>::const_iterator it=listaAreasDeVision->begin(); it!=listaAreasDeVision->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getUbicacion() << kMensajeDelimitadorCampos <<(*it)->getTipoDeCapturador() << kMensajeDelimitadorCampos;
		return acumulador.str();
	}
}

const std::string Operador::detallarProducto(const std::string& comandoDeOperacion) const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoADetallar = datos.getProductoConId(idProducto);
	if (productoADetallar!=NULL){
		std::stringstream acumulador;
		acumulador << productoADetallar->getNombre() << kMensajeDelimitadorCampos << productoADetallar->getDescripcion() << kMensajeDelimitadorCampos<< productoADetallar->getIdIcono() << kMensajeDelimitadorCampos;//faltan imagenes
		for (std::list<unsigned long int>::const_iterator idImagen = productoADetallar->getIdsImagenes()->begin(); idImagen!= productoADetallar->getIdsImagenes()->end(); ++idImagen)
				acumulador << (*idImagen);
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::altaProducto(const std::string& comandoDeOperacion){
	const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,4);
	datos.agregarProducto(new Producto(nombreProducto,descripcionProducto,idIcono));
	return kMensajeOK;
}

const std::string Operador::modificacionProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoAModificar = datos.getProductoConId(idProducto);
	if (productoAModificar!=NULL){
		const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,5);
		bool existenTodasLasImagenes= datos.existeImagenConId(idIcono);
		if (existenTodasLasImagenes){
			const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
			const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
			productoAModificar->setNombre(nombreProducto);
			productoAModificar->setDescripcion(descripcionProducto);
			productoAModificar->setIdIcono(idIcono);
			return kMensajeOK;
		}
	}
	return kMensajeError;
}

const std::string Operador::bajaProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
		Producto* productoADetallar = datos.getProductoConId(idProducto);
		if (productoADetallar!=NULL){
			datos.eliminarProducto(idProducto);
			return kMensajeOK;
		} else {
			return kMensajeError;
		}
}

const std::string Operador::altaAreaDeVision(const std::string& comandoDeOperacion){
	const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	datos.agregarAreaDeVision(new AreaDeVision(ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision));
	return kMensajeOK;
}

const std::string Operador::modificacionAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	AreaDeVision* AreaDeVisionAModificar = datos.getAreaDeVisionConId(idAreaDeVision);
	if (AreaDeVisionAModificar!=NULL){
		const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
		AreaDeVisionAModificar->setUbicacion(ubicacionAreaDeVision);
		const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
		AreaDeVisionAModificar->setTipoDeCapturador(tipoDeCapturadorAreaDeVision);
		return kMensajeOK;
	} else {
		return kMensajeError;
	}
}

const std::string Operador::bajaAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
		AreaDeVision* AreaDeVisionADetallar = datos.getAreaDeVisionConId(idAreaDeVision);
		if (AreaDeVisionADetallar!=NULL){
			datos.eliminarAreaDeVision(idAreaDeVision);
			return kMensajeOK;
		} else {
			return kMensajeError;
		}
}

const std::string Operador::stockGeneral() const{
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()>0){
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::stockAreaDeVision(const std::string& comandoDeOperacion)const{
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	AreaDeVision* areaDeVisionAInventariar = datos.getAreaDeVisionConId(idAreaDeVision);
	if (areaDeVisionAInventariar!=NULL){
		const std::list<Producto*>* productosDetectados= areaDeVisionAInventariar->getProductosDetectados();
		if (productosDetectados->size()>0){
			std::stringstream acumulador;
			for(std::list<Producto*>::const_iterator it=productosDetectados->begin(); it!=productosDetectados->end();++it)
				acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getStock()<< kMensajeDelimitadorCampos;
			return acumulador.str();
		}
	}
	return kMensajeError;
}

const std::string Operador::stockHistoricoProducto(const std::string& comandoDeOperacion)const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoAInventariar = datos.getProductoConId(idProducto);
	if (productoAInventariar!=NULL){
		const std::list<Stock*>* stockHistoricos = productoAInventariar->getStockHistorico();
		std::stringstream acumulador;
		for(std::list<Stock*>::const_iterator it=stockHistoricos->begin(); it!=stockHistoricos->end();++it)
			acumulador<< (*it)->getFecha() << kMensajeDelimitadorCampos <<(*it)->getCantidad()<< kMensajeDelimitadorCampos;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}


const std::string Operador::altaImagen(const std::string& comandoDeOperacion){
	const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,3);
	const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,4);
	protocolo.enviarMensaje(cliente, kMensajeOK);
	Imagen imagenRecibida = protocolo.recibirImagen(cliente,altoImagen,anchoImagen,tamanioImagen);
	if (cliente.estaConectado()){
		const unsigned long int idImagen = datos.agregarImagen(imagenRecibida);
		if (idImagen){
			std::stringstream acumulador;
			acumulador<< idImagen << kMensajeDelimitadorCampos;
			return acumulador.str();
		}
	}
	return kMensajeError;
}

const std::string Operador::enviarImagen(const std::string& comandoDeOperacion){
	const unsigned long int idImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeImagenConId(idImagen)){
		Imagen imagenSolicitada = datos.getImagenConId(idImagen);
		protocolo.enviarImagen(cliente,imagenSolicitada);
		return kRespuestaNula;
	}
	return kMensajeError;
}

const std::string Operador::bajaImagen(const std::string& comandoDeOperacion)const{
	const unsigned long int idImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeImagenConId(idImagen)){
		datos.eliminarImagen(idImagen);
		return kMensajeOK;
	}
	return kMensajeError;
}





