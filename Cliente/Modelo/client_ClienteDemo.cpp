/*
 * client_ClienteDemo.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: ale
 */

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_ClienteDemo.h"
#include "common_CommandParser.h"
#include "common_Imagen.h"
#include "common_Video.h"

#define kRespuestaOK "ok|\n"
#define kRespuestaERROR "error|\n"
#define TEMP_CARPETA "TEMP_clienteDemoImagenes"

using common::Imagen;
using common::Video;

ClienteDemo::ClienteDemo(const char* ip, const char* puerto) :
		client(ip,puerto){
	if (!client.estaConectado())
		std::cerr << "NO ESTOY CONECTADO\n";

	if (!this->identificarse())
		std::cerr << "NO ME IDENTIFICO BIEN!\n";

	//Creo la carpeta TEMP si no existe...
	mkdir(TEMP_CARPETA, S_IRWXU);
}

ClienteDemo::~ClienteDemo() {
	this->data.eliminarAreasDeVision();
	this->data.eliminarProductos();

	system( (std::string("rm -rf ")+ std::string(TEMP_CARPETA)).c_str());
}

bool ClienteDemo::identificarse(){
	if (this->client.estaConectado()){
		std::cerr << "Indetificandose...\n";
		protocolo.enviarMensaje(this->client, kIdentificacionCliente);//"Client|");
	}
	std::string r;
	if ((r = this->protocolo.recibirMensaje(this->client)) == kRespuestaOK)//"ok|\n")
		return true;
	std::cerr << r;
	return false;
}

void ClienteDemo::cerrarConeccion(){
	this->client.cerrarConeccion();
}

void ClienteDemo::actualizarIdImagenesDeProducto(Producto* prod){
	if (this->client.estaConectado()){
		std::stringstream ss;
		ss << kIndicadorComandoDetalleProducto << kMensajeDelimitadorCampos
				<< prod->getId() << kMensajeDelimitadorCampos;
		protocolo.enviarMensaje(this->client,ss.str());
	}else{
		return;
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == kRespuestaERROR || !this->client.estaConectado())//"error|\n")
		return;

	CommandParser parser;

	parser.tokenize(respuesta);

	//Obtengo la lista de ids vacia
	std::list<unsigned long int>* ids = prod->getIdsImagenes();

	unsigned int argum = 4;
	try{
		while (true){
			unsigned long int id = 0;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			if (ss.str() == "\n")
				return;
			ss >> id;

			//std::cerr << "agrego " << ss.str() << "\n";

			ids->push_back(id);
			++argum;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}

}

bool ClienteDemo::actualizarProductos(){
	mutex.bloquear();
	if (this->client.estaConectado()){
		std::stringstream ss;
		ss << kIndicadorComandoListarProductos << kMensajeDelimitadorCampos;
		protocolo.enviarMensaje(this->client, ss.str());
	}else{
		mutex.desbloquear();
		return false;
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == kRespuestaERROR || !this->client.estaConectado()){//"error|\n"){
		std::cerr << "error pidiendo productos\n";
		return false;
	}

	this->data.eliminarProductos();

	CommandParser parser;

	parser.tokenize(respuesta);

	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string nombre = parser.getParametro(argum+1);
			std::string descripcion = parser.getParametro(argum+2);

			unsigned long int idIcono;
			ss.clear();
			ss.flush();
			ss.str("");
			ss << parser.getParametro(argum+3);
			ss >> idIcono;
			Producto* nuevo = this->data.agregarProducto(nombre,descripcion,id, idIcono);

			std::cerr << "Agregando Producto:" << id << " "
					  << nombre << " " << descripcion
					  << " id Icono: " << idIcono << std::endl;

			this->actualizarIdImagenesDeProducto(nuevo);

			argum+=4;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	mutex.desbloquear();
	return true;
}

bool ClienteDemo::actualizarAreasDeVision(){
	mutex.bloquear();
	if (this->client.estaConectado()){
		std::stringstream ss;
		ss << kIndicadorComandoListarAreasDeVision << kMensajeDelimitadorCampos;
		protocolo.enviarMensaje(this->client,ss.str());
	}else{
		mutex.desbloquear();
		return false;
	}
	std::string respuesta = protocolo.recibirMensaje(this->client);

	if (respuesta == kRespuestaERROR || !this->client.estaConectado())//"error|\n")
		return false;

	this->data.eliminarAreasDeVision();

	CommandParser parser;

	parser.tokenize(respuesta);

	unsigned int argum = 1;
	try{
		while (true){
			unsigned long int id;
			std::stringstream ss;
			ss << parser.getParametro(argum);
			ss >> id;
			std::string ubicacion = parser.getParametro(argum+1);
			std::string tipo = parser.getParametro(argum+2);

			this->data.agregarAreaDeVision(ubicacion,tipo,id);

			std::cerr << "Agregando Area:" << id << " " << ubicacion << " " << tipo << std::endl;
			argum+=3;
		}
	}catch (std::exception& e){
		//std::cout << "ya se manejar excepciones:)\n";
		//std::cout << e.what();
	}
	mutex.desbloquear();
	return true;
}

const std::list<AreaDeVision*>* ClienteDemo::getAreasDeVision() {
	mutex.bloquear();
	const std::list<AreaDeVision*>* aux = data.getAreasDeVision();
	mutex.desbloquear();
	return aux;
}

const std::list<Producto*>* ClienteDemo::getProductos() {
	mutex.bloquear();
	const std::list<Producto*>* aux = data.getProductos();
	mutex.desbloquear();
	return aux;
}

std::string ClienteDemo::getImagenConId(unsigned long int id){
	std::cerr << "GET IMAGEN MUTEX\n";
	mutex.bloquear();
	if (this->client.estaConectado()){
		std::stringstream s;
		s << kIndicadorComandoSolicitudImagen << kMensajeDelimitadorCampos
				<< id << kMensajeDelimitadorCampos;
		protocolo.enviarMensaje(this->client,s.str());
	}else{
		mutex.desbloquear();
		return "";
	}

	std::string respuestaDatosImagen = protocolo.recibirMensaje(this->client);
	std::cerr << "RESPUESTA A R|" << id << "|\n";
	std::cerr << respuestaDatosImagen << "\n";
	if (respuestaDatosImagen == kRespuestaERROR || !this->client.estaConectado()){//"error|\n")
		mutex.desbloquear();
		return "";
	}

	CommandParser parser;
	parser.tokenize(respuestaDatosImagen);

	unsigned int altoImagen;
	unsigned int anchoImagen;
	unsigned long int tamanioImagen;
	std::stringstream ss;
	try{
		ss << parser.getParametro(2);
		ss >> altoImagen;
		ss.clear();
		ss.str("");

		ss << parser.getParametro(3);
		ss >> anchoImagen;
		ss.clear();
		ss.str("");

		ss << parser.getParametro(4);
		ss >> tamanioImagen;
		ss.clear();
		ss.str("");
	}catch (std::exception& e){
		protocolo.enviarMensaje(this->client, kMensajeError);
		mutex.desbloquear();
		return "";
	}
	protocolo.enviarMensaje(this->client, kMensajeOK);

	std::cerr << "Recibiendo IMAGEN...\n";
	Imagen img = protocolo.recibirImagen(this->client,altoImagen,anchoImagen,tamanioImagen);
	std::cerr << "IMAGEN recibida\n";

	if (!img.esValida()){
		std::cerr << "No recibio bien imagen\n";
		mutex.desbloquear();
		return "";
	}

	/*Guardo la imagen en la carpeta temp*/
	std::stringstream sss;
	sss << TEMP_CARPETA << "/" << id << ".jpg";
	std::string ruta(sss.str());

	img.guardarEnArchivo(ruta);

	mutex.desbloquear();
	return ruta;
}

void ClienteDemo::enviarFoto(const char* comando, unsigned long int idArea, std::string& fecha,Imagen& img){
	std::stringstream ss;

	ss << comando << idArea << kMensajeDelimitadorCampos << fecha << kMensajeDelimitadorCampos;
	std::cerr << "ENVIANDO: " << ss.str() << "\n";


	this->protocolo.enviarMensaje(this->client,ss.str());

	if (this->protocolo.recibirMensaje(this->client) == kRespuestaOK){
		this->protocolo.enviarImagen(this->client, img);
	}
	else{
		std::cerr << "ERROR AL ENVIAR LA IMAGEN\n";
		return;
	}
	if (this->protocolo.recibirMensaje(this->client) == kRespuestaOK){
		std::cerr << "TODO PIOLA\n";
	}else{
		std::cerr << "NO LLEGO NADA\n";
	}
}

void ClienteDemo::enviarFotoTemplateMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	mutex.bloquear();
	Imagen img(rutaDeImagen);
	std::stringstream ss;
	ss << kIndicadorComandoFotoTemplateMatching << kMensajeDelimitadorCampos;

	this->enviarFoto(ss.str().c_str(),idArea,fecha,img);
	mutex.desbloquear();
}

