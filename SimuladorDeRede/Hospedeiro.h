#ifndef HOSPEDEIRO_H
#define HOSPEDEIRO_H

#include "No.h"
#include "Chat.h"
#include "Roteador.h"
#include <vector>

using namespace std;

class Chat;

class Hospedeiro : public No{
public:
    Hospedeiro(int endereco, Roteador* gateway, int atraso);
    virtual ~Hospedeiro();

    virtual void adicionarChat(int porta, int enderecoDestino, int portaDestino);
    virtual vector<Chat*>* getChats();
    virtual Chat* getChat(int porta);

    virtual Evento* processar(int instante);

    virtual void imprimir();
private:
    Roteador* gateway;
    int atrasoGateway;
    vector<Chat*>* chats;
};

#endif // HOSPEDEIRO_H
