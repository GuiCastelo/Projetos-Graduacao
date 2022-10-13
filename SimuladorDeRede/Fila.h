#ifndef FILA_H
#define FILA_H

#include "Datagrama.h"
#include <stdexcept>

using namespace std;

class Fila{
public:
    Fila(int tamanho);
    virtual ~Fila();

    virtual void enqueue(Datagrama* d);
    virtual Datagrama* dequeue();
    virtual bool isEmpty();
    virtual int getSize();

    virtual void imprimir();
protected:
    int tamanhoMaximo;
    int tamanhoAtual = 0;
    int comeco = 0;
    int fim = 0;
    Datagrama** datagramas;
};

#endif // FILA_H
