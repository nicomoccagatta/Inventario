/*
 * ListaImagenesEnOrden.h
 *
 *  Created on: Jun 30, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_LISTAIMAGENESENORDEN_H_
#define CLIENTE_VISTA_LISTAIMAGENESENORDEN_H_

#include <gtkmm/scrolledwindow.h>
//#include "AspectPreservingScalingImage.h"

//class AspectPreservingScalingImage;

class ListaImagenesEnOrden: public Gtk::ScrolledWindow {
public:
	ListaImagenesEnOrden(){}
	virtual ~ListaImagenesEnOrden(){}

	class ModelColumns: public Gtk::TreeModel::ColumnRecord{
	public:
		ModelColumns(){
			add(m_col_imagenIcono);
			add(m_col_nombre);
			add(m_col_ruta);
			add(m_col_imgGrande);
		}

		Gtk::TreeModelColumn<Glib::RefPtr <Gdk::Pixbuf> > m_col_imagenIcono;
		Gtk::TreeModelColumn<Glib::ustring> m_col_nombre;
		Gtk::TreeModelColumn<Glib::ustring> m_col_ruta;
		Gtk::TreeModelColumn<Gtk::Image* > m_col_imgGrande;
	};

	ModelColumns m_Columns;
};

#endif /* CLIENTE_VISTA_LISTAIMAGENESENORDEN_H_ */
