/*
 * VistaListadoProductos.cpp
 *
 *  Created on: 17/6/2015
 *      Author: nicomoccagatta
 */

#include "VistaListadoAreasDeVision.h"

VistaListadoAreasDeVision::VistaListadoAreasDeVision()
{
	m_AgregarButton.set_label("Agregar");
	m_AgregarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoAreasDeVision::on_button_agregar));
	m_EditarButton.set_label("Editar");
	m_EditarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoAreasDeVision::on_button_editar));
	m_EliminarButton.set_label("Eliminar");
	m_EliminarButton.signal_clicked().connect( sigc::mem_fun(*this, &VistaListadoAreasDeVision::on_button_eliminar) );

	m_ButtonBox.pack_start(m_AgregarButton);
	m_ButtonBox.pack_start(m_EditarButton);
	m_ButtonBox.pack_start(m_EliminarButton);
	m_ButtonBox.set_layout(Gtk::BUTTONBOX_START);

	verticalBox.pack_start(m_ButtonBox,Gtk::PACK_SHRINK,true,0);

	m_AVList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_AVList.set_size_request(200,400);
	m_AVList.add(m_AVTreeView);

	m_AVTreeView.append_column("Ubicacion", m_AVList.m_Columns.m_col_Ubicacion);

	hBoxListados.pack_start(m_AVList);
	labelProductos.set_text("Productos Detectados");
	labelProductosMasListado.pack_start(labelProductos);
	labelProductosMasListado.pack_end(m_ProductosList);
	labelProductosMasListado.set_size_request(400,Gtk::EXPAND);
	hBoxListados.pack_start(m_Vseparator);
	hBoxListados.pack_end(labelProductosMasListado);

	m_ProductosList.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_ProductosList.set_size_request(200,400);
	m_ProductosList.add(m_ProductosTreeView);
	m_ProductosTreeView.append_column("Icono", m_ProductosList.m_Columns.m_col_imagenIcono);
	m_ProductosTreeView.append_column("Producto", m_ProductosList.m_Columns.m_col_nombre);
	m_ProductosTreeView.append_column("Cantidad", m_ProductosList.m_Columns.m_col_cantidad);

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	verticalBox.pack_end(hBoxListados);

	refTreeSelection = m_AVTreeView.get_selection();
	refTreeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &VistaListadoAreasDeVision::on_av_seleccionado) );
}

void VistaListadoAreasDeVision::update(){
	m_refAVListStore = Gtk::ListStore::create(m_AVList.m_Columns);
	m_AVTreeView.set_model(m_refAVListStore);

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	this->update_lista_av();

	refTreeSelection = m_AVTreeView.get_selection();
}

void VistaListadoAreasDeVision::run(Gtk::Viewport *panelDinamico,Modelo_Observable *model){
	this->modelo = model;
	this->panelDinam = panelDinamico;

	m_refAVListStore = Gtk::ListStore::create(m_AVList.m_Columns);
	m_AVTreeView.set_model(m_refAVListStore);

	m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
	m_ProductosTreeView.set_model(m_refProductosListStore);

	this->update_lista_av();

	panelDinam->add(verticalBox);

	refTreeSelection = m_AVTreeView.get_selection();
}

VistaListadoAreasDeVision::~VistaListadoAreasDeVision() {
}

void VistaListadoAreasDeVision::on_button_agregar(){
	vistaAgregarAreaVision = new VistaAgregarAreaVision(modelo);
}

void VistaListadoAreasDeVision::on_button_editar(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		AreaDeVision *area = row[m_AVList.m_Columns.m_col_data];
		unsigned long int id = area->getId();
		std::string ubicacion = area->getUbicacion();
		std::string capturador = area->getTipoDeCapturador();
		std::cerr << "TIPO DE CAPTURADOR : --" << area->getTipoDeCapturador() <<"--"<<std::endl;
		vistaEditarAreaVision = new VistaEditarAreaVision(modelo,id,ubicacion,capturador);
	}
}

void VistaListadoAreasDeVision::on_button_eliminar(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		modelo->eliminarAreaVision(row[m_AVList.m_Columns.m_col_Id]);
		modelo->notify();
	}
}

void VistaListadoAreasDeVision::on_av_seleccionado(){
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		const std::list<Producto*>* prods = row[m_AVList.m_Columns.m_ProductosDetectados];

		m_refProductosListStore = Gtk::ListStore::create(m_ProductosList.m_Columns);
		m_ProductosTreeView.set_model(m_refProductosListStore);

		std::list<Producto*>::const_iterator it;
		for (it=prods->begin(); it!=prods->end();++it){
		Gtk::TreeModel::Row row = *(m_refProductosListStore->append());
		std::string rutaImagen = modelo->getImagenConID((*it)->getIdIcono());
		Glib::RefPtr<Gdk::Pixbuf>  pic = Gdk::Pixbuf::create_from_file(rutaImagen,20,20,false);
		row[m_ProductosList.m_Columns.m_col_imagenIcono] = pic;
		row[m_ProductosList.m_Columns.m_col_nombre] = (*it)->getNombre();
		row[m_ProductosList.m_Columns.m_col_cantidad] = (*it)->getStock();
		row[m_ProductosList.m_Columns.m_col_data] = *it;
		}
	}
}

void VistaListadoAreasDeVision::update_lista_av(){
	modelo->actualizarAreasDeVision();
	const std::list<AreaDeVision*>* avs = modelo->getAreasDeVision();
	std::list<AreaDeVision*>::const_iterator it;
	for (it=avs->begin(); it!=avs->end();++it){
	Gtk::TreeModel::Row row = *(m_refAVListStore->append());
	row[m_AVList.m_Columns.m_col_Id] = (*it)->getId();
	row[m_AVList.m_Columns.m_col_Ubicacion] = (*it)->getUbicacion();
	row[m_AVList.m_Columns.m_ProductosDetectados] = (*it)->getProductosDetectados();
	row[m_AVList.m_Columns.m_col_data] = *it;
	}
}
