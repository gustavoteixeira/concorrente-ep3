#include "passageiro.h"

#include <cstdio>

void Passageiro::pega_carona() {
	printf("Passageiro %d: pega_carota-ini\n", id_);
    monitor_->wait(false, this);
    sem_wait(&semaforo_);
    voltas_dadas_++;
	printf("Passageiro %d: pega_carota-fim\n", id_);
}

void Passageiro::imprime_passageiro() {
    if(bilhete_dourado_)
        printf("D%dK%d", id_, voltas_dadas_);
    else
        printf(" %dK%d", id_, voltas_dadas_);
}
