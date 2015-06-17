/*
 * VistaVentanaPPAL.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaVentanaPPAL.h"

VistaVentanaPPAL::VistaVentanaPPAL(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject), model(0), m_refGlade(refGlade),listado_productos(0),agregar_productos(0),
  listado_av(0),agregar_av(0),sgp(0),spav(0),shpp(0),panelDinamico(0)
{
	m_refGlade->get_widget("Listado de Productos", listado_productos);
	if(listado_productos)
		listado_productos->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_LP) );

	m_refGlade->get_widget("Agregar Producto", agregar_productos);
		if(agregar_productos)
			agregar_productos->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_AP) );

	m_refGlade->get_widget("Listado de Areas de Vision", listado_av);
		if(listado_av)
			listado_av->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_LAV) );

	m_refGlade->get_widget("Agregar Areas de Vision", agregar_av);
		if(agregar_av)
			agregar_av->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_AAV) );

	m_refGlade->get_widget("SGPP", sgp);
		if(sgp)
			sgp->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_SGPP) );

	m_refGlade->get_widget("SPAV", spav);
		if(spav)
			spav->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_SPAV) );

	m_refGlade->get_widget("SHPP", shpp);
		if(shpp)
			shpp->signal_clicked().connect( sigc::mem_fun(*this, &VistaVentanaPPAL::on_button_SHPP) );

	m_refGlade->get_widget("panelDinamico",panelDinamico);
}

void VistaVentanaPPAL::setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo){
	m_refGlade = refGlade;
	model = modelo;
}

VistaVentanaPPAL::~VistaVentanaPPAL() {
}

void VistaVentanaPPAL::on_button_LP()
{
	//model->notify();
	hide();
}

void VistaVentanaPPAL::on_button_AP()
{
	hide();
}

void VistaVentanaPPAL::on_button_LAV()
{
	hide();
}

void VistaVentanaPPAL::on_button_AAV()
{
	hide();
}

void VistaVentanaPPAL::on_button_SGPP()
{
	hide();
}

void VistaVentanaPPAL::on_button_SPAV()
{
	hide();
}

void VistaVentanaPPAL::on_button_SHPP()
{
	hide();
}
