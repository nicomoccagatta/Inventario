#ifndef PORCION_CIRCULAR_H
#define PORCION_CIRCULAR_H

#include "Area.h"

/*
 *  Clase que representa una porción circular de un gráfico de torta.
 */
class PorcionCircular : public Area {
    double x0;
    double y0;
    double r;
    double valor;
public:
	PorcionCircular(const DatoGrafico& dato, double maximo, unsigned i,
                        double offset,double x0, double y0, double radio);
	~PorcionCircular();

    /*
     * Dibuja la porción circular.
     */
	void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);

	/*
	 * Devuelve el valor del comienzo de la proxima porcion circular
	 */
	double getAvance();
};

#endif  // PORCION_CIRCULAR_H
