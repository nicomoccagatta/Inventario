#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>
#include "DatoGrafico.h"

/*
 * Clase abstracta que comprende comportamiento común
 * a clase Barra y Porcion Circular
 */
class Area {
	DatoGrafico dato;
	static double colores[][4];
	double lineWidth;
public:
	Area(const DatoGrafico& dato, double maximo, unsigned i, double offset);
	virtual ~Area();

	const Glib::ustring& getEtiqueta() const;
	virtual const double* getColor() const;

	/*
	 * Dibuja el área, redefinido por clase hija.
	 * ctx es el contexto sobre el que se dibuja
	 */
	virtual void dibujar(Cairo::RefPtr< Cairo::Context >& ctx) = 0;

	/*
	 * Obtener el offset nuevo.
	 * Devuelve la posición siguiente a dibujar un área
	 */
	virtual double getAvance() = 0;
protected:
	double max;
	double color[4];
	double offset;
	void set_line_width(Cairo::RefPtr< Cairo::Context >& ctx);
};

#endif  // AREA_H
