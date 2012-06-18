#ifndef CARRO_H_
#define CARRO_H_

#include "monitor.h"
#include "passageiro.h"
#include <list>

#ifdef _WIN32 /* _Win32 eh normalmente definido por compiladores compilando para sistemas Windows de 32 ou 64 bits */
# include <windows.h>
#elif __unix__ /* __unix__ eh normalmente definido por compiladores compilando para sistemas Unix. */
# include <unistd.h>
#endif

#define TEMPO_NUMA_VOLTA 100
#define TEMPO_NUMA_ATUALIZACAO 1

struct MonitorCond;

class Carro {
  public:
    Carro(int id, int capacity, Monitor* monitor):
        id_(id),
        capacity_(capacity),
        segundos_desde_inicio_volta_(0),
        monitor_(monitor) {}
    ~Carro() {}
    
    int id() const { return id_; }
    int segundos() { return segundos_desde_inicio_volta_; }
    void set_segundos(int segundos) { segundos_desde_inicio_volta_ += segundos; }

    void carrega ();
    void descarrega();
    
  private:
    void Skip();

    int id_;
    int capacity_;
    int segundos_desde_inicio_volta_;
    std::list<Passageiro*> passageiros_;
    Monitor* monitor_;
    
};

#endif /* CARRO_H_ */