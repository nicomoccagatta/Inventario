#ifndef BARRA_H
#define BARRA_H

#include "Area.h"

/** @class Barra
 * Clase concreta que representa una barra de un gráfico de barras.
 */
class Barra : public Area {
    public:
        /**
         * Constructor.
         * @param dato aquello que representará la barra
         * @param maximo el valor máximo encontrado
         * @param i número de porción (esto es meramente por el color)
         * @param offset desplazamiento de la barra
         * @param separacion separación entre barras
         * @param ancho ancho de las barras
         */
        Barra(const DatoGrafico& dato, double maximo, unsigned i, double offset,
              double separacion, double ancho);
        /**
         * Destructor.
         */
        ~Barra();

        /**
         * Dibuja la barra.
         * @param ctx contexto sobre el que se dibuja
         */
        void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);

        /**
         * Evalúa si el mouse está posado sobre la barra.
         * @param x posición x del mouse en la ventana, normalizada
         * @param y posición y del mouse en la ventana, normalizada
         * @return true o false, según la posición pertenece al área
         */
        bool fueClickeada(double x, double y);

        /**
         * Obtener el offset nuevo.
         * @return posición siguiente a dibujar una barra
         */
        double getAvance();

        /**
         * Información sobre el área.
         * @return string para tooltip
         */
        std::string getInfo();
    private:
        double sep;
        double ancho;
        double hasta;
        double x0;
        double y0;
};

#endif  // BARRA_H

