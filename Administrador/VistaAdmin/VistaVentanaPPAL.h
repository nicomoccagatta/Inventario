#ifndef ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_
#define ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_

#include <gtkmm-2.4/gtkmm.h>
#include "ModeloAdmin/admin_ModeloObservable.h"
#include "VistaListadoProductos.h"
#include "VistaListadoAreasDeVision.h"
#include "VistaStockGeneral.h"
#include "VistaStockPorAV.h"
#include "VistaStockHistorico.h"

class VistaVentanaPPAL: public Gtk::Window {
public:
	VistaVentanaPPAL(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& refGlade);
	void setearAtributos(const Glib::RefPtr<Gtk::Builder>& refGlade,Modelo_Observable *modelo);
	virtual ~VistaVentanaPPAL();
private:
	Modelo_Observable *model;

	Glib::RefPtr<Gtk::Builder> m_refGlade;
	Gtk::Viewport *panelDinamicoP;
	Gtk::Viewport *panelDinamicoAV;
	Gtk::Viewport *panelDinamicoRSG;
	Gtk::Viewport *panelDinamicoRAV;
	Gtk::Viewport *panelDinamicoRHP;

	VistaListadoProductos vistaLP;
	VistaListadoAreasDeVision vistaLAV;
	VistaStockGeneral vistaRSG;
	VistaStockPorAV vistaRAV;
	VistaStockHistorico vistaRHP;
};

#endif /* ADMINISTRADOR_VISTAADMIN_VISTAVENTANAPPAL_H_ */
