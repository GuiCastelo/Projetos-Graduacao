#include "Rede.h"
#include <iostream>

Rede::Rede(){
    nos = new list<No*>;
}

Rede::~Rede(){
    list<No*>::iterator i = nos->begin();

    while(i != nos->end()){
        delete (*i);
        i++;
    }
    delete nos;
}

void Rede::adicionar(No* n){
    list<No*>::iterator i = nos->begin();

    while(i != nos->end()){
        if((*i)->getEndereco() == n->getEndereco()){
            throw new logic_error("No ja na rede");
            return;
        }
        i++;
    }
    nos->push_back(n);
}

No* Rede::getNo(int endereco){
    list<No*>::iterator i = nos->begin();

    while(i != nos->end()){
        if((*i)->getEndereco() == endereco)
            return (*i);
        i++;
    }
    return NULL;
}

list<No*>* Rede::getNos(){
    return nos;
}

list<Hospedeiro*>* Rede::getHospedeiros(){
    list<Hospedeiro*>* hospedeiros = new list<Hospedeiro*>;
    list<No*>::iterator i = nos->begin();

    while(i != nos->end()){
        Hospedeiro* hospedeiroTemporario = dynamic_cast<Hospedeiro*>(*i);
        if(hospedeiroTemporario != NULL)
            hospedeiros->push_back(hospedeiroTemporario);
        i++;
    }
    return hospedeiros;
}

void Rede::imprimir(){}
