#include "PersistenciaDeRede.h"
#include <iostream>

PersistenciaDeRede::PersistenciaDeRede(string arquivo): arquivo(arquivo){}

PersistenciaDeRede::~PersistenciaDeRede(){}

Rede* PersistenciaDeRede::carregar(){
    Rede* rede = new Rede();
    ifstream leitura;
    leitura.open(arquivo);

    if(leitura.fail())
        throw new logic_error("Arquivo nao encontrado");

    int contadorRoteador, i = 0;

    leitura >> contadorRoteador;

    while(leitura && i < contadorRoteador){
        char leituraCaracter;
        leitura >> leituraCaracter;
        if(leituraCaracter == 'r'){
            int endereco;
            leitura >> endereco;
            Roteador* roteadorNovo = new Roteador(endereco);
            rede->adicionar(roteadorNovo);
            i++;
        }
        else if(leituraCaracter == 'q'){
            int endereco, quantidadePriorizados;
            leitura >> endereco;
            leitura >> quantidadePriorizados;
            RoteadorComQoS* roteadorQoSNovo = new RoteadorComQoS(endereco);
            for(int j = 0; j < quantidadePriorizados; j++){
                int destino;
                leitura >> destino;
                roteadorQoSNovo->priorizar(destino);
            }
            rede->adicionar(roteadorQoSNovo);
            i++;
        }
    }
    if(leitura.fail())
        throw new logic_error("Erro na leitura");

    int contadorHospedeiro = 0;
    i = 0;
    leitura >> contadorHospedeiro;
    while(leitura && i < contadorHospedeiro){
        int endereco, gateway, atraso, quantidadeChats;
        leitura >> endereco;
        leitura >> gateway;
        leitura >> atraso;
        leitura >> quantidadeChats;

        Roteador* roteadorGateway = dynamic_cast<Roteador*>(rede->getNo(gateway));
        Hospedeiro* hospedeiroNovo = new Hospedeiro(endereco, roteadorGateway, atraso);
        for(int j = 0; j < quantidadeChats; j++){
            int porta, enderecoDestino, portaDestino;
            leitura >> porta;
            leitura >> enderecoDestino;
            leitura >> portaDestino;
            hospedeiroNovo->adicionarChat(porta, enderecoDestino, portaDestino);
        }
        rede->adicionar(hospedeiroNovo);
        i++;
    }
    if(leitura.fail())
        throw new logic_error("Erro na leitura");

    i = 0;
    while(leitura && i < contadorRoteador){
        int endereco, enderecoPadrao, atrasoPadrao, quantidadeMapeamentos;
        leitura >> endereco;
        leitura >> enderecoPadrao;
        leitura >> atrasoPadrao;
        leitura >> quantidadeMapeamentos;

        Roteador* roteadorUsado = dynamic_cast<Roteador*>(rede->getNo(endereco));
        Roteador* roteadorPadrao = dynamic_cast<Roteador*>(rede->getNo(enderecoPadrao));
        roteadorUsado->setPadrao(roteadorPadrao, atrasoPadrao);
        for(int j = 0; j < quantidadeMapeamentos; j++){
            int enderecoDestino, enderecoAdjacente, atraso;
            leitura >> enderecoDestino;
            leitura >> enderecoAdjacente;
            leitura >> atraso;
            No* noAdjacente = rede->getNo(enderecoAdjacente);
            try{
                roteadorUsado->mapear(enderecoDestino, noAdjacente, atraso);
            }catch(overflow_error* e){
                delete e;
                throw new logic_error("Nao foi possivel mapear");
            }catch(invalid_argument* e){
                delete e;
                throw new logic_error("Nao foi possivel mapear");
            }
        }
        i++;
    }
    bool teste;
    leitura >> teste;
    if(!leitura.eof())
        throw new logic_error("Erro de leitura");

    leitura.close();
    return rede;
}
