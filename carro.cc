#include "carro.h"

void Carro::carrega() {
    MonitorCond* cv;
    for(int i = 0; i < capacity_; i++)
        monitor->signal(cv);
}

void Carro::descarrega() {

}

void Carro::volta() {
    
}