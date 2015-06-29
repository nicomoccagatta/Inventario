/*
 * VistaVentanaPPAL.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaVentanaPPAL.h"

VistaVentanaPPAL::VistaVentanaPPAL(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject), model(0), m_refGlade(refGlade),panelDinamicoP(0),panelDinamicoAV(0),
  	  	  	  	  	  	  	  	  panelDinamicoRSG(0),panelDinamicoRAV(0),panelDinamicoRHP(0)
{
	m_refGlade->get_widget("PanelDinamicoP", panelDinamicoP);
	m_refGlade->get_widget("PanelDinamicoAV", panelDinamicoAV);

	m_refGlade->get_widget("PanelDinamicoRSG",panelDinamicoRSG);
	m_refGlade->get_widget("PanelDinamicoRAV",panelDinamicoRAV);
	m_refGlade->get_widget("PanelDinamicoRHP",panelDinamicoRHP);
}

void VistaVentanaPPAL::setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo){
	m_refGlade = refGlade;
	model = modelo;

	model->suscribe(&vistaLP);
	model->suscribe(&vistaLAV);
	model->suscribe(&vistaRSG);
	model->suscribe(&vistaRAV);
	model->suscribe(&vistaRHP);

	model->actualizarProductos();
	vistaLP.run(panelDinamicoP,model);

	model->actualizarAreasDeVision();
	vistaLAV.run(panelDinamicoAV,model);

	vistaRSG.run(panelDinamicoRSG,model);
	vistaRAV.run(panelDinamicoRAV,model);
	vistaRHP.run(panelDinamicoRHP,model);

	this->show_all();
}

VistaVentanaPPAL::~VistaVentanaPPAL() {
}
