/*
 * ThActualizador.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: ale
 */

#include "ThActualizador.h"
#include "client_ModeloObservable.h"

ThActualizador::ThActualizador() :
	modelo(0), mutex(0) {
	//pthread_cond_init(&cond,NULL);
	estoyVivo = false;
}

ThActualizador::~ThActualizador() {}

void ThActualizador::setParametros(ModeloObservable* modelo, Mutex* mutex){
	this->modelo = modelo;
	this->mutex = mutex;
}

void ThActualizador::run(){
	std::cerr << "INICIANDO ACTUALIZADOR DE DATA\n";
	estoyVivo = true;
	while (estoyVivo){
		if (!modelo->actualizarDatos())
			break;
		//mutex->bloquear();
		std::cerr << "10 SEGUNDOS!!\n";
		//mutex->cond_timedwait(&cond,10);
		sleep(10);
		std::cerr << "PASARON LO 10!!!\n";
		//mutex->desbloquear();

		//sleep(30);
	}
}

