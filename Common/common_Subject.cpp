#include "common_Subject.h"

Subject::Subject() {
}

void Subject::suscribe(Observer *observador){
	bool suscripto = false;
	std::vector<Observer*>::iterator it;
	for(it = observadores.begin() ; it != observadores.end() ; ++it){
		if ((*it) == observador)
			suscripto = true;
	}
	if (!suscripto)
		observadores.push_back(observador);
}

void Subject::notify(){
	std::vector<Observer*>::iterator it;
	for(it = observadores.begin() ; it != observadores.end() ; ++it){
		(*it)->update();
	}
}

void Subject::unsuscribe(Observer *observador){
	std::vector<Observer*>::iterator it;
	for(it = observadores.begin() ; it != observadores.end() ; ++it){
		if ((*it) == observador)
			observadores.erase(it++);
	}
}

Subject::~Subject() {
}

