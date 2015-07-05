#ifndef ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_
#define ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_

#include <gtkmm-2.4/gtkmm.h>
#include <string>

class ControlAP {
	Gtk::VBox *boton;
	std::string *filedir;
	void *vista;
public:
	ControlAP(Gtk::VBox *button,std::string *sfiledir,void *view);
	void on_button_eliminarIcono();
	virtual ~ControlAP();
};

#endif /* ADMINISTRADOR_CONTROLADMIN_CONTROLAP_H_ */
