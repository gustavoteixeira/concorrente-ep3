#include "carro.h"

#include <cstdio>

void Carro::carrega() {
    Passageiro* passageiro;
    
	sem_wait(&semaforo_);
    while(passageiros_.size() < capacity_) {
		sem_post(&semaforo_);
        passageiro = monitor_->signal(false);
		sem_wait(&semaforo_);
        if(passageiro == NULL)
            Skip();
        else
            passageiros_.push_back(passageiro);
    }
	andando_ = true;
    sem_post(&semaforo_);
}

void Carro::descarrega() {
    sem_wait(&semaforo_);
	andando_ = false;
    for(std::list<Passageiro*>::iterator it = passageiros_.begin(); it != passageiros_.end(); it++)
        sem_post( (*it)->semaforo() );
    passageiros_.clear();
    sem_post(&semaforo_);
}

void Carro::stop() {
    sem_wait(&semaforo_);
}

void Carro::resume() {
    sem_post(&semaforo_);
}

void Carro::print() {
    sem_wait(&semaforo_);
	printf("Carro %d: %u passageiros. Em Movimento? : %c\n", id_, passageiros_.size(), andando_ ? 'S' : 'N');
	int i = 0;
	for(std::list<Passageiro*>::iterator it = passageiros_.begin(); it != passageiros_.end(); it++) {
		(*it)->imprime_passageiro();
		if(i % 8 == 7) printf("\n");
	}
	printf("\n");
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
