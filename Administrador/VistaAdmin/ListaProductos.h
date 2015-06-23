/*
 * ListaProductos.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_LISTAPRODUCTOS_H_
#define ADMINISTRADOR_VISTAADMIN_LISTAPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm-2.4/gtkmm/scrolledwindow.h>
#include <list>

#include "../ModeloAdmin/admin_ModeloObservable.h"

class ListaProductos: public Gtk::ScrolledWindow {
public:
	ListaProductos();
	virtual ~ListaProductos();

	class ModelColumns: public Gtk::TreeModel::ColumnRecord{
	public:
		ModelColumns(){
			add(m_col_id);
			add(m_col_nombre);
			add(m_col_descripcion);
			add(m_col_cantidad);
			add(m_col_idIcono);
			add(m_col_data);
		}

		Gtk::TreeModelColumn<unsigned int> m_col_id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_nombre;
		Gtk::TreeModelColumn<Glib::ustring> m_col_descripcion;
		Gtk::TreeModelColumn<unsigned int> m_col_cantidad;
		Gtk::TreeModelColumn<unsigned int> m_col_idIcono;
		Gtk::TreeModelColumn<Producto*> m_col_data;
	};

	ModelColumns m_Columns;
};

#endif /* ADMINISTRADOR_VISTAADMIN_LISTAPRODUCTOS_H_ */
