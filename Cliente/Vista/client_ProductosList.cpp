/*
 * client_ProductosList.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: ale
 */

#include "client_ProductosList.h"

ProductosList::ProductosList() {
	/* Create a new scrolled window, with scrollbars only if needed */
	//set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

	//add(m_TreeView);

	/* create list store */
	//m_refListStore = Gtk::ListStore::create(m_Columns);

	//m_TreeView.set_model(m_refListStore);

	//Add the Model's column to the View's columns:
	//m_TreeView.append_column("Iconos", m_Columns.m_col_icon_id);
	//m_TreeView.append_column("Productos", m_Columns.m_col_text);

	/*PARA MOSTRAR LOS ICONOS TENGO QUE HACER ALGO PARECIDO A ESTO PERO CON
	 * ICON EN VEZ DE CellRendererProgress
	 * Voy a tener que buscar la imagen segun el id del icono
	 *
	 * //Display a progress bar instead of a decimal number:
  Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
  int cols_count = m_TreeView.append_column("Some percentage", *cell);
  Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count - 1);
  if(pColumn)
  {
    pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
  }*/

	//show_all_children();

}

ProductosList::~ProductosList() {
	// TODO Auto-generated destructor stub
}

void ProductosList::update(const std::list<Producto*>* prods){
	/* Add some messages to the window */
	/*std::list<Producto*>::const_iterator it;

	for (it=prods->begin(); it!=prods->end();++it){
		std::cerr << (*it)->getId() << " " << (*it)->getNombre() << std::endl;

		Gtk::TreeModel::Row row = *(m_refListStore->append());
		row[m_Columns.m_col_text] = (*it)->getNombre();
		row[m_Columns.m_col_icon_id] = (*it)->getIdIcono();
		row[m_Columns.m_col_data] = *it;
	}
	show_all_children();*/
}

