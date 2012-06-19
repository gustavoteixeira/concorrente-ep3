#include "carro.h"
#include "passageiro.h"
#include "worker.h"

#include <time.h>
#include <list>
#include <vector>
#include <cstdlib>
#include <cstdio>

#define NUMERO_CARROS    1
#define CAPACIDADE_CARRO 8
#define NUMERO_MAXIMO_PASSAGEIROS 16

/* Cada passagem por atualiza_carro = 1 unidade de tempo.*/

static void Skip() {
    #ifndef WIN32
	struct timespec req, rem;
	req.tv_sec = 0;
	req.tv_nsec = 5000;
	nanosleep(&req, &rem);
	#endif
}

void* atualiza_carro(Worker *arg) {
    Carro* carro = (Carro*) arg->data();
    carro->set_segundos(0);
    carro->carrega();
    while(true) {
        carro->adiciona_segundos(TEMPO_NUMA_ATUALIZACAO);
        if(carro->segundos() >= TEMPO_NUMA_VOLTA) {
            carro->set_segundos(0);
            carro->descarrega();
            carro->carrega();
        }
		Skip();
    }
    return NULL;
}

void* atualiza_passageiro(Worker* arg) {
    Passageiro* passageiro = (Passageiro*) arg->data();
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

	Worker** carros_threads = new Worker*[NUMERO_CARROS];

    for(int i = 0; i < NUMERO_CARROS; i++) {
        Carro* carro = new Carro(carro_id++, CAPACIDADE_CARRO, &monitor);
        carros.push_back(carro);
		carros_threads[i] = new Worker(atualiza_carro, carro);
		carros_threads[i]->Run();
    }

    while(true) {
        contador_chegada_de_novo_passageiro += taxa_de_chegada;
        if(contador_chegada_de_novo_passageiro >= 1 && monitor.tamanho_fila_passageiros() <= NUMERO_MAXIMO_PASSAGEIROS ) {
			//for(std::list<Carro*>::iterator it = carros.begin(); it != carros.end(); it++)
            //    (*it)->stop();
            //print_dados(&monitor);
            //for(std::list<Carro*>::iterator it = carros.begin(); it != carros.end(); it++)
            //    (*it)->resume();

			Passageiro* passageiro = new Passageiro(passageiro_id++, &monitor);
			(new Worker(atualiza_passageiro, passageiro))->Run();
            contador_chegada_de_novo_passageiro = 0;
        }
		Skip();
    }
    return 0;
}
