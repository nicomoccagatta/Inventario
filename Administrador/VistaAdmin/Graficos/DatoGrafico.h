#ifndef DATOGRAFICO_H
#define DATOGRAFICO_H

#include <glibmm/ustring.h>

class DatoGrafico {
    public:
		DatoGrafico(const Glib::ustring& etiqueta, double valor);
        ~DatoGrafico();

        const Glib::ustring& getEtiqueta() const;
        double getValor() const;
    private:
        Glib::ustring etiqueta;
        double valor;
};

#endif  // DATOGRAFICO_H
