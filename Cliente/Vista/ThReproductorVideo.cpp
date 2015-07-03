/*
 * ThReproductorVideo.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: ale
 */

#include <iostream>
#include <unistd.h>

#include "ThReproductorVideo.h"

ThReproductorVideo::ThReproductorVideo(Gtk::VBox* box){
	this->reproduciendo = true;
	this->box = box;
	this->fps = 1;
	this->activo = -1;
	this->vivo = false;
	this->cond = 0;
}

ThReproductorVideo::~ThReproductorVideo() {

}

void ThReproductorVideo::setearFrames(std::vector<Gtk::Image*>& frames){
	this->frames = frames;
	activo=-1;

}

void ThReproductorVideo::setFPS(double fps){
	this->fps=fps;
}

void ThReproductorVideo::pausa(){
	if(this->activo > 0)
		this->reproduciendo = false;
}

void ThReproductorVideo::sacarImagenPausada(){
	if(reproduciendo==false && activo!=-1){
		std::cerr << "SACO IMAGEN PAUSADA: " << activo << "\n";
		box->remove(*frames[activo]);
	}
	activo=-1;
}

void ThReproductorVideo::run(){
	std::cerr << "REPRODUCIENDO\n";
	this->vivo = true;

	while (this->vivo){

		//Cuando apreto play retoma desde aca
		mutex.bloquear();
		pthread_cond_wait(cond, &(mutex.mutex)); //BLOQUEA

		//Si se habia pausado remuevo el frame que deje puesto
		if(reproduciendo==false && activo!=-1){
			std::cerr << "SIGO REPRODUCIENDO DESDE: " << activo << "\n";
			box->remove(*frames[activo]);
		}
		this->reproduciendo = true;

		int it;

		if(activo > 0)
			it = activo; //sigue desde el que se habia pausado
		else
			it = 0;

		std::cerr << "ACTIVO ANTES DEL FOR = " << activo << std::endl;

		for (;it<frames.size() && reproduciendo==true && vivo==true;++it){
			std::cerr << "IT = " << it << std::endl;
			//std::cerr << "AGREGO\n";

			box->pack_start(*frames[it]);

			activo=it;

			frames[it]->show();

			usleep(1000000/fps); //periodo

			//std::cerr << "REMUEVO\n";

			box->remove(*frames[it]);
		}
		std::cerr << "ACTIVO DESP DEL FOR = " << activo << std::endl;
		//Si se termino, lo dejo en estado inicial
		if (activo == frames.size()-1)
			activo=-1;

		//Si se pauso, dejo la imagen en la que se habia pausado
		if(reproduciendo==false && activo!=-1){
			std::cerr << "SE QUEDA PAUSADO EN: " << activo << "\n";
			box->pack_start(*frames[activo]);
		}

		mutex.desbloquear();
	}
}
