#ifndef AGENDADOR_H
#define AGENDADOR_H

#include "Datagrama.h"
#include "Rede.h"

using namespace std;

class Agendador{
public:
    Agendador(int instanteInicial, Rede* rede, int tamanho);
    virtual ~Agendador();

    virtual bool agendar(int instante, No* n, Datagrama* d);
    virtual void processar();
    virtual int getInstante();
private:
    int instante;
    Rede* rede;
    int tamanhoMaximo;
    Evento** eventos;
    int quantidadeDeEventos = 0;
};

#endif // AGENDADOR_H
