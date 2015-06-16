/*
 * client_ProductosList.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: ale
 */

#include "client_ProductosList.h"

ProductosList::ProductosList() {
	/* Create a new scrolled window, with scrollbars only if needed */
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	add(m_TreeView);

	/* create list store */
	m_refListStore = Gtk::ListStore::create(m_Columns);

	m_TreeView.set_model(m_refListStore);

	//Add the Model's column to the View's columns:
	m_TreeView.append_column("Productos", m_Columns.m_col_text);

	show_all_children();

}

ProductosList::~ProductosList() {
	// TODO Auto-generated destructor stub
}

void ProductosList::update(const std::list<Producto*>* prods){
	/* Add some messages to the window */
	std::list<Producto*>::const_iterator it;

	for (it=prods->begin(); it!=prods->end();++it){
		std::cerr << (*it)->getId() << " " << (*it)->getNombre() << std::endl;

		Gtk::TreeModel::Row row = *(m_refListStore->append());
		row[m_Columns.m_col_text] = (*it)->getNombre();
	}
}

