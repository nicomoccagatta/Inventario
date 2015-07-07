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

/*
 * La clase es un Thread  que cada cierto intervalo de tiempo, o hasta que
 * se broadcastee la condicion variable actualiza los Productos y AreasDeVision
 * mediante el ModeloObservable.
 */
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
