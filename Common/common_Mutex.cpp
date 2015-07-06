#include "common_Mutex.h"

namespace common {

Mutex::Mutex() { pthread_mutex_init(&this->mutex, NULL); }

Mutex::~Mutex() { pthread_mutex_destroy(&this->mutex); }

void Mutex::bloquear() { pthread_mutex_lock(&this->mutex); }

void Mutex::desbloquear() { pthread_mutex_unlock(&this->mutex); }

void Mutex::cond_wait(pthread_cond_t* cond){
	pthread_cond_wait(cond, &(this->mutex));
}

} /* namespace common */

