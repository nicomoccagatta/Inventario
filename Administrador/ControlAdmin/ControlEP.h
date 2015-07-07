#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_

#include <gtkmm-2.4/gtkmm.h>
#include <string>

/*
 * Este controlador pertenece a un boton eliminar de una
 * imagen especifica. Se instancia una vez por cada vbox de
 * las imagenes de la vista Editar Producto.
 */
class ControlEP {
	Gtk::VBox *boton;
	std::string *filedir;
	unsigned long int id;

	/*
	 * Debido a que VistaEditarProducto tiene una lista de punteros a ControlEP
	 * no podemos definirla en este header ya que se define a ControlEP.h en
	 * VistaEditarProducto.
	 */
	void *vista;
public:
	ControlEP(Gtk::VBox *button,std::string *sfiledir,void *view);
	ControlEP(Gtk::VBox *button,unsigned long int idImagen,void *view);

	/*
	 * Ambos metodos sirven para eliminar un vBOX que contiene la imagen
	 * y el boton eliminar del producto. Esta imagen a eliminar puede estar
	 * representada por un id si ya fue ingresada al server previamente, o
	 * una ruta si se ingreso en esta oportunidad, por eso ambos metodos.
	 */
	void on_button_eliminarIconoConFileDir();
	void on_button_eliminarIconoConID();

	virtual ~ControlEP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_ */
