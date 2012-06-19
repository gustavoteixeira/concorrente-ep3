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

#include <cstdio>

struct MonitorCond;

class Carro {
  public:
    Carro(int id, size_t capacity, Monitor* monitor):
		andando_(false),
        id_(id),
        capacity_(capacity),
        segundos_desde_inicio_volta_(0),
        monitor_(monitor) { sem_init(&semaforo_, 0, 1); }
    ~Carro() { sem_destroy(&semaforo_); }
    
    int id() const { return id_; }
    double segundos() { return segundos_desde_inicio_volta_; }
    void set_segundos(double segundos) { segundos_desde_inicio_volta_ = segundos; }
    void adiciona_segundos(double segundos) { segundos_desde_inicio_volta_ += segundos; }

    void carrega ();
    void descarrega();

    void stop();
    void resume();

	void set_andando(bool b) { andando_ = b; }

	void print();
    
  private:
    void Skip();

	bool andando_;
    int id_;
    size_t capacity_;
    double segundos_desde_inicio_volta_;
    std::list<Passageiro*> passageiros_;
    sem_t semaforo_;
    Monitor* monitor_;
    
};

#endif /* CARRO_H_ */
