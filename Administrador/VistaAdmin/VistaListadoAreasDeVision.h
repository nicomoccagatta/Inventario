#ifndef ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_
#define ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "VistaAgregarAreaVision.h"
#include "VistaEditarAreaVision.h"
#include "ListaAV.h"
#include "common_ListaProductos.h"
#include <list>
#include "common_AreaDeVision.h"

class VistaListadoAreasDeVision : public Observer {
	Modelo_Observable *modelo;
	Gtk::Viewport *panelDinam;
	void update_lista_av();
	bool on_imagen_button_press(GdkEventButton*);
	void on_av_seleccionado();
	void on_button_agregar();
	void on_button_editar();
	void on_button_eliminar();

	Glib::RefPtr<Gtk::ListStore> m_refProductosListStore;
	Gtk::TreeView m_ProductosTreeView;

	Glib::RefPtr<Gtk::ListStore> m_refAVListStore;
	Gtk::TreeView m_AVTreeView;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;

	Gtk::VBox verticalBox;
	Gtk::HBox hBoxListados;
	ListaAV m_AVList;
	ListaProductos m_ProductosList;
	Gtk::VSeparator m_Vseparator;
	Gtk::VBox labelProductosMasListado;
	Gtk::Label labelProductos;
	Gtk::HButtonBox m_ButtonBox;
	Gtk::Button m_AgregarButton;
	Gtk::Button m_EditarButton;
	Gtk::Button m_EliminarButton;

	VistaAgregarAreaVision *vistaAgregarAreaVision;
	VistaEditarAreaVision *vistaEditarAreaVision;
public:
	VistaListadoAreasDeVision();
	void update();
	void run(Gtk::Viewport *panelDinamico,Modelo_Observable *modelo);
	virtual ~VistaListadoAreasDeVision();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTALISTADOAREASDEVISION_H_ */
