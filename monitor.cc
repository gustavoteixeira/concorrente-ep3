#include "monitor.h"

Monitor::Monitor() {
    sem_init(&semaforo_, 0, 0); 
}

Monitor::~Monitor() {
    sem_destroy(&semaforo_);
}