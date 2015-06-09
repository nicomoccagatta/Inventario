#ifndef COMMON_THREAD_H_
#define COMMON_THREAD_H_
#include "pthread.h"
#include <stdlib.h>

class Thread {
 public:
  virtual ~Thread();
  virtual void run();
  void start();
  const void* join();

 private:
  static void* starter(void* datos);

 protected:
  pthread_t thread;
};

#endif
