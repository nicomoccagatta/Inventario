/*
 * ListaProductos.h
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#ifndef ADMINISTRADOR_VISTAADMIN_LISTAAV_H_
#define ADMINISTRADOR_VISTAADMIN_LISTAAV_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm-2.4/gtkmm/scrolledwindow.h>
#include <list>

#include "../ModeloAdmin/admin_ModeloObservable.h"

class ListaAV: public Gtk::ScrolledWindow {
public:
	ListaAV();
	virtual ~ListaAV();

	class ModelColumns: public Gtk::TreeModel::ColumnRecord{
	public:
		ModelColumns(){
			add(m_col_Id);
			add(m_col_Ubicacion);
			add(m_col_data);
		}

		Gtk::TreeModelColumn<long unsigned int> m_col_Id;
		Gtk::TreeModelColumn<Glib::ustring> m_col_Ubicacion;
		Gtk::TreeModelColumn<AreaDeVision*> m_col_data;
	};

	ModelColumns m_Columns;
};

#endif /* ADMINISTRADOR_VISTAADMIN_LISTAAV_H_ */