#include "Chat.h"
#include <stdexcept>

Chat::Chat(Hospedeiro* h, int porta, int enderecoDestino, int portaDestino)
        : hospedeiroChat(h), porta(porta), enderecoDestino(enderecoDestino), portaDestino(portaDestino){
    if(h == NULL)
        throw new invalid_argument("Hospedeiro invalido");
    textoCompleto = "";
}

Chat::~Chat(){}

int Chat::getPorta(){
    return porta;
}

void Chat::enviar(string texto){
    Segmento* segmentoEnviado = new Segmento(porta, portaDestino, texto);
    Datagrama* datagramaEnviado = new Datagrama(hospedeiroChat->getEndereco(), enderecoDestino, segmentoEnviado);

    hospedeiroChat->receber(datagramaEnviado);

    textoCompleto += "\t\tEnviado: " + texto + "\n";
}

void Chat::receber(Datagrama* d){
    textoCompleto += "\t\tRecebido: " + d->getSegmento()->getDado() + "\n";
    delete d;
}

string Chat::getTextoCompleto(){
    return textoCompleto;
}

void Chat::imprimir(){}
