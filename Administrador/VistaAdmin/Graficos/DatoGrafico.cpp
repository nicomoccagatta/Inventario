#include "DatoGrafico.h"

DatoGrafico::DatoGrafico(const Glib::ustring& _etiqueta, double _valor) {
    etiqueta = _etiqueta;
    valor = _valor;
}

DatoGrafico::~DatoGrafico() {}

const Glib::ustring& DatoGrafico::getEtiqueta() const {
    return etiqueta;
}

double DatoGrafico::getValor() const {
    return valor;
}
