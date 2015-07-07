/*
 * ThReproductorVideo.h
 *
 *  Created on: Jul 1, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_THREPRODUCTORVIDEO_H_
#define CLIENTE_VISTA_THREPRODUCTORVIDEO_H_

#include <vector>
#include <gtkmm-2.4/gtkmm.h>

#include "common_Thread.h"
#include "common_Mutex.h"


using common::Mutex;

/*
 * Este Thread sirve para que se pueda reproducir la secuencia de frames
 * sin bloquear al hilo principal y poder seguir usando la interfaz.
 * Una vez arrancado, duerme hasta que se broadcastea la condicion cond.
 */
class ThReproductorVideo: public Thread {

	bool reproduciendo; //false si esta en pausa
	double fps;
	std::vector<Gtk::Image*> frames;
	Gtk::VBox* box; //Donde hay que poner la imagen
	int activo; //El indice en el vector de la imagen que esta en el box
	bool vivo; //para saber si joinear o no

	Mutex mutex;
	pthread_cond_t* cond;

public:
	ThReproductorVideo(Gtk::VBox* box);
	virtual ~ThReproductorVideo();

	void run();
	/*
	 * Setea el vector de Imagenes a mostrar y pone el valor del
	 * activo en -1.
	 */
	void setearFrames(std::vector<Gtk::Image*>& frames);
	void setFPS(double fps);
	void pausa();
	void sacarImagenPausada();

	bool estaVivo(){
		return vivo;
	}
	bool estaPausado(){
		return !reproduciendo;
	}
	void setMutex(Mutex& mutex, pthread_cond_t* cond){
		this->mutex = mutex;
		this->cond = cond;
	}
	void matar(){
		this->vivo = false;
	}
};

#endif /* CLIENTE_VISTA_THREPRODUCTORVIDEO_H_ */
