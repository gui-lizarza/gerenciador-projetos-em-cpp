#include "AtividadeDeEsforcoFixo.h"
#include "Pessoa.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

AtividadeDeEsforcoFixo::AtividadeDeEsforcoFixo(string nome, int horasNecessarias) : Atividade(nome) {
    if (horasNecessarias <= 0)
        throw new invalid_argument ("Horas necessarias invalidas");

    this->horasNecessarias = horasNecessarias;
}

AtividadeDeEsforcoFixo::~AtividadeDeEsforcoFixo() {

}

int AtividadeDeEsforcoFixo::getHorasNecessarias() {
    return horasNecessarias;
}

int AtividadeDeEsforcoFixo::getDuracao() {
    //Teste de pessoas em recurso
    bool temPessoas = false;
    for (int i = 0; i < quantidadeDeRecursos && temPessoas == false; i++) {
        Pessoa *p = dynamic_cast<Pessoa*>(recursos[i]);
            if (p != NULL)
                temPessoas = true;
    }
    if (temPessoas == false)
        throw new logic_error ("Atividade de trabalho fixo sem pessoas");

    if (terminou == true)
        return duracaoReal;

    int horasAdicionadas = 0;
    for (int i = 0; i < quantidadeDeRecursos; i++) {
            Pessoa *p = dynamic_cast<Pessoa*>(recursos[i]);
            if (p != NULL)
                horasAdicionadas = horasAdicionadas + p->getHorasDiarias();
    }
        return ceil((double)horasNecessarias/(double)horasAdicionadas);
}

double AtividadeDeEsforcoFixo::getCusto() {
    if (quantidadeDeRecursos == 0)
        return 0;
    else {
        double custo = 0;
        for (int i = 0; i < quantidadeDeRecursos; i++)
                custo = custo + recursos[i]->getCusto(getDuracao());
        return custo;
    }
}

void AtividadeDeEsforcoFixo::imprimir() {
        cout << getNome() << " - " << getDuracao() << " dias - R$" << getCusto() << endl;

}
