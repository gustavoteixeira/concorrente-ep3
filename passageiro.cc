#include "passageiro.h"

void Passageiro::pega_carona() {
    MonitorCond* cv;
    monitor_->wait(cv, this);
    sem_wait(&semaforo_);
    voltas_dadas_++;
}

void Passageiro::imprime_passageiro() {
    if(bilhete_dourado_)
        printf("D%dK%d", id_, voltas_dadas_);
    else
        printf(" %dK%d", id_, voltas_dadas_);
}