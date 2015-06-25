#include "server_Operador.h"
#include <list>
#include <string>

using server::Operador;
using common::Protocolo;
using common::Socket;

Operador::Operador(Socket& cliente, const Protocolo& protocolo, MonitorBaseDeDatos& datos)
    : cliente(cliente),
      protocolo(protocolo),
      datos(datos),
      realizarOperaciones(true),
	  identificadorUsuario(Operador::identificarUsuario(cliente,protocolo)){}

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
		case kIndicadorComandoListarProductos: return listarProductos();
		case kIndicadorComandoListarAreasDeVision:return listarAreasDeVision();
		case kIndicadorComandoDetalleProducto:return detallarProducto(comandoDeOperacion);
		case kIndicadorComandoSolicitudImagen:return enviarImagen(comandoDeOperacion);
		default :return realizarOperacionEspecifica(comandoDeOperacion);
	  }
    }
  return kMensajeError;
}

const std::string Operador::realizarOperacionEspecifica(std::string& comandoDeOperacion){
	if (identificadorUsuario==(kIdentificacionAdministrador+protocolo.getFinalizadorDeMensaje()))
		switch (comandoDeOperacion[0]) {
			case kIndicadorComandoAltaProducto:return altaProducto(comandoDeOperacion);
			case kIndicadorComandoModificacionProducto:return modificacionProducto(comandoDeOperacion);
			case kIndicadorComandoBajaProducto: return bajaProducto(comandoDeOperacion);
			case kIndicadorComandoAltaAreaDeVision: return altaAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoModificacionAreaDeVision:return modificacionAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoBajaAreaDeVision: return bajaAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoStockGeneral: return stockGeneral();
			case kIndicadorComandoStockAreaDeVision: return stockAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoStockHistoricoProducto: return stockHistoricoProducto(comandoDeOperacion);
			case kIndicadorComandoAltaImagen: return altaImagen(comandoDeOperacion);
		}
	if (identificadorUsuario==(kIdentificacionCliente+protocolo.getFinalizadorDeMensaje()))
		switch (comandoDeOperacion[0]) {
			case kIndicadorComandoFotoTemplateMatching:return actualizarStockAreaDeVision(comandoDeOperacion);
			case kIndicadorComandoFotoFeatureMatching:return actualizarStockAreaDeVision(comandoDeOperacion);
		}
	return kMensajeError;
}

const std::string Operador::listarProductos()const{
	return datos.obtenerListadoProductos();
}

const std::string Operador::listarAreasDeVision()const{
	return datos.obtenerListadoAreasDeVision();
}

const std::string Operador::detallarProducto(const std::string& comandoDeOperacion) const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	return datos.obtenerDetalleProducto(idProducto);
}

const std::string Operador::enviarImagen(const std::string& comandoDeOperacion){
	const unsigned long int idImagen = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeImagen(idImagen)){
		Imagen imagenSolicitada = datos.obtenerImagen(idImagen);
		protocolo.enviarImagen(cliente,imagenSolicitada);
		return kRespuestaNula;
	}
	return kMensajeError;
}


const Imagen Operador::recibirImagen(const std::string& informacionDeImagen){
	const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,2);
	const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,3);
	const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(informacionDeImagen,4);
	protocolo.enviarMensaje(cliente, kMensajeOK);
	return protocolo.recibirImagen(cliente,altoImagen,anchoImagen,tamanioImagen);
}


const std::string Operador::altaProducto(const std::string& comandoDeOperacion){
	const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,4);
	std::stringstream parseador;
	parseador << datos.altaProducto(nombreProducto,descripcionProducto,idIcono);
	return (parseador.str() + kMensajeDelimitadorCampos);
}

const std::string Operador::modificacionProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	const std::string nombreProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const std::string descripcionProducto = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
	const unsigned long int idIcono = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,5);
	bool existenTodasLasImagenes= datos.existeImagen(idIcono);
	int numeroDeArgumento=6;
	std::list<unsigned long int> nuevaListaDeIdsImagenes;
	unsigned long int idImagen;
	while ((idImagen= Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,numeroDeArgumento))&& existenTodasLasImagenes){
		if ((idImagen) && (existenTodasLasImagenes=datos.existeImagen(idImagen)))
			nuevaListaDeIdsImagenes.push_back(idImagen);
		++numeroDeArgumento;
	}
	if (datos.existeProducto(idProducto) && existenTodasLasImagenes){
		datos.modificarProducto(idProducto,nombreProducto,descripcionProducto,idIcono,nuevaListaDeIdsImagenes);
		return kMensajeOK;
	}
	return kMensajeError;
}

