#ifndef CLIENTE_VISTA_MODELCOMBOBOXAREASDEVISION_H_
#define CLIENTE_VISTA_MODELCOMBOBOXAREASDEVISION_H_

#include "common_AreaDeVision.h"

using common::AreaDeVision;

class AreasDeVisionComboBoxModel : public Gtk::TreeModel::ColumnRecord{
private:
    Gtk::TreeModelColumn<AreaDeVision*> columnaValor;
    Gtk::TreeModelColumn<Glib::ustring> columnaTexto;
public:
    AreasDeVisionComboBoxModel(){
        add(columnaValor);
        add(columnaTexto);
    }
    Gtk::TreeModelColumn<AreaDeVision*>& getColumnaValor(){
        return columnaValor;
    }
    Gtk::TreeModelColumn<Glib::ustring>& getColumnaTexto(){
        return columnaTexto;
    }
    virtual ~AreasDeVisionComboBoxModel(){}
};

#endif /* CLIENTE_VISTA_MODELCOMBOBOXAREASDEVISION_H_ */
