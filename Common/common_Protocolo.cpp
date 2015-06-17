#include "common_Protocolo.h"
#include <string>
#include <cstring>
#include <string.h>

using common::Protocolo;
using common::Socket;
using common::Imagen;


Protocolo::Protocolo(const std::string& finalizador)
    : finalizadorDeMensaje(finalizador) {}

Protocolo::~Protocolo() {}

const std::string Protocolo::getFinalizadorDeMensaje() const {
  return this->finalizadorDeMensaje;
}

void Protocolo::setFinalizadorMensaje(const std::string& finalizador) {
  this->finalizadorDeMensaje = finalizador;
}

const std::string Protocolo::recibirMensaje(Socket& skt) const {
  return this->protocolizarMensaje(
      skt.recibirMensajeFinalizado(this->finalizadorDeMensaje));
}
void Protocolo::enviarMensaje(Socket& skt, std::string mensaje) const {
  skt.enviarMensaje(this->protocolizarMensaje(mensaje));
}

const std::string Protocolo::protocolizarMensaje(std::string mensaje) const {
  if (mensaje == "") return finalizadorDeMensaje;
  // si el mensaje no termina con el finalizador correspondiente lo agrego.
  if (mensaje[mensaje.length() - 1] != this->getFinalizadorDeMensaje()[0]) {
    return mensaje.append(this->getFinalizadorDeMensaje());
  }
  return mensaje;
}

//Recibe la imagen enviada por red. Debe chequearse a su salida que el socket siga abierto ya que si no significa que fallo la transmision.
Imagen Protocolo::recibirImagen(Socket& socket,const unsigned int altoImagen,const unsigned int anchoImagen, const unsigned long int tamanioImagen) const{
	std::cerr << "RECIBIENDO BYTES IMAGEN\n";
	const unsigned char* datosImagen=socket.recibirBytesDinamicos(tamanioImagen);
	if (socket.estaConectado()){
		Imagen imagenARetornar (altoImagen,anchoImagen,datosImagen);
		//imagenARetornar.mostrarImagen();
		delete[] datosImagen;
		std::cerr << "SIGO CONECTADO\n";
		return imagenARetornar;
	}
	delete[] datosImagen;
	return Imagen("");
}

void Protocolo::enviarImagen(Socket& socket,const Imagen& imagenAEnviar) const{
	const unsigned int altoImagen=imagenAEnviar.getAlto();
	const unsigned int anchoImagen=imagenAEnviar.getAncho();
	const unsigned int tamanioImagen=imagenAEnviar.getTamanio();
	std::stringstream parseadorMensaje;
	parseadorMensaje  << kIndicadorComandoAltaImagen << kMensajeDelimitadorCampos << altoImagen << kMensajeDelimitadorCampos << anchoImagen << kMensajeDelimitadorCampos << tamanioImagen<<kMensajeDelimitadorCampos<<finalizadorDeMensaje;
	enviarMensaje(socket,parseadorMensaje.str());
	std::string respuesta =recibirMensaje(socket);
	if (respuesta==kMensajeOK+finalizadorDeMensaje){
		std::cerr << "ENVIANDO BYTES IMAGEN\n";
		const unsigned char* const datosImagen= imagenAEnviar.obtenerBytesDinamicos();
		socket.enviarBytes(datosImagen,tamanioImagen);
		delete[] datosImagen;
	}
}

const std::string Protocolo::extraerArgumentoDeComando(
        const std::string& comandoDeOperacion, const size_t numeroArgumento){
	std::stringstream parseador(comandoDeOperacion);
	std::string argumento;
	for (size_t i =0;i<numeroArgumento;++i)
		  std::getline(parseador, argumento, '|');
	return argumento;
}

const unsigned long int Protocolo::extraerArgumentoNumericoDeComando(
    const std::string& comandoDeOperacion, const size_t numeroDeParametro) {
  std::stringstream parseador(extraerArgumentoDeComando(comandoDeOperacion,numeroDeParametro));
  unsigned long int argumentoNumerico=0;
  parseador >> argumentoNumerico;
  return argumentoNumerico;
}
