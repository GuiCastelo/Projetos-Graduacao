#include "Datagrama.h"
#include <iostream>

Datagrama::Datagrama(int origem, int destino, Segmento* dado)
            : origem(origem), destino(destino), segmento(dado){}

Datagrama::~Datagrama(){
    delete segmento;
}

int Datagrama::getOrigem(){
    return origem;
}

int Datagrama::getDestino(){
    return destino;
}

Segmento* Datagrama::getSegmento(){
    return segmento;
}

void Datagrama::imprimir(){
    cout << "Origem: " << origem << ":" << segmento->getPortaDeOrigem() << ", Destino: " << destino << ":" << segmento->getPortaDeDestino() << ", " << segmento->getDado() << endl;
}
