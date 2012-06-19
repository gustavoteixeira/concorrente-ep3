#include "carro.h"

#include <cstdio>

void Carro::carrega() {
    Passageiro* passageiro;
    while(passageiros_.size() < capacity_) {
        passageiro = monitor_->signal(false);
        if(passageiro == NULL)
            Skip();
        else
            passageiros_.push_back(passageiro);
    }
}

void Carro::descarrega() {
    for(std::list<Passageiro*>::iterator it = passageiros_.begin(); it != passageiros_.end(); it++)
        sem_post( (*it)->semaforo() );
    passageiros_.clear();
}

void Carro::stop() {
    sem_wait(&semaforo_);
}

void Carro::resume() {
    sem_post(&semaforo_);
}

void Carro::Skip() {
    #ifndef WIN32
    struct timespec req, rem;
    req.tv_sec = 0;
    req.tv_nsec = 5000;
    nanosleep(&req, &rem);
    #endif
}
