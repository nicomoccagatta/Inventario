#ifndef DATOGRAFICO_H
#define DATOGRAFICO_H

#include <glibmm/ustring.h>

/*
 * Clase que contiene el valor a graficar con su respectiva etiqueta.
 */
class DatoGrafico {
    Glib::ustring etiqueta;
    double valor;
public:
	DatoGrafico(const Glib::ustring& etiqueta, double valor);
	~DatoGrafico();

	const Glib::ustring& getEtiqueta() const;
	double getValor() const;
};

#endif  // DATOGRAFICO_H
