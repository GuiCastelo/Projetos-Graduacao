#ifndef ROTEADORCOMQOS_H
#define ROTEADORCOMQOS_H

#include <vector>
#include "Roteador.h"

using namespace std;

class RoteadorComQoS : public Roteador{
public:
    RoteadorComQoS(int endereco);
    virtual ~RoteadorComQoS();

    virtual void priorizar(int destino);
    virtual vector<int>* getDestinosPriorizados();

    virtual void receber(Datagrama* d);
private:
    FilaComPrioridade* filaComPrioridade;
    vector<int>* destinosPriorizados;
};

#endif // ROTEADORCOMQOS_H
