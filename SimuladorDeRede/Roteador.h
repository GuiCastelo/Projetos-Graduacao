#ifndef ROTEADOR_H
#define ROTEADOR_H

#include "No.h"
#include "TabelaDeRepasse.h"

using namespace std;

class Roteador : public No{
public:
    Roteador(int endereco);
    virtual ~Roteador();

    virtual void mapear(int endereco, No* adjacente, int atraso);
    virtual void setPadrao(No* padrao, int atraso);

    virtual Evento* processar(int instante);

    static const int TAMANHO_TABELA = 10;

    virtual void imprimir();
protected:
    TabelaDeRepasse* tabela;
    Roteador(int endereco, Fila* fila);
};

#endif // ROTEADOR_H
