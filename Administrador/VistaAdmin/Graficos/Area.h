#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>

#include "DatoGrafico.h"

/** @class Area
 * Clase abstracta que comprende comportamiento común a toda área de un
 * gŕafico, como la capacidad de responder si un click del mouse cayó sobre
 * ella, retornar una string informativa y, el más importante, dibujarse.
 */
class Area {
    public:
        /**
         * Constructor.
         * @param dato aquello que representará el área
         * @param maximo el valor máximo encontrado
         * @param i número de porción (esto es meramente por el color)
         * @param offset desplazamiento del área
         */
        Area(const DatoGrafico& dato, double maximo, unsigned i, double offset);
        virtual ~Area();

        const Glib::ustring& getEtiqueta() const;
        virtual const double* getColor() const;

        /**
         * Dibuja el área.
         * @param ctx contexto sobre el que se dibuja
         */
        virtual void dibujar(Cairo::RefPtr< Cairo::Context >& ctx) = 0;

       /**
         * Obtener el offset nuevo.
         * @return posición siguiente a dibujar un área
         */
        virtual double getAvance() = 0;

        /**
         * Información sobre el área.
         * @return string para tooltip
         */
        virtual std::string getInfo() = 0;
    protected:
        DatoGrafico dato;
        double max;
        double color[4];
        double offset;

        void set_line_width(Cairo::RefPtr< Cairo::Context >& ctx);
    private:
        static double colores[][4];
        double lineWidth;
};

#endif  // AREA_H
