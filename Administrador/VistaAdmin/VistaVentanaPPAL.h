/*
 * VistaVentanaPPAL.h
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ControlAdmin/ControlLP.h"
#include "ControlAdmin/ControlLAV.h"
#include "VistaListadoProductos.h"
#include "VistaListadoAreasDeVision.h"
#include "VistaAgregarProducto.h"
#include "VistaAgregarAreaVision.h"
#include "VistaStockGeneral.h"

class VistaVentanaPPAL: public Gtk::Window {
public:
	VistaVentanaPPAL(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& refGlade);
	void setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo);
	virtual ~VistaVentanaPPAL();
private:
	Modelo_Observable *model;
	void on_button_LP();
	void on_button_AP();
	void on_button_LAV();
	void on_button_AAV();
	void on_button_SGPP();
	void on_button_SPAV();
	void on_button_SHPP();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Button *listado_productos,*agregar_productos;
	Gtk::Button *listado_av,*agregar_av;
	Gtk::Button *sgp,*spav,*shpp;
	Gtk::Viewport *panelDinamico;
	Gtk::HBox *HBoxDinamico;

	ControlLP controlLP;
	ControlLAV controlLAV;
	VistaListadoProductos vistaLP;
	VistaListadoAreasDeVision vistaLAV;
	VistaAgregarProducto vistaAP;
	VistaAgregarAreaVision vistaAAV;
	VistaStockGeneral vistaSG;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_ */
