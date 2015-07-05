#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_

#include <gtkmm-2.4/gtkmm.h>
#include <string>

class ControlEP {
		Gtk::VBox *boton;
		std::string *filedir;
		unsigned long int id;
		void *vista;
public:
	ControlEP(Gtk::VBox *button,std::string *sfiledir,void *view);
	ControlEP(Gtk::VBox *button,unsigned long int idImagen,void *view);
	void on_button_eliminarIconoConFileDir();
	void on_button_eliminarIconoConID();
	virtual ~ControlEP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLEP_H_ */
