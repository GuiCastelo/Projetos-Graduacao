#include "RoteadorComQoS.h"
#include <iostream>

RoteadorComQoS::RoteadorComQoS(int endereco): Roteador(endereco, filaComPrioridade = new FilaComPrioridade(TAMANHO_FILA)){
    destinosPriorizados = new vector<int>();
}

RoteadorComQoS::~RoteadorComQoS(){
    delete destinosPriorizados;
}

void RoteadorComQoS::priorizar(int destino){
    destinosPriorizados->push_back(destino);
}

vector<int>* RoteadorComQoS::getDestinosPriorizados(){
    return destinosPriorizados;
}

void RoteadorComQoS::receber(Datagrama* d){
    bool prioridade = 0;

    for(unsigned int i = 0; i < destinosPriorizados->size(); i++){
        if(destinosPriorizados->at(i) == d->getDestino())
            prioridade = 1;
    }

    try{
        filaComPrioridade->enqueue(d, prioridade);
    }catch(overflow_error *e){
        cout << "\tFila em " << endereco << " estorou\n";
        delete d;
        delete e;
    }
}
