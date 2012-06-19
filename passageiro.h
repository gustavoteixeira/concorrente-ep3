#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include <pthread.h>
#include <time.h>
#include "monitor.h"

struct MonitorCond;

class Passageiro {
  public:
    Passageiro(int id, Monitor* monitor, bool bilhete_dourado = false):
        id_(id),
        voltas_dadas_(0),
        bilhete_dourado_(bilhete_dourado),
        monitor_(monitor) { sem_init(&semaforo_, 0, 0); }
    ~Passageiro() { sem_destroy(&semaforo_); }
    sem_t* semaforo() { return &semaforo_; }

    int id() const { return id_; }

    void set_voltas_dadas(int voltas_dadas) { voltas_dadas_ = voltas_dadas; }

    bool bilhete_dourado() const { return bilhete_dourado_; }
    void pega_carona ();

    void imprime_passageiro();

  private:
    int id_;
    int voltas_dadas_;
    bool bilhete_dourado_;

    Monitor* monitor_;
    sem_t semaforo_;
};

#endif /* PASSAGEIRO_H_ */