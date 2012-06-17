#ifndef CARRO_H_
#define CARRO_H_

#include "monitor.h"
#include "passageiro.h"
#include <queue>

struct MonitorCond;

class Carro {
  public:
    Carro(int id, int capacity):
        id_(id),
        capacity_(capacity) {}
    ~Carro() {}
    
    int id() const { return id_; }
    void carrega ();
    void descarrega();
    void volta();
    
  private:
    int id_;
    int capacity_;
    std::queue<Passageiro*> passageiros_;
    Monitor* monitor;
    
};

#endif /* CARRO_H_ */