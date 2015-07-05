#ifndef GRAFICO_H
#define GRAFICO_H

#include <list>
#include <gtkmm-2.4/gtkmm.h>
#include "DatoGrafico.h"
#include "Referencia.h"
#include "Area.h"

class Grafico : public Gtk::DrawingArea {
public:
	Grafico();
	void redibujar();
	virtual ~Grafico();
protected:
	virtual void hallarNormalizacion(const std::list<DatoGrafico>& datos) = 0;
	// borra y regenera todas las referencias
	void deleteAreas();
	void regenerarReferencias();

	virtual void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx) = 0;
	// itera por las áreas y las grafica donde esté puesto el contexto
	void dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx);
	// itera por las referencias y las grafica donde esté puesto el contexto
	void dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx);
	virtual void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) = 0;
	// Regrafica todo el widget
	bool on_expose_event(GdkEventExpose* ev);
	virtual void actualizarDatos(const std::list< DatoGrafico >& datos) = 0;
	void actualizarTamanioMinimo(double x, double y);
	void resize();

	std::list< Referencia > referencias;
	int ancho_ventana;
	int alto_ventana;
	int min_lado;
	bool should_request_size;
	double furthest_x, furthest_y;
	std::list< Area* > areas;
	double normalizacion;
};
#endif  // GRAFICO_H
