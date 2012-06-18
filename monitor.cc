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

void Monitor::wait(MonitorCond* cv) {
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

void Monitor::wait(MonitorCond* cv, Passageiro* rank) {
    entrada();

    if(rank->bilhete_dourado()) {
        std::list<Passageiro*>::iterator it = objetos_de_rank_.end();
        while( it!=objetos_de_rank_.begin() && (difftime(*rank->tempo_de_chegada(), *(*it)->tempo_de_chegada())) > 0 )
            it--;
        objetos_de_rank_.insert(it, rank);
    }
    else {
        std::list<Passageiro*>::iterator it = objetos_de_rank_.begin();
        while( it!=objetos_de_rank_.end() && !(*it)->bilhete_dourado()
               && (difftime(*rank->tempo_de_chegada(), *(*it)->tempo_de_chegada())) > 0 )
            it++;
        objetos_de_rank_.insert(it, rank);
    }
    saida();
    sem_wait(rank->semaforo());
    entrada();

    saida();
}

Passageiro* Monitor::signal(MonitorCond* cv) {
    entrada();

    Passageiro* passageiro = NULL;
    unranked_signal();
    passageiro = ranked_signal();

    saida();
    return passageiro;
}

Passageiro* Monitor::minrank(MonitorCond* cv) {
    if(!objetos_de_rank_.empty())
        return objetos_de_rank_.front();
}

void Monitor::signal_all(MonitorCond* cv) {
    while(!processos_privados_.empty())
        unranked_signal();
    while(!objetos_de_rank_.empty())
        ranked_signal();
}

void Monitor::empty(MonitorCond* cv) {
    objetos_de_rank_.clear();
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