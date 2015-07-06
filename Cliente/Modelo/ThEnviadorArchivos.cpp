/*
 * ThEnviadorArchivos.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: ale
 */

#include "ThEnviadorArchivos.h"

ThEnviadorArchivos::ThEnviadorArchivos(ClienteDemo& cliente) : cliente(cliente){
	this->estoyVivo = false;

}

ThEnviadorArchivos::~ThEnviadorArchivos() {
	// TODO Auto-generated destructor stub
}

void ThEnviadorArchivos::agregarImagen(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen, int matching){
	struct itemEnvio* item = new struct itemEnvio;
	item->idArea = idArea;
	item->fecha = fecha;
	item->rutaDeImagen = rutaDeImagen;
	item->matching = matching;

	mutex.bloquear();
	this->colaImagenes.push(item);
	mutex.desbloquear();
}

void ThEnviadorArchivos::agregarVideo(unsigned long int idArea, std::string& fecha,std::string& rutaDeVideo, int matching){
	struct itemEnvio* item = new struct itemEnvio;
	item->idArea = idArea;
	item->fecha = fecha;
	item->rutaDeImagen = rutaDeVideo;
	item->matching = matching;

	std::cerr << "VOY A ENCOLAR VIDEO (ANTES DEL MUTEX)\n";
	mutex.bloquear();
	std::cerr << "ENCOLO VIDEO (PASADO EL MUTEX)\n";
	this->colaVideos.push(item);
	mutex.desbloquear();
}

void ThEnviadorArchivos::run(){
	std::cerr << "INICIANDO ENVIADOR DE ARCHIVOS\n";
	this->estoyVivo = true;

	//Aunque quiera matar el hilo, que espere a que termine de enviar las cosas...
	while (this->estoyVivo || !colaImagenes.empty() || !colaVideos.empty()){
		sleep(5);

		//while hayan cosas en cola imagnees--> enviarlas
		while (!colaImagenes.empty()){
			mutex.bloquear();
			struct itemEnvio*  item = colaImagenes.front();
			colaImagenes.pop();
			mutex.desbloquear();
			if (item->matching == TEMPLATE_MATCHING)
				cliente.enviarFotoTemplateMatching(item->idArea,item->fecha,item->rutaDeImagen);
			else
				cliente.enviarFotoFeatureMatching(item->idArea,item->fecha,item->rutaDeImagen);

			delete item;
		}

		//while hayan cosas en cola videos--> enviarlas
		while (!colaVideos.empty()){
			mutex.bloquear();
			std::cerr << "DESENCOLO VIDEO PASADO EL MUTEX\n";
			struct itemEnvio*  item = colaVideos.front();
			colaVideos.pop();
			mutex.desbloquear();
			if (item->matching == TEMPLATE_MATCHING)
				cliente.enviarVideoTemplateMatching(item->idArea,item->fecha,item->rutaDeImagen);
			else
				cliente.enviarVideoFeatureMatching(item->idArea,item->fecha,item->rutaDeImagen);

			delete item;
		}
		//Si no hay mas cosas en ninguna de los dos que se duerma 10 segundos (al inicio del bucle) y vuelva a empezar
	}
}

