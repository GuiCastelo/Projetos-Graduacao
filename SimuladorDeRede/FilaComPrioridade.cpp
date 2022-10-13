#include "FilaComPrioridade.h"

FilaComPrioridade::FilaComPrioridade(int tamanho): Fila(tamanho){}

FilaComPrioridade::~FilaComPrioridade(){}

void FilaComPrioridade::enqueue(Datagrama* d, bool prioritario){
    if(tamanhoAtual == tamanhoMaximo)
        throw new overflow_error("Overflow da fila");

    if(!prioritario){
        enqueue(d);
        return;
    }
    /* A partir daqui, consta um codigo que coloca o datagrama prioritario recebido em ultimo lugar dos prioritarios no vetor
       e antes dos nao prioritarios no vetor*/
    int fimDasPrioridades = comeco;
    for(int i = numeroDePrioridades; i > 0; i--){
        fimDasPrioridades ++;
        if(fimDasPrioridades == tamanhoMaximo)
            fimDasPrioridades = 0;
    }

    Datagrama* temporarioProximo = d;
    while(fimDasPrioridades != fim){
        Datagrama* temporarioAtual = datagramas[fimDasPrioridades];
        datagramas[fimDasPrioridades] = temporarioProximo;
        temporarioProximo = temporarioAtual;
        fimDasPrioridades++;
        if(fimDasPrioridades == tamanhoMaximo)
            fimDasPrioridades = 0;
    }
    datagramas[fim] = temporarioProximo;
    numeroDePrioridades++;
    fim++;
    if(fim == tamanhoMaximo)
        fim = 0;
    tamanhoAtual++;
}

Datagrama* FilaComPrioridade::dequeue(){
    if(numeroDePrioridades > 0)
        numeroDePrioridades --;
    Datagrama* temporario = Fila::dequeue();
    return temporario;
}
