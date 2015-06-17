/*
 * admin_Subject.cpp
 *
 *  Created on: 16/6/2015
 *      Author: nicomoccagatta
 */

#include "admin_Subject.h"

Subject::Subject() {
}

void Subject::suscribe(Observer *observador){
	observadores.push_back(observador);
}

void Subject::notify(){
	//std::vector::iterator<Observer*> iterator = observadores.begin();
	//for( ; iterator != observadores.end() ; ++iterator){
	//	iterator->update();
	//}
}

void Subject::unsuscribe(Observer *observador){

}

Subject::~Subject() {
}