void ClienteDemo::enviarFotoFeatureMatching(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen){
	mutex.bloquear();
	Imagen img(rutaDeImagen);
	std::stringstream ss;
	ss << kIndicadorComandoFotoFeatureMatching << kMensajeDelimitadorCampos;

	this->enviarFoto(ss.str().c_str(),idArea,fecha,img);
	mutex.desbloquear();
}

void ClienteDemo::enviarVideo(const char* comando, unsigned long int idArea, std::string& fechaInicio,int intervaloSegs, Video& vid){
	std::stringstream ss;

	std::list<Imagen> frames;
	std::list<std::string> fechas;

	/*Saco los frames cada 60 segundos y sus fechas correspondientes*/
	vid.capturasPeriodicasVideo(frames,fechas,fechaInicio,intervaloSegs);

	std::list<Imagen>::iterator itIm;
	std::list<std::string>::iterator itStr;

	std::cerr << "Enviando frames del video\n";

	for (itIm=frames.begin(), itStr=fechas.begin();
			itIm != frames.end(); ++itIm, ++itStr){
		std::cerr << "Fecha y hora del frame: " << *itStr << "\n";
		this->enviarFoto(comando,idArea,*itStr,*itIm);
	}
}

void ClienteDemo::enviarVideoTemplateMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo,int intervaloSegs){
	std::cerr << "ENVIAR VIDEO MUTEX\n";
	mutex.bloquear();
	Video vid(rutaDeVideo);
	std::stringstream ss;
	ss << kIndicadorComandoFotoTemplateMatching << kMensajeDelimitadorCampos;
	this->enviarVideo(ss.str().c_str(),idArea,fechaInicio,intervaloSegs,vid);
	mutex.desbloquear();
	std::cerr << "ENVIAR VIDEO DESBLOQUEO MUTEX\n";
}

void ClienteDemo::enviarVideoFeatureMatching(unsigned long int idArea, std::string& fechaInicio,std::string& rutaDeVideo,int intervaloSegs){
	mutex.bloquear();
	Video vid(rutaDeVideo);
	std::stringstream ss;
	ss << kIndicadorComandoFotoFeatureMatching << kMensajeDelimitadorCampos;
	this->enviarVideo(ss.str().c_str(),idArea,fechaInicio,intervaloSegs,vid);
	mutex.desbloquear();
}
