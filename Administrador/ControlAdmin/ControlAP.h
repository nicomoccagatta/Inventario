#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_

#include <gtkmm-2.4/gtkmm.h>
#include <string>

/*
 * Este controlador pertenece a un boton eliminar de una
 * imagen especifica. Se instancia una vez por cada vbox de
 * las imagenes de la vista Editar Producto.
 */
class ControlAP {
	Gtk::VBox *boton;
	std::string *filedir;

	/*
	 * Debido a que VistaAgregarProducto tiene una lista de punteros a ControlAP
	 * no podemos definirla en este header ya que se define a ControlAP.h en
	 * VistaAgregarProducto.
	 */
	void *vista;
public:
	ControlAP(Gtk::VBox *button,std::string *sfiledir,void *view);
	void on_button_eliminarIcono();
	virtual ~ControlAP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_ */
