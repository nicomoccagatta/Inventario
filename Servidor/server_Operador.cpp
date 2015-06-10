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
    if (this->cliente.estaConectado())
      this->protocolo.enviarMensaje(this->cliente,
                                    this->realizarOperacion(mensajeRecibido));
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
	  }
    }
  return kMensajeError;
}

const std::string Operador::listarProductos()const{
	const std::list<Producto*>* listaProductos = datos.getProductos();
	if (listaProductos->size()==0){
		return kMensajeError;
	} else {
		std::stringstream acumulador;
		for(std::list<Producto*>::const_iterator it=listaProductos->begin(); it!=listaProductos->end();++it)
			acumulador<< (*it)->getId() << kMensajeDelimitadorCampos <<(*it)->getNombre() << kMensajeDelimitadorCampos <<(*it)->getDescripcion() << kMensajeDelimitadorCampos;
		return acumulador.str();
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

const std::string Operador::detallarProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	Producto* productoADetallar = datos.getProductoConId(idProducto);
	if (productoADetallar!=NULL){
		std::stringstream acumulador;
		acumulador << productoADetallar->getNombre() << kMensajeDelimitadorCampos << productoADetallar->getDescripcion() << kMensajeDelimitadorCampos ;
		return acumulador.str();
	} else {
		return kMensajeError;
	}
}

const std::string Operador::extraerArgumentoDeComando(
        const std::string& comandoDeOperacion, const size_t numeroArgumento){
	std::stringstream parseador(comandoDeOperacion);
	std::string argumento;
	for (size_t i =0;i<numeroArgumento;++i)
		  std::getline(parseador, argumento, '|');
	return argumento;
}

const unsigned long int Operador::extraerArgumentoNumericoDeComando(
    const std::string& comandoDeOperacion, const size_t numeroDeParametro) {
  std::stringstream parseador(extraerArgumentoDeComando(comandoDeOperacion,numeroDeParametro));
  unsigned long int argumentoNumerico=0;
  parseador >> argumentoNumerico;
  return argumentoNumerico;
}



