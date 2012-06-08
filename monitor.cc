#include "monitor.h"
#include <queue>

static int GET_ID_POR_MAGIA() { return 42; }


struct MonitorCond {
    std::queue<int> delay;
};

Monitor::Monitor(int N) : N_(N) {
    sem_init(&semaforo_, 0, 1);
    processos_privado_ = new sem_t[N];
    for(int i = 0; i < N; ++i)
        sem_init(&processos_privado_[i], 0, 1);
}

Monitor::~Monitor() {
    sem_destroy(&semaforo_);
    for(int i = 0; i < N_; ++i)
        sem_init(&processos_privado_[i], 0, 1);
}

void Monitor::wait(MonitorCond* cv) {
    entrada();

    int id = GET_ID_POR_MAGIA();
    cv->delay.push(id);
    saida();
    sem_wait(&processos_privado_[id]);
    entrada();

    saida();
}

void Monitor::signal(MonitorCond* cv) {
    entrada();

    if(!cv->delay.empty()) {
        int id = cv->delay.front();
        cv->delay.pop();
        sem_post(&semaforo_);
    }

    saida();
}

void Monitor::entrada() {
    sem_wait(&semaforo_);
}

void Monitor::saida() {
    sem_post(&semaforo_);
}
