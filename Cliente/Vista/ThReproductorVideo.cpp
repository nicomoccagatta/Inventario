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
	//this->laImagen = laImagen;

}

ThReproductorVideo::~ThReproductorVideo() {
	// TODO Auto-generated destructor stub
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

void ThReproductorVideo::run(){
	std::cerr << "REPRODUCIENDO\n";
	this->vivo = true;

	//Si se habia pausado
	if(reproduciendo==false && activo!=-1){
		std::cerr << "SIGO REPRODUCIENDO DESDE: " << activo << "\n";
		box->remove(*frames[activo]);
	}
	this->reproduciendo = true;

	int it;

	if(activo > 0)
		it = activo;
	else
		it = 0;

	std::cerr << "ACTIVO ANTES DEL FOR = " << activo << std::endl;

	for (;it<frames.size() && reproduciendo==true;++it){
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
	if (activo == frames.size()-1)
		activo=-1;

	//Si se pauso, dejo la imagen en la que se habia pausado
	if(reproduciendo==false && activo!=-1){
		std::cerr << "SE QUEDA PAUSADO EN: " << activo << "\n";
		box->pack_start(*frames[activo]);
	}
}
