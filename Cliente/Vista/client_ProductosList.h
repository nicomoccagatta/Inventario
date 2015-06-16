/*
 * client_ProductosList.h
 *
 *  Created on: Jun 16, 2015
 *      Author: ale
 */

#ifndef CLIENTE_VISTA_CLIENT_PRODUCTOSLIST_H_
#define CLIENTE_VISTA_CLIENT_PRODUCTOSLIST_H_

#include <gtkmm-2.4/gtkmm.h>
#include <gtkmm-2.4/gtkmm/scrolledwindow.h>
#include <list>

#include "../Modelo/client_ModeloObservable.h"

class ProductosList: public Gtk::ScrolledWindow {
public:
	ProductosList();
	virtual ~ProductosList();

	void update(const std::list<Producto*>* prods);

	class ModelColumns: public Gtk::TreeModel::ColumnRecord{
	public:
		ModelColumns(){
			add(m_col_text);
		}

		Gtk::TreeModelColumn<Glib::ustring> m_col_text;
	};

	ModelColumns m_Columns;

protected:
	Glib::RefPtr<Gtk::ListStore> m_refListStore; //The Tree Model.
	Gtk::TreeView m_TreeView; //The Tree View.
};

#endif /* CLIENTE_VISTA_CLIENT_PRODUCTOSLIST_H_ */
