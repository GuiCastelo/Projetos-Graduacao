#ifndef EVENTO_H
#define EVENTO_H

#include "Datagrama.h"
#include "No.h"

using namespace std;

class No;

class Evento{
public:
    Evento(int instante, No* destino, Datagrama* d);
    virtual ~Evento();

    virtual int getInstante();
    virtual No* getDestino();
    virtual Datagrama* getDatagrama();

    virtual void imprimir();
private:
    int instante;
    No* destino;
    Datagrama* data;
};

#endif // EVENTO_H
