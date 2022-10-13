#include "TabelaDeRepasse.h"
#include <iostream>

TabelaDeRepasse::TabelaDeRepasse(int tamanho): tamanhoMaximo(tamanho){
    if(tamanhoMaximo <= 0)
        throw new invalid_argument("Tamanho de tabela invalido");

    nosAdjacentes = new No*[tamanhoMaximo];
    enderecos = new int[tamanhoMaximo];
    atrasos = new int[tamanhoMaximo];
    padrao = NULL;
    atrasoPadrao = 0;
}

TabelaDeRepasse::~TabelaDeRepasse(){
    delete[] nosAdjacentes;
    delete[] atrasos;
    delete[] enderecos;
}

void TabelaDeRepasse::mapear(int endereco, No* adjacente, int atraso){
    if(tamanhoAtual == tamanhoMaximo){
        throw new overflow_error("Overflow da tabela");
        return;
    }
    for(int i = 0; i < tamanhoAtual; i++)
        if(endereco == enderecos[i])
            throw new invalid_argument("Endereco repetido");
    enderecos[tamanhoAtual] = endereco;
    nosAdjacentes[tamanhoAtual] = adjacente;
    atrasos[tamanhoAtual] = atraso;
    tamanhoAtual ++;
}

No** TabelaDeRepasse::getAdjacentes(){
    return nosAdjacentes;
}

int TabelaDeRepasse::getQuantidadeDeAdjacentes(){
    return tamanhoAtual;
}

void TabelaDeRepasse::setPadrao(No* padrao, int atraso){
    this->padrao = padrao;
    atrasoPadrao = atraso;
}

No* TabelaDeRepasse::getProximoSalto(int endereco, int& atraso){
    for(int i = 0; i < tamanhoAtual; i++)
        if(endereco == enderecos[i]){
            atraso = atrasos[i];
            return nosAdjacentes[i];
        }
    atraso = atrasoPadrao;
    return padrao;
}

void TabelaDeRepasse::imprimir(){}
