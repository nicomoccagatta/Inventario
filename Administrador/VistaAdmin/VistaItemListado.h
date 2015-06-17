/*
 * VistaItemListado.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_VISTAITEMLISTADO_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAITEMLISTADO_H_

#include <gtkmm-2.4/gtkmm.h>
#include <glibmm-2.4/glibmm.h>

class VistaItemListado : public Gtk::HBox{
	Gtk::Button boton_Imagen;
	Gtk::VBox nom_desc;
	Gtk::Label label_Nombre;
	Gtk::Label label_Descripcion;
	Gtk::HBox edit_elim;
	Gtk::Button boton_editar;
	Gtk::Button boton_eliminar;
public:
	VistaItemListado();
	void setear(const std::string& rutaImagen,const std::string& nombre,const std::string& descripcion);
	virtual ~VistaItemListado();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAITEMLISTADO_H_ */
