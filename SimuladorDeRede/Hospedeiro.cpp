#include "Hospedeiro.h"
#include <stdexcept>
#include <iostream>

Hospedeiro::Hospedeiro(int endereco, Roteador* gateway, int atraso) : No(endereco){
    this->gateway = gateway;
    atrasoGateway = atraso;
    chats = new vector<Chat*>;
}

Hospedeiro::~Hospedeiro(){
    while (!chats->empty()){
        Chat* ultimo = chats->back();
        chats->pop_back();
        delete ultimo;
    }
    delete chats;
}

void Hospedeiro::adicionarChat(int porta, int enderecoDestino, int portaDestino){
    for(unsigned int i = 0; i < chats->size(); i++)
        if(chats->at(i)->getPorta() == porta)
            throw new logic_error("Porta do hospedeiro ja possui chat");
    Chat* chatNovo = new Chat(this, porta, enderecoDestino, portaDestino);
    chats->push_back(chatNovo);
}

vector<Chat*>* Hospedeiro::getChats(){
    return chats;
}

Chat* Hospedeiro::getChat(int porta){
    for(unsigned int i = 0; i < chats->size(); i++)
        if(chats->at(i)->getPorta() == porta)
            return chats->at(i);
    return NULL;
}

Evento* Hospedeiro::processar(int instante){
    if(fila->isEmpty())
        return NULL;
    cout << "Hospedeiro " << endereco << endl;

    Datagrama* retirado = fila->dequeue();
    if(retirado->getDestino() == endereco){
        Chat* chatProcurado = getChat(retirado->getSegmento()->getPortaDeDestino());
        if(chatProcurado != NULL){
            chatProcurado->receber(retirado);
            cout << "\tMensagem recebida\n" << chatProcurado->getTextoCompleto() << endl;
        }
        else{
            cout << "\tSem chat: ";
            retirado->imprimir();
            delete retirado;
        }
        return NULL;
    }
    cout << "\tMensagem enviada" << endl;
    Evento* eventoNovo = new Evento(instante + atrasoGateway, gateway, retirado);
    return eventoNovo;
}

void Hospedeiro::imprimir(){
}
