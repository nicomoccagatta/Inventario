#ifndef PORCION_CIRCULAR_H
#define PORCION_CIRCULAR_H

#include "Area.h"

/** @class PorcionCircular
 * Clase concreta que representa una porción circular de un gráfico de torta.
 */
class PorcionCircular : public Area {
    public:
        /**
         * Constructor.
         * @param dato aquello que representará la porción
         * @param maximo el valor máximo encontrado
         * @param i número de porción (esto es meramente por el color)
         * @param offset desplazamiento de la porción
         * @param x0 centro del círculo
         * @param y0 centro del círculo
         * @param radio radio del círculo
         */
        PorcionCircular(const DatoGrafico& dato, double maximo, unsigned i,
                        double offset,
                        double x0, double y0, double radio);
        /**
         * Destructor.
         */
        ~PorcionCircular();

        /**
         * Dibuja la porción circular.
         * @param ctx contexto sobre el que se dibuja
         */
        void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);

        /**
         * Evalúa si el mouse está posado sobre la porción circular.
         * @param x posición x del mouse en la ventana, normalizada
         * @param y posición y del mouse en la ventana, normalizada
         * @return true o false, según la posición pertenece al área
         */
        bool fueClickeada(double x, double y);

        /**
         * Obtener el offset nuevo.
         * @return posición siguiente a dibujar un porción circular
         */
        double getAvance();

        /**
         * Información sobre el área.
         * @return string para tooltip
         */
        std::string getInfo();
    private:
        double x0;
        double y0;
        double r;
        double valor;
};

#endif  // PORCION_CIRCULAR_H
