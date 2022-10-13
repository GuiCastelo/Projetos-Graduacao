#include "Fila.h"
#include <iostream>

Fila::Fila(int tamanho): tamanhoMaximo(tamanho){
    if(tamanho <= 0)
        throw new invalid_argument("Tamanho de fila invalido");

    datagramas = new Datagrama*[tamanho];
}

Fila::~Fila(){
    for(int i = 0; i < tamanhoAtual; i++)
        delete datagramas[i];
    delete[] datagramas;
}

void Fila::enqueue(Datagrama* d){
    if(tamanhoAtual == tamanhoMaximo){
        throw new overflow_error("Overflow da fila");
        return;
    }

    datagramas[fim++] = d;
    if(fim == tamanhoMaximo)
        fim = 0;
    tamanhoAtual ++;
}

Datagrama* Fila::dequeue(){
    if(tamanhoAtual == 0)
        throw new underflow_error("Underflow da fila");

    Datagrama* temporario = datagramas[comeco];
    datagramas[comeco++] = NULL;
    if(comeco == tamanhoMaximo)
        comeco = 0;
    tamanhoAtual --;
    return temporario;
}

bool Fila::isEmpty(){
    if(tamanhoAtual == 0)
        return true;
    return false;
}

int Fila::getSize(){
    return tamanhoAtual;
}

void Fila::imprimir(){
    if(tamanhoAtual == 0){
        cout << "Fila vazia";
        return;
    }
    cout << "Fila:\n";
    int i = comeco;
    while(i != fim){
        datagramas[i++]->imprimir();
        if(i == tamanhoMaximo)
            i = 0;
    }
}
