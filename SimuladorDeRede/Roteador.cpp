#include "Roteador.h"
#include <stdexcept>
#include <iostream>

Roteador::Roteador(int endereco): No(endereco){
    tabela = new TabelaDeRepasse(TAMANHO_TABELA);
}

Roteador::Roteador(int endereco, Fila* fila): No(endereco, fila){
    tabela = new TabelaDeRepasse(TAMANHO_TABELA);
}

Roteador::~Roteador(){
    delete tabela;
}

void Roteador::mapear(int endereco, No* adjacente, int atraso){
    tabela->mapear(endereco, adjacente, atraso);
}

void Roteador::setPadrao(No* padrao, int atraso){
    tabela->setPadrao(padrao, atraso);
}

Evento* Roteador::processar(int instante){
    if(fila->isEmpty())
        return NULL;

    cout << "Roteador " << endereco << endl;

    Datagrama* datagramaRetirado = fila->dequeue();

    if(datagramaRetirado->getDestino() == endereco){
        cout << "\tRecebido: " << datagramaRetirado->getSegmento()->getDado() << endl;
        delete datagramaRetirado;
        return NULL;
    }
    int atraso;
    No* noDestino = tabela->getProximoSalto(datagramaRetirado->getDestino(), atraso);

    if(noDestino == NULL){
        cout << "\tSem proximo: ";
        datagramaRetirado->imprimir();
        delete datagramaRetirado;
        return NULL;
    }
    cout << "\tRepassado para " << noDestino->getEndereco() << " (instante " << instante + atraso << "): ";
    datagramaRetirado->imprimir();

    Evento* eventoCriado = new Evento(instante + atraso, noDestino, datagramaRetirado);

    return eventoCriado;
}

void Roteador::imprimir(){}
