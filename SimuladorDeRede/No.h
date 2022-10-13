#ifndef NO_H
#define NO_H

#include "Evento.h"
#include "Fila.h"
#include "FilaComPrioridade.h"
#include "Datagrama.h"

using namespace std;

class Evento;

class No{
public:
    No(int endereco);
    No(int endereco, Fila* fila);
    virtual ~No();

    virtual int getEndereco();

    virtual Evento* processar(int instante) = 0;
    virtual void receber(Datagrama* d);

    virtual void imprimir() = 0;
    static const int TAMANHO_FILA = 5;
protected:
    int endereco;
    Fila* fila;
};

#endif // NO_H
