#include <string>
#include <time.h>
#include "client_Cliente.h"

using common::Protocolo;
using client::SocketCliente;
using client::Cliente;

using namespace cv;

// Se instancia el objeto y se intenta conectar al servidor con al direccion
// indicada.
Cliente::Cliente(const std::string& direccionServidor, Protocolo protocolo)
    : skt(obtenerDireccionIP(direccionServidor),
          obtenerPuerto(direccionServidor)),
      protocolo(protocolo) {}

Cliente::~Cliente() {}

const std::string Cliente::recibirMensaje() {
  if (this->skt.estaConectado())
    return this->protocolo.recibirMensaje(this->skt);
  else
    return "";
}

void Cliente::enviarMensaje(const std::string& mensaje) {
  if (this->skt.estaConectado())
    this->protocolo.enviarMensaje(this->skt, mensaje);
}

bool Cliente::conectado() const { return this->skt.estaConectado(); }

void Cliente::cerrarConeccion() { this->skt.cerrarConeccion(); }


//recibe una imagen usando el protocolo. al salir debe chequearse que el socket sigue avierto o que la imagen es valida.
Imagen  Cliente::recibirImagen(const std::string& comando){
	enviarMensaje(comando);
	if (skt.estaConectado()){
		std::string mensajeDatosImagen = recibirMensaje();
		if (mensajeDatosImagen != (kMensajeError+protocolo.getFinalizadorDeMensaje())){
			const unsigned int altoImagen = Protocolo::extraerArgumentoNumericoDeComando(mensajeDatosImagen,2);
			const unsigned int anchoImagen = Protocolo::extraerArgumentoNumericoDeComando(mensajeDatosImagen,3);
			const unsigned long int tamanioImagen = Protocolo::extraerArgumentoNumericoDeComando(mensajeDatosImagen,4);
			protocolo.enviarMensaje(skt, kMensajeOK);
			return protocolo.recibirImagen(skt,altoImagen,anchoImagen,tamanioImagen);
		}
	}
	return Imagen("");
}

void Cliente::enviarImagen(const Imagen& imagenAEnviar){
	protocolo.enviarImagen(skt,imagenAEnviar);
}

const size_t Cliente::realizarConsultas() {
  // seguira la ejecucion solo si se pudo setear y conectar al servidor
  // correctamente.
  if (skt.estaConectado()) {
	  identificarse();
    std::string mensajeAEnviar="";
    while (skt.estaConectado()) {
      getline(std::cin, mensajeAEnviar);
      if (strcmp(mensajeAEnviar.c_str(), kMensajeFinDeSesion) != 0) {

    	//protocolo.enviarMensaje(this->skt,mensajeAEnviar);
    	//featureMatching(mensajeAEnviar,Imagen("aInventariar.jpg"));
    	enviarImagen(Imagen(mensajeAEnviar));
    	if (skt.estaConectado()){
    		std::string mensajeRecibido = recibirMensaje();
    		std::cerr << "RESPUESTA FINAL: " << mensajeRecibido <<"\n";
    	} else {
    		return 1;
    	}
      } else {
        // si el usuario ingreso el mensaje de finalizacion cierro la
        // coneccion y la aplicacion.
        cerrarConeccion();
      }
    }
    cerrarConeccion();
    return kRetornoOK;
  }
  return kRetornoError;
}

void Cliente::templateMatching(const std::string& idAreaDeVision,const Imagen& imagenAEnviar){
	time_t hora;
	time (&hora);
	std::string fecha(asctime(localtime(&hora)));
	fecha.erase (std::remove(fecha.begin(), fecha.end(), '\n'), fecha.end());
	std::stringstream mensajeInicial;
	mensajeInicial<<kIndicadorComandoFotoTemplateMatching<<kMensajeDelimitadorCampos<<idAreaDeVision<<kMensajeDelimitadorCampos<<fecha<<kMensajeDelimitadorCampos;

	std::cerr << "ENVIANDO MSGE INICIAL: " << mensajeInicial.str() << "\n";
	enviarMensaje(mensajeInicial.str());
	std::string mensajeRecibido = recibirMensaje();
	std::cerr << "RECIBIDO MSGE INICIAL: " << mensajeRecibido << "\n";
	if (skt.estaConectado() && mensajeRecibido==kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		std::cerr << "ENVIANDO IMAGEN\n";
		enviarImagen(imagenAEnviar);
	}
}

void Cliente::featureMatching(const std::string& idAreaDeVision,const Imagen& imagenAEnviar){
	time_t hora;
	time (&hora);
	std::string fecha(asctime(localtime(&hora)));
	fecha.erase (std::remove(fecha.begin(), fecha.end(), '\n'), fecha.end());
	std::stringstream mensajeInicial;
	mensajeInicial<<kIndicadorComandoFotoFeatureMatching<<kMensajeDelimitadorCampos<<idAreaDeVision<<kMensajeDelimitadorCampos<<fecha<<kMensajeDelimitadorCampos;

	std::cerr << "ENVIANDO MSGE INICIAL: " << mensajeInicial.str() << "\n";
	enviarMensaje(mensajeInicial.str());
	std::string mensajeRecibido = recibirMensaje();
	std::cerr << "RECIBIDO MSGE INICIAL: " << mensajeRecibido << "\n";
	if (skt.estaConectado() && mensajeRecibido==kMensajeOK+protocolo.getFinalizadorDeMensaje()){
		std::cerr << "ENVIANDO IMAGEN\n";
		enviarImagen(imagenAEnviar);
	}
}

const std::string Cliente::obtenerDireccionIP(
    const std::string& direccionServidor) {
  std::stringstream parseadorDeArgumentos(direccionServidor);
  std::string direccionIP;
  getline(parseadorDeArgumentos, direccionIP, kSeparadorDireccion);
  return direccionIP;
}

const std::string Cliente::obtenerPuerto(const std::string& direccionServidor) {
  std::stringstream parseadorDeArgumentos(direccionServidor);
  std::string direccionIP;
  getline(parseadorDeArgumentos, direccionIP, kSeparadorDireccion);
  std::string puerto;
  parseadorDeArgumentos >> puerto;
  return puerto;
}

void Cliente::identificarse(){
	std::string respuestaServidor("");
	while (respuestaServidor != (kMensajeOK+protocolo.getFinalizadorDeMensaje())){
		protocolo.enviarMensaje(skt,"Client|");
		respuestaServidor=protocolo.recibirMensaje(skt);
		std::cerr << "IDENTIFICACION: " <<respuestaServidor<<std::endl;
	}
}
