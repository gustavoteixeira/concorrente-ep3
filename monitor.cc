#include "monitor.h"

static int GET_ID_POR_MAGIA() { return 42; }

struct MonitorCond {
    std::queue<pthread_t> delay;
};

struct QueueItem {
    pthread_t thread_id;
    sem_t* semaphore;
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
    delete[] processos_privado_;
}

void Monitor::wait(MonitorCond* cv) {
    entrada();

    sem_t semaphore;
    processos_privados_.push(&semaphore);
    saida();
    sem_wait(&semaphore);
    entrada();

    saida();
}

void Monitor::signal(MonitorCond* cv) {
    entrada();

    if(!processos_privados_.empty()) {
        sem_t* semaphore = processos_privados_.front();
        processos_privados_.pop();
        sem_post(semaphore);
    }

    saida();
}

void Monitor::entrada() {
    sem_wait(&semaforo_);
}

void Monitor::saida() {
    sem_post(&semaforo_);
}
