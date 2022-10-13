#include "Segmento.h"
#include <iostream>

Segmento::Segmento(int portaDeOrigem, int portaDeDestino, string dado)
            : portaDeOrigem(portaDeOrigem), portaDeDestino(portaDeDestino), dado(dado){}

Segmento::~Segmento(){}

int Segmento::getPortaDeOrigem(){
    return portaDeOrigem;
}

int Segmento::getPortaDeDestino(){
    return portaDeDestino;
}

string Segmento::getDado(){
    return dado;
}

void Segmento::imprimir(){
    cout << "Porta de origem: " << portaDeOrigem << " Porta de destino: " << portaDeDestino << " Dado: " << dado << endl;
}
