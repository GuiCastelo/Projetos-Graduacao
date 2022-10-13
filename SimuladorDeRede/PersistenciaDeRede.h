#ifndef PERSISTENCIADEREDE_H
#define PERSISTENCIADEREDE_H

#include "Rede.h"
#include <fstream>
#include <stdexcept>

using namespace std;

class PersistenciaDeRede{
public:
    PersistenciaDeRede(string arquivo);
    virtual ~PersistenciaDeRede();

    virtual Rede* carregar();
private:
    string arquivo;
};

#endif // PERSISTENCIADEREDE_H
