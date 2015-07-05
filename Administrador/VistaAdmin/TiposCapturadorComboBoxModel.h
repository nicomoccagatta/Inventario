#ifndef ADMINISTRADOR_VISTAADMIN_TIPOSCAPTURADORCOMBOBOXMODEL_H_
#define ADMINISTRADOR_VISTAADMIN_TIPOSCAPTURADORCOMBOBOXMODEL_H_

class TiposCapturadorComboBoxModel : public Gtk::TreeModel::ColumnRecord{
private:
    Gtk::TreeModelColumn<Glib::ustring> columnaCapturador;
public:
    TiposCapturadorComboBoxModel(){
        add(columnaCapturador);
    }
    Gtk::TreeModelColumn<Glib::ustring>& getColumnaCapturador(){
        return columnaCapturador;
    }
    virtual ~TiposCapturadorComboBoxModel(){}
};

#endif /* ADMINISTRADOR_VISTAADMIN_TIPOSCAPTURADORCOMBOBOXMODEL_H_ */
