/*
 * ThActualizador.h
 *
 *  Created on: Jul 6, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_THACTUALIZADOR_H_
#define CLIENTE_MODELO_THACTUALIZADOR_H_

#include "client_ClienteDemo.h"
#include "common_Thread.h"

class ModeloObservable;

class ThActualizador: public Thread {

	bool estoyVivo;
	ModeloObservable* modelo;
	Mutex* mutex;
	pthread_cond_t cond;
	struct timespec abstime;

public:
	ThActualizador();
	virtual ~ThActualizador();

	void setParametros(ModeloObservable* modelo, Mutex* mutex);
	void run();

	void matar(){
		pthread_cond_broadcast(&cond);
		this->estoyVivo=false;

	}
};

#endif /* CLIENTE_MODELO_THACTUALIZADOR_H_ */
