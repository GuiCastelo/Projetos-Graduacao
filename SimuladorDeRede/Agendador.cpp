#include "Agendador.h"

Agendador::Agendador(int instanteInicial, Rede* rede, int tamanho)
            : instante(instanteInicial), rede(rede), tamanhoMaximo(tamanho){
    eventos = new Evento*[tamanho];
}

Agendador::~Agendador(){
    for(int i = 0; i < quantidadeDeEventos; i++)
        delete eventos[i];
    delete[] eventos;
}

bool Agendador::agendar(int instante, No* n, Datagrama* d){
    if(quantidadeDeEventos == tamanhoMaximo)
        return false;

    Evento *eventoNovo = new Evento(instante, n, d);
    eventos[quantidadeDeEventos++] = eventoNovo;
    return true;
}

void Agendador::processar(){
    for(int i = 0; i < quantidadeDeEventos; i++)
        if(eventos[i]->getInstante() == instante){
            eventos[i]->getDestino()->receber(eventos[i]->getDatagrama());
            delete eventos[i];
            for(int j = i + 1; j < quantidadeDeEventos; j++)
                eventos[j - 1] = eventos[j];
            quantidadeDeEventos--;
            i--;
        }

    list<No*>* nosRede = rede->getNos();
    list<No*>::iterator i = nosRede->begin();

    while(i != nosRede->end()){
        Evento* eventoNovo = (*i)->processar(instante);
        if(eventoNovo != NULL && quantidadeDeEventos < tamanhoMaximo)
            eventos[quantidadeDeEventos++] = eventoNovo;
        i++;
    }
    instante++;
}

int Agendador::getInstante(){
    return instante;
}
