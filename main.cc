#include "carro.h"
#include "passageiro.h"
#include <map>

#define NUMERO_CARROS    2
#define CAPACIDADE_CARRO 8

int main(int argc, char** argv) {
    int carro_id = 0, passageiro_id = 0;
    std::map<int, Carro*> carros_livres, carros_ocupados;
    for(int i = 0; i < NUMERO_CARROS; i++) {
        Carro carro = Carro(carro_id++, CAPACIDADE_CARRO);
        carros_livres[i] = &carro;
    }
    while(true) {
    }
    return 0;
}