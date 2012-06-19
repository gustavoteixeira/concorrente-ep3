#include "monitor.h"
#include "passageiro.h"

static int GET_ID_POR_MAGIA() { return 42; }

struct MonitorCond {
    std::queue<int> delay;
};

Monitor::Monitor(int N) : N_(N) {
    sem_init(&semaforo_, 0, 1);
    /*processos_privado_ = new sem_t[N];
    for(int i = 0; i < N; ++i)
        sem_init(&processos_privado_[i], 0, 1);*/
}

Monitor::~Monitor() {
    sem_destroy(&semaforo_);
    /*for(int i = 0; i < N_; ++i)
        sem_init(&processos_privado_[i], 0, 1);*/
}

void Monitor::wait(bool cv) {
    entrada();
    
    sem_t semaphore;
    sem_init(&semaphore, 0, 0);
    processos_privados_.push(&semaphore);
    saida();
    sem_wait(&semaphore);
    entrada();
    sem_destroy(&semaphore);

    saida();
}

void Monitor::wait(bool cv, Passageiro* rank) {
    entrada();
    
    if(rank->bilhete_dourado()) {
        std::list<Passageiro*>::iterator it = objetos_de_rank_.end();
        while( it!=objetos_de_rank_.begin() && (*it)->bilhete_dourado() )
            it--;
        objetos_de_rank_.insert(it, rank);
    }
    else {
        std::list<Passageiro*>::iterator it = objetos_de_rank_.begin();
        while( it!=objetos_de_rank_.end() && !(*it)->bilhete_dourado() )
            it++;
        objetos_de_rank_.insert(it, rank);
    }
    saida();
    sem_wait(rank->semaforo());
    entrada();

    saida();
}

Passageiro* Monitor::signal(bool cv) {
    entrada();
    
    Passageiro* passageiro = NULL;
    unranked_signal();
    passageiro = ranked_signal();

    saida();
    return passageiro;
}

Passageiro* Monitor::minrank(bool cv) {
    entrada();

    if(!objetos_de_rank_.empty())
        return objetos_de_rank_.front();
    return NULL;

    saida();
}

void Monitor::signal_all(bool cv) {
    entrada();

    while(!processos_privados_.empty())
        unranked_signal();
    while(!objetos_de_rank_.empty())
        ranked_signal();

    saida();
}

void Monitor::empty(bool cv) {
    entrada();

    objetos_de_rank_.clear();

    saida();
}

int Monitor::tamanho_fila_passageiros() {
    entrada();

    if(!processos_privados_.empty()) {
        int size = processos_privados_.size();
        saida();
        return size;
    }
    else if(!objetos_de_rank_.empty()) {
        int size = objetos_de_rank_.size();
        saida();
        return size;
    }

    saida();
    return 0;
}

void Monitor::print_list_passageiros() {
    entrada();

    for(std::list<Passageiro*>::iterator it = objetos_de_rank_.begin(); it != objetos_de_rank_.end(); it++)
        (*it)->imprime_passageiro();

    saida();
}

void Monitor::entrada() {
    sem_wait(&semaforo_);
}

void Monitor::saida() {
    sem_post(&semaforo_);
}

void Monitor::unranked_signal() {
    if(!processos_privados_.empty()) {
        sem_t* semaphore = processos_privados_.front();
        processos_privados_.pop();
        sem_post(semaphore);
        delete semaphore;
    }
}

Passageiro* Monitor::ranked_signal() {
    Passageiro* passageiro = NULL;
    if(!objetos_de_rank_.empty()) {
        passageiro = objetos_de_rank_.front();
        objetos_de_rank_.pop_front();
        sem_post(passageiro->semaforo());
    }
    return passageiro;
}