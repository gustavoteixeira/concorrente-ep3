#include "carro.h"
#include "passageiro.h"

#include <time.h>
#include <list>
#include <vector>
#include <cstdlib>

#define NUMERO_CARROS    2
#define CAPACIDADE_CARRO 8
#define NUMERO_MAXIMO_PASSAGEIROS 256

/* Cada passagem por atualiza_carro = 1 unidade de tempo.*/

void* atualiza_carro(void *arg) {
    Carro* carro = (Carro*) arg;
    carro->set_segundos(0);
    carro->carrega();
    while(true) {
        carro->adiciona_segundos(TEMPO_NUMA_ATUALIZACAO);
        if(carro->segundos() >= TEMPO_NUMA_VOLTA) {
            carro->set_segundos(0);
            carro->descarrega();
            carro->carrega();
        }
    }
    return NULL;
}

void* atualiza_passageiro(void* arg) {
    Passageiro* passageiro = (Passageiro*) arg;
    passageiro->pega_carona();
    passageiro->pega_carona();
    delete passageiro;
    return NULL;
}

void print_dados(Monitor* monitor) {
    printf("Tamanho da fila de passageiros: %d\n", monitor->tamanho_fila_passageiros());
    monitor->print_list_passageiros();
    printf("\n");
}

int main(int argc, char** argv) {
    Monitor monitor = Monitor(0);
    int carro_id = 0, passageiro_id = 0;
    int chance = 0;
    double taxa_de_chegada = 0.25, contador_chegada_de_novo_passageiro = 0;
    std::list<Carro*> carros;
    pthread_t *carros_threads, *passageiros_threads;
    pthread_attr_t carros_atributo, passageiros_atributo;

    carros_threads = static_cast<pthread_t*>(malloc((NUMERO_CARROS)*sizeof( *(carros_threads) )));
    if(!carros_threads)
        return 1;
    passageiros_threads = static_cast<pthread_t*>(malloc((NUMERO_MAXIMO_PASSAGEIROS)*sizeof( *(passageiros_threads) )));
    if(!passageiros_threads)
        return 1;

    pthread_attr_init(&carros_atributo);
    pthread_attr_init(&passageiros_atributo);
    pthread_attr_setdetachstate(&carros_atributo, PTHREAD_CREATE_DETACHED);
    pthread_attr_setdetachstate(&passageiros_atributo, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < NUMERO_CARROS; i++) {
        Carro carro = Carro(carro_id++, CAPACIDADE_CARRO, &monitor);
        carros.push_back(&carro);
        pthread_create(&carros_threads[i], &carros_atributo, atualiza_carro, (void*) &carro);
    }

    while(true) {
        contador_chegada_de_novo_passageiro += taxa_de_chegada;
        if(contador_chegada_de_novo_passageiro >= 1 && monitor.tamanho_fila_passageiros() <= NUMERO_MAXIMO_PASSAGEIROS ) {
            for(std::list<Carro*>::iterator it = carros.begin(); it != carros.end(); it++)
                (*it)->stop();
            print_dados(&monitor);
            for(std::list<Carro*>::iterator it = carros.begin(); it != carros.end(); it++)
                (*it)->resume();
            Passageiro passageiro = Passageiro(passageiro_id++, &monitor);
            pthread_create(&passageiros_threads[passageiro_id - 1], &passageiros_atributo, atualiza_passageiro, (void*) &passageiro);
            contador_chegada_de_novo_passageiro = 0;
        }
    }
    return 0;
}