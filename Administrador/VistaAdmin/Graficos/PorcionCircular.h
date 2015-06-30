#ifndef PORCION_CIRCULAR_H
#define PORCION_CIRCULAR_H

#include "Area.h"


// Clase que representa una porción circular de un gráfico de torta.
class PorcionCircular : public Area {
    public:
	PorcionCircular(const DatoGrafico& dato, double maximo, unsigned i,
                        double offset,
                        double x0, double y0, double radio);
	~PorcionCircular();

        //Dibuja la porción circular.
	void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);

	double getAvance();

    private:
        double x0;
        double y0;
        double r;
        double valor;
};

#endif  // PORCION_CIRCULAR_H
