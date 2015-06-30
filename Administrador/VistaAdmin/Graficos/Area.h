#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>

#include "DatoGrafico.h"

//Clase abstracta que comprende comportamiento común a toda área de un gŕafico.
class Area {
    public:
        /* dato es aquello que representará el área
         * maximo es el valor máximo encontrado
         * i es un número utilizado para establecer su color
         * offset es el desplazamiento del área
         */
        Area(const DatoGrafico& dato, double maximo, unsigned i, double offset);
        virtual ~Area();
        const Glib::ustring& getEtiqueta() const;
        virtual const double* getColor() const;

//Dibuja el área. ctx es el contexto sobre el que se dibuja
        virtual void dibujar(Cairo::RefPtr< Cairo::Context >& ctx) = 0;

//Obtener el offset nuevo.Devuelve la posición siguiente a dibujar un área
        virtual double getAvance() = 0;
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
