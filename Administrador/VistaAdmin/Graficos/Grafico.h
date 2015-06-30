#ifndef GRAFICO_H
#define GRAFICO_H

#include <list>
#include <gtkmm/drawingarea.h>
#include <gtkmm/layout.h>
#include <gtkmm/viewport.h>

#include "DatoGrafico.h"
#include "Referencia.h"

class Area;

class Grafico : public Gtk::DrawingArea {
    public:
        Grafico();
        void redibujar();
        virtual ~Grafico();

    protected:
        std::list< Area* > areas;
        double normalizacion;

        virtual void hallarNormalizacion(const std::list<DatoGrafico>& datos) = 0;
        /** borra y regenera todas las referencias */
        void deleteAreas();
        void regenerarReferencias();

    private:
        virtual void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx) = 0;
        /** itera por las áreas y las grafica donde esté puesto el contexto */
        void dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx);
        /** itera por las referencias y las grafica donde esté puesto el contexto */
        void dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx);

        std::list< Referencia > referencias;
        std::list< Area* >::iterator areaSeleccionada;

        virtual void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) = 0;


        /**
         * Signal handler para el evento Gtk::Widget::signal_expose_event.
         *
         * Regrafica todo el widget.
         * @return true siempre, el manejo del evento termina acá.
         */
        bool on_expose_event(GdkEventExpose* ev);

        int ancho_ventana;
        int alto_ventana;
        int min_lado;
        bool should_request_size;
        double furthest_x, furthest_y;
        void resize();

        virtual void actualizarDatos(const std::list< DatoGrafico >& datos) = 0;
        void actualizarTamanioMinimo(double x, double y);
};
#endif  // GRAFICO_H
