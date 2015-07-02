#include "common_Thread.h"

Thread::~Thread() {}

void Thread::start() {
	pthread_create(&this->thread, NULL, starter, this);
}

const void* Thread::join() {
  void* result;
  pthread_join(this->thread, &result);
  return result;
}

void* Thread::starter(void* data) {
  Thread* thread = (Thread*)data;
  thread->run();
  return NULL;
}

void Thread::run() {}
