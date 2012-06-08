#include "monitor.h"

Monitor::Monitor() {
    sem_init(&semaforo_, 0, 1); 
}

Monitor::~Monitor() {
    sem_destroy(&semaforo_);
}

void Monitor::entrada() {
    sem_wait(&semaforo_);
}

void Monitor::saida() {
    sem_post(&semaforo_);
}
