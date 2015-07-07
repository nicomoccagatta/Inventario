#ifndef ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_
#define ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "common_ListaProductos.h"
#include <list>
#include "common_Producto.h"
#include "Graficos/GraficoDeBarras.h"
#include "Graficos/DatoGrafico.h"

class VistaStockGeneral : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_productos();

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;
	ListaProductos m_ProductosList;

	Gtk::HBox m_HBoxGrillaEImagen;
	GraficoDeBarras m_ImagenItem;
	std::list<DatoGrafico> m_datosGrafico;
public:
	VistaStockGeneral();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaStockGeneral();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTASTOCKGENERAL_H_ */
