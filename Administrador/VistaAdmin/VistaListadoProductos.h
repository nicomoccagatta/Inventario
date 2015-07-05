#ifndef ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_
#define ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ListaProductos.h"
#include <list>
#include "common_Producto.h"
#include "VistaAgregarProducto.h"
#include "VistaEditarProducto.h"

#define RUTA_CARPETA_TEMP "temp_admin/"

class VistaListadoProductos : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;

	void update_lista_productos();
	bool on_imagen_button_press(GdkEventButton*);
	void on_producto_seleccionado();
	void on_button_agregar();
	void on_button_editar();
	void on_button_eliminar();

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	ListaProductos m_ProductosList;

	Gtk::VBox m_verticalBox;

	Gtk::HButtonBox m_botoneraABM;
	Gtk::Button m_AgregarButton;
	Gtk::Button m_EditarButton;
	Gtk::Button m_EliminarButton;

	Gtk::ScrolledWindow m_ventanitaBotoneraImagenes;
	Gtk::Viewport *m_viewportVentanitaBotoneraImagenes;
	Gtk::HButtonBox m_botoneraImagenesProducto;
	std::list<Gtk::Image*> m_listaPunteroImagenes;

	VistaAgregarProducto *vistaAgregarProducto;
	VistaEditarProducto *vistaEditarProducto;
public:
	VistaListadoProductos();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaListadoProductos();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOPRODUCTOS_H_ */
