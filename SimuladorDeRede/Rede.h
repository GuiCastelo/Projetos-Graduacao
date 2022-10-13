#ifndef REDE_H
#define REDE_H

#include "RoteadorComQoS.h"
#include "Hospedeiro.h"
#include <list>

using namespace std;

class Rede{
public:
    Rede();
    virtual ~Rede();

    virtual void adicionar(No* n);
    virtual No* getNo(int endereco);
    virtual list<No*>* getNos();
    virtual list<Hospedeiro*>* getHospedeiros();

    virtual void imprimir();
private:
    list<No*>* nos;
};

#endif // REDE_H
