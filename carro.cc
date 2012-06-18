#include "carro.h"

void Carro::carrega() {
    MonitorCond* cv;
    Passageiro* passageiro;
    while(passageiros_.size() < capacity_) {
        passageiro = monitor_->signal(cv);
        if(passageiro == NULL)
            Skip();
        else
            passageiros_.push_back(passageiro);
    }
}

void Carro::descarrega() {
    MonitorCond* cv;
    for(std::list<Passageiro*>::iterator it = passageiros_.begin(); it != passageiros_.end(); it++)
        sem_post( (*it)->semaforo() );
    passageiros_.clear();
}

void Carro::Skip() {
    #ifndef WIN32
    struct timespec req, rem;
    req.tv_sec = 0;
    req.tv_nsec = 5000;
    nanosleep(&req, &rem);
    #endif
}