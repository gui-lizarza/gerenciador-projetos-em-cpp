#ifndef ATIVIDADEDEESFORCOFIXO_H
#define ATIVIDADEDEESFORCOFIXO_H
#include <iostream>
#include "Atividade.h"

using namespace std;

class AtividadeDeEsforcoFixo : public Atividade {
private:
    int horasNecessarias;

public:
    AtividadeDeEsforcoFixo(string nome, int horasNecessarias);
    virtual ~AtividadeDeEsforcoFixo();

    virtual int getHorasNecessarias();

    int getDuracao();
    double getCusto();

    void imprimir();
};

#endif // ATIVIDADEDEESFORCOFIXO_H
