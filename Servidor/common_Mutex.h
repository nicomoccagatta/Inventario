#ifndef COMMON_MUTEX_H_
#define COMMON_MUTEX_H_

#include "pthread.h"

namespace common {

class Mutex {
 public:
  Mutex();
  virtual ~Mutex();
  void bloquear();
  void desbloquear();

 private:
  pthread_mutex_t mutex;
};

} /* namespace common */

#endif /* COMMON_MUTEX_H_ */
