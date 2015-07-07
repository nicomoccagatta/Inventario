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

/*
 * Estructura utilizada para completar los datos de envio y ser encolada.
 */
struct itemEnvio{
	unsigned long int idArea;
	std::string fecha;
	std::string rutaDeImagen;
	int matching;
	int intervaloSegs;
};

/*
 * La clase es un Thread que se ocupa de enviar las imagenes y videos
 * al Servidor mediente un ClienteDemo.
 */
class ThEnviadorArchivos: public Thread {
	bool estoyVivo;
	common::Mutex mutex;
	ClienteDemo* cliente;

	std::queue<itemEnvio*> colaImagenes;
	std::queue<itemEnvio*> colaVideos;

public:
	ThEnviadorArchivos(ClienteDemo* cliente);
	virtual ~ThEnviadorArchivos();

	/*
	 * Crea y encola un itemEnvio en la cola de imagenes.
	 */
	void agregarImagen(unsigned long int idArea, std::string& fecha,std::string& rutaDeImagen, int matching);

	/*
	 * Crea y encola un itemEnvio en la cola de iseideos.
	 */
	void agregarVideo(unsigned long int idArea, std::string& fecha,std::string& rutaDeVideo, int matching,int intervaloSegs);

	void matar(){
		this->estoyVivo=false;
	}
	void run();
};

#endif /* CLIENTE_MODELO_THENVIADORARCHIVOS_H_ */
