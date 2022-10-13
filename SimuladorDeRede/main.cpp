#include <iostream>
#include <stdexcept>
#include <list>

#include "Datagrama.h"
#include "Segmento.h"
#include "Fila.h"
#include "FilaComPrioridade.h"
#include "TabelaDeRepasse.h"
#include "Evento.h"
#include "No.h"
#include "Roteador.h"
#include "RoteadorComQoS.h"
#include "Hospedeiro.h"
#include "Chat.h"
#include "Rede.h"
#include "Agendador.h"
#include "PersistenciaDeRede.h"

using namespace std;

int main(){
    string arquivo;
    int instanteInicial;
    Rede* rede;

    cout << "Nome do arquivo: ";
    cin >> arquivo;
    cout << "Instante inicial: ";
    cin >> instanteInicial;

    PersistenciaDeRede* repositorio = new PersistenciaDeRede(arquivo);
    try{
        rede = repositorio->carregar();
    }catch(logic_error* e){
        cout << e->what();
        delete e;
        return 0;
    }
    Agendador* agendador = new Agendador(instanteInicial, rede, 10);

    cout << endl;
    int escolha;
    do{
        cout << "Simulador de Rede\n1) Enviar uma mensagem\n2) Passar tempo\n0) Sair\nEscolha uma opcao: ";
        cin >> escolha;
        if(escolha == 1){
            cout << endl;
            list<Hospedeiro*>* hospedeiros = rede->getHospedeiros();
            list<Hospedeiro*>::iterator i = hospedeiros->begin();
            while(i != hospedeiros->end()){
                cout << "Hospedeiro: " << (*i)->getEndereco() << endl;
                for(unsigned int j = 0; j < (*i)->getChats()->size(); j++){
                    cout << "\tChat: " << (*i)->getChats()->at(j)->getPorta() << endl;
                }
                i++;
            }
            int enderecoHospedeiro, portaChat;
            cout << "Endereco do hospedeiro: ";
            cin >> enderecoHospedeiro;
            cout << "Porta do Chat: ";
            cin >> portaChat;
            Hospedeiro* hospedeiro = dynamic_cast<Hospedeiro*>(rede->getNo(enderecoHospedeiro));
            if(hospedeiro == NULL)
                cout << "Erro: origem desconhecida\n" << endl;
            else{
                Chat* chat = hospedeiro->getChat(portaChat);
                if(chat == NULL)
                    cout << "Erro: origem desconhecida\n" << endl;
                else{
                    string mensagem;
                    cout << "Conteudo:\n" << chat->getTextoCompleto() << "\nMensagem: ";
                    cin >> mensagem;
                    chat->enviar(mensagem);
                    cout << endl;
                }
            }
        }
        else if(escolha == 2){
            int tempoAdicionado;
            cout << "\nQuantidade de tempo: ";
            cin >> tempoAdicionado;
            for(int i = 0; i < tempoAdicionado; i++){
                cout << "\nInstante " << agendador->getInstante() << "\n---\n";
                agendador->processar();
            }
            cout << endl;

        }
    }while(escolha != 0);
    return 0;
}