const std::string Operador::bajaProducto(const std::string& comandoDeOperacion){
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeProducto(idProducto)){
		datos.bajaProducto(idProducto);
		return kMensajeOK;
	} else {
		return kMensajeError;
	}
}

const std::string Operador::altaAreaDeVision(const std::string& comandoDeOperacion){
	const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,2);
	const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	std::stringstream parseador;
	parseador << datos.altaAreaDeVision(ubicacionAreaDeVision,tipoDeCapturadorAreaDeVision);
	return (parseador.str() + kMensajeDelimitadorCampos);
}

const std::string Operador::modificacionAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	const std::string ubicacionAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const std::string tipoDeCapturadorAreaDeVision = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,4);
	if (datos.existeAreaDeVision(idAreaDeVision)){

		return kMensajeOK;
	} else {
		return kMensajeError;
	}
}

const std::string Operador::bajaAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeAreaDeVision(idAreaDeVision)){
		datos.bajaAreaDeVision(idAreaDeVision);
		return kMensajeOK;
	}
	return kMensajeError;
}

const std::string Operador::stockGeneral() const{
	return datos.obtenerStockGeneralProductos();
}

const std::string Operador::stockAreaDeVision(const std::string& comandoDeOperacion){
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	return datos.obtenerStockAreaDeVision(idAreaDeVision);
}

const std::string Operador::stockHistoricoProducto(const std::string& comandoDeOperacion)const{
	const unsigned long int idProducto = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	return datos.obtenerStockHistoricoProducto(idProducto);
}


const std::string Operador::altaImagen(const std::string& comandoDeOperacion){
	Imagen imagenRecibida = recibirImagen(comandoDeOperacion);
	if (cliente.estaConectado()){
		const unsigned long int idImagen = datos.altaImagen(imagenRecibida);
		if (idImagen){
			std::stringstream acumulador;
			acumulador<< idImagen << kMensajeDelimitadorCampos;
			return acumulador.str();
		}
	}
	return kMensajeError;
}

const std::string Operador::actualizarStockAreaDeVision(const std::string& comandoDeOperacion){
	const std::string tipoDeDeteccion = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,1);
	const std::string fechaDeCaptura = Protocolo::extraerArgumentoDeComando(comandoDeOperacion,3);
	const unsigned long int idAreaDeVision = Protocolo::extraerArgumentoNumericoDeComando(comandoDeOperacion,2);
	if (datos.existeAreaDeVision(idAreaDeVision)){
		protocolo.enviarMensaje(cliente, kMensajeOK);
		std::string mensajeRecibido = this->protocolo.recibirMensaje(this->cliente);
		Imagen imagenRecibida = recibirImagen(mensajeRecibido);
		if (cliente.estaConectado() && imagenRecibida.esValida()){
			protocolo.enviarMensaje(cliente, kMensajeOK);
			datos.actualizarDeteccionAreaDeVision(idAreaDeVision,imagenRecibida,fechaDeCaptura,tipoDeDeteccion);
			return kRespuestaNula;
		}
	}
	return kMensajeError;
}

const std::string Operador::identificarUsuario(Socket& cliente,const Protocolo& protocolo){
	bool usuarioIdentificado=false;
	while (!usuarioIdentificado){
		const std::string mensajeIdentificacion = protocolo.recibirMensaje(cliente);
		if (mensajeIdentificacion==(kIdentificacionAdministrador+protocolo.getFinalizadorDeMensaje()) || mensajeIdentificacion==(kIdentificacionCliente+protocolo.getFinalizadorDeMensaje())){
			protocolo.enviarMensaje(cliente,kMensajeOK);
			return mensajeIdentificacion;
		} else {
			protocolo.enviarMensaje(cliente,kMensajeError);
		}
	}
	return "";
}
