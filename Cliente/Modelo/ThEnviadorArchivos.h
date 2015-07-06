/*
 * ThEnviadorArchivos.h
 *
 *  Created on: Jul 5, 2015
 *      Author: ale
 */

#ifndef CLIENTE_MODELO_THENVIADORARCHIVOS_H_
#define CLIENTE_MODELO_THENVIADORARCHIVOS_H_

#include <queue>
#include "common_Thread.h"
#include "common_Mutex.h"
#include "client_ClienteDemo.h"

#define FEATURE_MATCHING 1
#define TEMPLATE_MATCHING 2

struct itemEnvio{
	unsigned long int idArea;
	std::string fecha;
	std::string rutaDeImagen;
	int matching;
};

class ThEnviadorArchivos: public Thread {

	bool estoyVivo;
	common::Mutex mutex;
	ClienteDemo cliente;

	std::queue<itemEnvio*> colaImagenes;
	std::queue<itemEnvio*> colaVideos;

public:
	ThEnviadorArchivos(ClienteDemo& cliente);
	virtual ~ThEnviadorArchivos();

	void agregarImagen(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen, int matching);
	void agregarVideo(unsigned long int idArea, std::string& fecha,std::string& rutaDeVideo, int matching);

	void matar(){
		this->estoyVivo=false;
	}
	void run();
};

#endif /* CLIENTE_MODELO_THENVIADORARCHIVOS_H_ */
