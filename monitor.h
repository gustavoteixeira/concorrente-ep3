#ifndef MONITOR_H_
#define MONITOR_H_

#include <semaphore.h>

struct MonitorCond;

class Monitor {
  public:
    Monitor(int N);
    ~Monitor();

    //empty(cv),  wait(cv,rank), signal all(cv), minrank(cv)

    void wait(MonitorCond* cv);
    void signal(MonitorCond* cv);

  private:
    void entrada();
    void saida();

    int N_;
    sem_t semaforo_;
    sem_t *processos_privado_;
};

#endif /* MONITOR_H_ */