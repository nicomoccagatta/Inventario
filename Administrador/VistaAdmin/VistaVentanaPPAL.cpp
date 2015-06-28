/*
 * VistaVentanaPPAL.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaVentanaPPAL.h"

VistaVentanaPPAL::VistaVentanaPPAL(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject), model(0), m_refGlade(refGlade),panelDinamicoP(0),panelDinamicoAV(0)
{
	m_refGlade->get_widget("PanelDinamicoP", panelDinamicoP);
	m_refGlade->get_widget("PanelDinamicoAV", panelDinamicoAV);
}

void VistaVentanaPPAL::setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo){
	m_refGlade = refGlade;
	model = modelo;

	model->suscribe(&vistaLP);
	model->suscribe(&vistaLAV);

	model->actualizarProductos();
	vistaLP.run(panelDinamicoP,model);

	model->actualizarAreasDeVision();
	vistaLAV.run(panelDinamicoAV,model);

	this->show_all();
}

VistaVentanaPPAL::~VistaVentanaPPAL() {
}
