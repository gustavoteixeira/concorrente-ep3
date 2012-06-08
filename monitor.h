#ifndef MONITOR_H_
#define MONITOR_H_

#include <semaphore.h>

class Monitor {
  public:
    Monitor();
    ~Monitor();

    //empty(cv), wait(cv), wait(cv,rank), signal(cv), signal all(cv), minrank(cv)
  private:
    void entrada();
    void saida();

    sem_t semaforo_;
};

#endif /* MONITOR_H_ */