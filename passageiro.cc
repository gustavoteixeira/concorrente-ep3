#include "passageiro.h"

void Passageiro::pega_carona() {
    MonitorCond* cv;
    monitor->wait(cv);
}

void Passageiro::dar_voltas() {

}