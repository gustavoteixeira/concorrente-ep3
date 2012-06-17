#ifndef MONITOR_H_
#define MONITOR_H_

#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>

struct MonitorCond;
struct QueueItem;

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
    std::queue<sem_t*> processos_privados_;
};

#endif /* MONITOR_H_ */