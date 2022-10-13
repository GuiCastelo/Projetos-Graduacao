#ifndef TABELADEREPASSE_H
#define TABELADEREPASSE_H

#include <stdexcept>
#include "No.h"

using namespace std;

class TabelaDeRepasse{
public:
    TabelaDeRepasse(int tamanho);
    virtual ~TabelaDeRepasse();

    virtual void mapear(int endereco, No* adjacente, int atraso);
    virtual No** getAdjacentes();
    virtual int getQuantidadeDeAdjacentes();

    virtual void setPadrao(No* padrao, int atraso);

    virtual No* getProximoSalto(int endereco, int& atraso);

    virtual void imprimir();
private:
    int tamanhoMaximo;
    int tamanhoAtual = 0;
    No* padrao;
    int atrasoPadrao;
    No** nosAdjacentes;
    int* enderecos;
    int* atrasos;
};

#endif // TABELADEREPASSE_H
