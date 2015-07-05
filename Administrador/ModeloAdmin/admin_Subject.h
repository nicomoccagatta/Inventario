#ifndef ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_
#define ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_

#include <vector>
#include "ModeloAdmin/admin_Observer.h"
#include <iostream>

class Subject {
	std::vector<Observer*> observadores;
public:
	Subject();
	void suscribe(Observer *observador);
	void notify();
	void unsuscribe(Observer *observador);
	virtual ~Subject();
};

#endif /* ADMINISTRADOR_MODELOADMIN_ADMIN_SUBJECT_H_ */
