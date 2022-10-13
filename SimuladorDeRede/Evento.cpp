#include "Evento.h"

Evento::Evento(int instante, No* destino, Datagrama* d): instante(instante), destino(destino), data(d){}

Evento::~Evento(){}

int Evento::getInstante(){
    return instante;
}

No* Evento::getDestino(){
    return destino;
}

Datagrama* Evento::getDatagrama(){
    return data;
}

void Evento::imprimir(){

}
