/*
 * VistaSeleccioneFPS.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: ale
 */

#include <sstream>

#include "VistaSeleccioneIntervaloSegundos.h"

VistaSeleccioneIntervaloSegundos::VistaSeleccioneIntervaloSegundos() {
	set_title("Ha seleccionado un video, cada cuantos segundos se enviaran los frames?");
	set_size_request(550,100);
	vbox = get_vbox();
	vbox->add(segs);
	vbox->add(ok);

	ok.set_label("OK");
	ok.signal_clicked().connect( sigc::mem_fun(*this, &VistaSeleccioneIntervaloSegundos::on_button_OK) );
}

int VistaSeleccioneIntervaloSegundos::correr(){
	this->show_all_children();
	this->run();

	std::stringstream ss;
	ss << segs.get_text();
	int f;
	ss >> f;
	return f;
}

void VistaSeleccioneIntervaloSegundos::on_button_OK(){
	hide();
}
