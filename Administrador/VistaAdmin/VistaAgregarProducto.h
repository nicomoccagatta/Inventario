#ifndef ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include <cstdio>
#include <cstdlib>

#include "../ControlAdmin/ControlAP.h"
using std::sprintf;
using std::strtol;

class VistaAgregarProducto : public Gtk::Window{
	Modelo_Observable *modelo;
	void on_button_actualizarIcono();
	void on_button_agregarImagen();
	void on_button_agregarProducto();
	void on_button_Cancelar();
	bool on_exit_clicked(GdkEventAny* event);

	Gtk::VBox m_vBoxPrincipal;

	Gtk::HBox hBoxNombre;
	Gtk::HBox hBoxDescripcion;
	Gtk::Label m_labelNombre;
	Gtk::Entry m_ingresarNombre;
	Gtk::Label m_labelDescripcion;
	Gtk::Entry m_ingresarDescripcion;

	Gtk::Label m_labelIcono;
	Gtk::Image m_ImagenIconoPPAL;
	bool m_ImagenSeteada;
	Gtk::VButtonBox m_botoneraFileChooser;
	Gtk::FileChooserButton m_botonFileChooserImgPPAL;
	Gtk::HButtonBox m_botoneraImgPPAL;

	Gtk::HButtonBox m_botoneraImagenAgregar;
	Gtk::Label m_labelImagen;
	Gtk::Button m_botonAgregarImagen;

	Gtk::ScrolledWindow m_scrolledWImagenes;
	Gtk::Viewport *m_viewPortImagenes;
	Gtk::HButtonBox m_botoneraImagenes;
	Gtk::VButtonBox m_botoneraImagenMasDeleteButton;
	std::list<Gtk::VBox*> m_listabotonEliminarImagenes;
	std::list<Gtk::Image*> m_refImagenesdelete;
	std::list<Gtk::Button*> m_refButtondelete;
	std::list<ControlAP*> controladores;

	std::list<std::string*> m_rutaImagenesIconos;

	Gtk::Button m_AgregarProducto;
	Gtk::Button m_Cancelar;
	Gtk::HButtonBox m_butoneraAgregarBoton;
public:
	VistaAgregarProducto(Modelo_Observable *model);
	virtual ~VistaAgregarProducto();

	/*
	 * Elimina el vBOX que contiene a la imagen y el boton eliminar.
	 * Sirve para eliminar una imagen ingresada previamente (arrepentimiento)
	 */
	void eliminarIconoPertenecienteABoton(Gtk::VBox *vbbox,std::string *sfiledir);
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAAGREGARPRODUCTO_H_ */
