#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "monitor.h"

struct MonitorCond;

class Passageiro {
  public:
    Passageiro(int id):
        id_(id),
        voltas_dadas_(0) {}
    ~Passageiro() {}
    
    int id() const { return id_; }
    bool bilhete_dourado() const { return bilhete_dourado_; }
    void pega_carona ();
    void dar_voltas ();

  private:
    int id_;
    int voltas_dadas_;    
    bool bilhete_dourado_;
    Monitor* monitor;
};

#endif /* PASSAGEIRO_H_ */