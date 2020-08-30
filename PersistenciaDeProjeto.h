#ifndef PERSISTENCIADEPROJETO_H
#define PERSISTENCIADEPROJETO_H
#include "Projeto.h"
#include <string>

using namespace std;

class PersistenciaDeProjeto
{
    public:
        PersistenciaDeProjeto();
        virtual ~PersistenciaDeProjeto();

        Projeto* carregar(string arquivo);
        void salvar(Projeto* p, string arquivo);
};

#endif // PERSISTENCIADEPROJETO_H
