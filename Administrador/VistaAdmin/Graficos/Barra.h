#ifndef BARRA_H
#define BARRA_H

#include "Area.h"

//Clase concreta que representa una barra de un gráfico de barras.
class Barra : public Area {
    double sep;
    double ancho;
    double hasta;
    double x0;
    double y0;
public:
	Barra(const DatoGrafico& dato, double maximo, unsigned i, double offset,
              double separacion, double ancho);
	~Barra();

//Dibuja la barra. ctx es el contexto sobre el que se dibuja
	void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);

//Obtener el offset nuevo. Devuelve la posición siguiente a dibujar una barra
	double getAvance();
};

#endif  // BARRA_H

