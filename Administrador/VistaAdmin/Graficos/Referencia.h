#ifndef REFERENCIA_H
#define REFERENCIA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>

class Area;
class Grafico;

/** @class Referencia
 * Una referencia para los gráficos. Son un cuadradito con el color del
 * área que refieren y la etiqueta del hecho que generó dicha área.
 */
class Referencia {
    public:
        /**
         * Constructor.
         * @param referente área a la que se relaciona la referencia
         */
        Referencia(const Area& referente);
        ~Referencia();

        void setNegrita(bool estado);

        double dibujar(Cairo::RefPtr< Cairo::Context >& ctx, double offset);
    private:
        double color[4];
        Glib::ustring etiqueta;
        static double anchoCuadradito;
        Cairo::FontWeight font;
};

#endif  // REFERENCIA_H
