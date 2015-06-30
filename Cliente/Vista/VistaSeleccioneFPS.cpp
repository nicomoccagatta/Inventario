/*
 * VistaSeleccioneFPS.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: ale
 */

#include <sstream>

#include "VistaSeleccioneFPS.h"

VistaSeleccioneFPS::VistaSeleccioneFPS() {
	set_title("Ha seleccionado un video, ingrese los FPS");
	set_size_request(450,100);
	vbox = get_vbox();
	vbox->add(fps);
	vbox->add(ok);

	ok.set_label("OK");
	ok.signal_clicked().connect( sigc::mem_fun(*this, &VistaSeleccioneFPS::on_button_OK) );
}

int VistaSeleccioneFPS::correr(){
	this->show_all_children();
	this->run();

	std::stringstream ss;
	ss << fps.get_text();
	int f;
	ss >> f;
	return f;
}

void VistaSeleccioneFPS::on_button_OK(){
	hide();
}
