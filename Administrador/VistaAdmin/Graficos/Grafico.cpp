#include "Grafico.h"
#include <gtkmm/messagedialog.h>
#include "Area.h"

#define MIN_LADO 200
#define COL_RESULTADO 0  // constante que hace que siempre se tome la columna 0 de la respuesta para dar nombre a las áreas del gráfico
#define SIN_DATOS "No hay datos para mostrar"

Grafico::Grafico(){
    set_size_request(MIN_LADO, MIN_LADO);
    furthest_x = 1.0;
    furthest_y = 1.0;
    min_lado = 0;
    should_request_size = true;
}

Grafico::~Grafico() {
    deleteAreas();
}

void Grafico::deleteAreas() {
    std::list< Area* >::iterator it;
    for (it = areas.begin(); it != areas.end(); ++it)
        delete *it;
}

void Grafico::regenerarReferencias() {
    std::list< Area* >::const_iterator itAreas = areas.begin();
    referencias.clear();
    for ( ; itAreas != areas.end(); ++itAreas) {
        Referencia refNueva(**itAreas);
        referencias.push_back(refNueva);
    }
}

bool Grafico::on_expose_event(GdkEventExpose* ev) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Gtk::Allocation allocation = get_allocation();
        ancho_ventana = allocation.get_width();
        alto_ventana = allocation.get_height();
        if (!min_lado)
            min_lado = ancho_ventana < alto_ventana? ancho_ventana : alto_ventana;

        Cairo::RefPtr<Cairo::Context> ctx = window->create_cairo_context();
        ctx->set_source_rgba(1.0, 1.0, 1.0, 1.0);
        ctx->rectangle(0, 0, ancho_ventana, alto_ventana);
        ctx->fill_preserve();
        ctx->clip();
        ctx->scale(min_lado, min_lado);
        dibujarAreas(ctx);
        dibujarReferencias(ctx);
        dibujarEspecializacion(ev, ctx);
    }

    return true;
}

void Grafico::dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx) {
    if (areas.empty()) {
        ctx->save();
            ctx->move_to(0.03, 0.1);
            ctx->set_font_size(0.06);
            ctx->set_source_rgb(0.5, 0.5, 0.5);
            ctx->show_text(SIN_DATOS);
        ctx->restore();
    } else {
        std::list< Area* >::iterator it = areas.begin();
        for ( ; it != areas.end(); ++it)
            (*it)->dibujar(ctx);
    }
}

void Grafico::dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx) {
    if (referencias.empty())
        return;

    double offset = 0.0;
    double x, y;
    std::list< Referencia >::iterator it = referencias.begin();
    for ( ; it != referencias.end(); ++it) {
        dibujarEspecializacionReferencias(ctx);
        offset = it->dibujar(ctx, offset);
        ctx->get_current_point(x, y);
        actualizarTamanioMinimo(x, y);
    }
    resize();
}


void Grafico::actualizarTamanioMinimo(double x, double y) {
    furthest_x = x > furthest_x? x : furthest_x;
    furthest_y = y > furthest_y? y : furthest_y;
}

void Grafico::resize() {
    if (should_request_size &&
        (furthest_x > 1 || furthest_y > 1)) {
        // para que no termine la ventana pegada al último punto
        furthest_x += 0.1;
        furthest_y += 0.1;
        set_size_request(min_lado * furthest_x, min_lado * furthest_y);
        should_request_size = false;
    }
}

void Grafico::redibujar() {
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(),
				get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
}
