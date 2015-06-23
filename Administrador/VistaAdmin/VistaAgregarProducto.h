/*
 * VistaAgregarProducto.h
 *
 *  Created on: 21/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ModelComboBoxAreasDeVision.h"
#include "ControlAdmin/admin_ControlAP.h"
#include "common_Stock.h"
#include <cstdio>
#include <cstdlib>
using std::sprintf;
using std::strtol;

class VistaAgregarProducto : public Observer{
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void on_button_ImagenPPAL();
	void on_button_agregarIcono();
	void on_button_agregarProducto();
	void on_cambio_dia_calendario();
	void comprobarsiFechaEstaEnStock(Glib::Date &fecha,Gtk::Entry &entryCantidad);
	void update_lista_av();
public:
	void borrarIconosAnteriores();
	VistaAgregarProducto();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	void eliminarIconoPertenecienteABoton(Gtk::Button *boton);
	virtual ~VistaAgregarProducto();
protected:
	Gtk::VBox vBoxPrincipal;

	Gtk::HBox hBoxNombre;
	Gtk::HBox hBoxDescripcion;
	Gtk::HBox hBoxStock;
	Gtk::HBox hBoxAreaVision;

	Gtk::Label m_labelNombre;
	Gtk::Entry m_ingresarNombre;

	Gtk::Label m_labelDescripcion;
	Gtk::Entry m_ingresarDescripcion;

	Gtk::VButtonBox m_botoneraStock;
	Gtk::Label m_labelAreaVision;
	Gtk::ComboBox m_AreasDeVision;
	AreasDeVisionComboBoxModel columnas;
	Glib::RefPtr<Gtk::ListStore> modeloComboBox;


	Gtk::Calendar m_calendario;
	Glib::Date m_fechaAnterior;
	std::list<common::Stock*> stockProducto;
	Gtk::Label m_labelCantidad;
	Gtk::Entry m_ingresarCantidad;

	Gtk::HBox hBoxImagenes;
	Gtk::Image m_ImagenBotonIconoPPAL;
	bool m_ImagenSeteada;
	Gtk::Button m_ImagenIconoPPAL;
	Gtk::HButtonBox m_botoneraImgPPAL;
	Gtk::HButtonBox m_botoneraImagenes;
	std::list<Gtk::Button*> m_ImagenIconosSecundarios;
	std::list<ControlAP*> controladores;
	Gtk::HButtonBox m_botoneraIconosSecundarios;
	Gtk::Button m_AgregarIconosSecundarios;

	std::string m_rutaImagenPPAL;
	std::list<std::string> m_rutaImagenesIconos;

	Gtk::Button m_AgregarProducto;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_ */
