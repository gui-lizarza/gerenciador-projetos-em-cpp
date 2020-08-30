#ifndef ATIVIDADEDEPRAZOFIXO_H
#define ATIVIDADEDEPRAZOFIXO_H
#include <iostream>
#include "Atividade.h"

using namespace std;

class AtividadeDePrazoFixo : public Atividade {
private:
    int dias;

public:
    AtividadeDePrazoFixo(string nome, int dias);
    virtual ~AtividadeDePrazoFixo();

    virtual int getPrazo();

    int getDuracao();
    double getCusto();

    void imprimir();
};

#endif // ATIVIDADEDEPRAZOFIXO_H
