#include "passageiro.h"

#include <cstdio>

void Passageiro::pega_carona() {
    monitor_->wait(false, this);
    sem_wait(&semaforo_);
    voltas_dadas_++;
}

void Passageiro::imprime_passageiro() {
    if(bilhete_dourado_)
        printf("D%5.dK%d", id_, voltas_dadas_);
    else
        printf(" %5.dK%d", id_, voltas_dadas_);
}
