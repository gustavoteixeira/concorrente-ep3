#ifndef MONITOR_H_
#define MONITOR_H_

#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <list>

class Passageiro;

struct MonitorCond;

class Monitor {
  public:
    Monitor(int N);
    ~Monitor();

    //empty(cv), wait(cv,rank), signal_all(cv), minrank(cv)

    void wait(bool cv);
    void wait(bool cv, Passageiro* rank);
    Passageiro* signal(bool cv);
    Passageiro* minrank(bool cv);
    void signal_all(bool cv);
    void empty(bool cv);

    int tamanho_fila_passageiros();
    void print_list_passageiros();

  private:
    void entrada();
    void saida();
    void unranked_signal();
    Passageiro* ranked_signal();
    
    int N_;
    sem_t semaforo_;

    /* Ja que nao eh recomendado o uso num mesmo programa de wait(cv) e wait(cv, rank),
       entao sao usadas estruturas diferentes para a execucao de cada. */
    std::queue<sem_t*> processos_privados_;
    std::list<Passageiro*> objetos_de_rank_;
};

#endif /* MONITOR_H_ */