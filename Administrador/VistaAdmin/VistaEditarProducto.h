#ifndef ADMINISTRADOR_VISTAADMIN_VISTAEDITARPRODUCTO_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAEDITARPRODUCTO_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "ControlAdmin/ControlEP.h"
#include <cstdio>
#include <cstdlib>
using std::sprintf;
using std::strtol;

#define RUTA_CARPETA_IMAGENES "temp_admin/"

class VistaEditarProducto : public Gtk::Window{
	Modelo_Observable *modelo;
	void on_button_actualizarIcono();
	void on_button_agregarImagen();
	void on_button_editarOK();
	void on_button_editarCANCEL();

	Gtk::VBox m_vBoxPrincipal;

	unsigned long int m_idProducto;

	Gtk::HBox hBoxNombre;
	Gtk::HBox hBoxDescripcion;
	Gtk::Label m_labelNombre;
	Gtk::Entry m_ingresarNombre;
	Gtk::Label m_labelDescripcion;
	Gtk::Entry m_ingresarDescripcion;
	std::list<unsigned long int> m_idsImagenes;

	Gtk::Label m_labelIcono;
	Gtk::Image m_ImagenIconoPPAL;
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
	std::list<ControlEP*> controladores;

	std::list<std::string*> m_rutaImagenes;

	Gtk::Button m_OKButton;
	Gtk::Button m_CANCELButton;
	Gtk::HButtonBox m_botoneraCANCELOK;
public:
	VistaEditarProducto(Modelo_Observable *model,unsigned long int idProducto,std::string& nombre,std::string& descripcion,
							unsigned long int idIcono,std::list<unsigned long int> idsImagenes);
	void eliminarIconoPertenecienteABotonFileDir(Gtk::VBox *vbbox,std::string *sfiledir);
	void eliminarIconoPertenecienteABotonID(Gtk::VBox *vbbox,unsigned long int id);
	virtual ~VistaEditarProducto();
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAEDITARPRODUCTO_H_ */
