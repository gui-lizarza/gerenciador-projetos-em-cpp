#include "AtividadeDePrazoFixo.h"
#include <iostream>
#include <stdexcept>

using namespace std;

AtividadeDePrazoFixo::AtividadeDePrazoFixo(string nome, int dias) : Atividade(nome) {
    if (dias <= 0)
        throw new invalid_argument ("Quantidade de dias invalida");

    this->dias = dias;
}

AtividadeDePrazoFixo::~AtividadeDePrazoFixo() {

}

int AtividadeDePrazoFixo::getPrazo() {
    return dias;
}

int AtividadeDePrazoFixo::getDuracao() {
    if (terminou == true)
        return duracaoReal;
    else return dias;
}

double AtividadeDePrazoFixo::getCusto() {
    if (quantidadeDeRecursos == 0)
        return 0;
    else {
        try {
             double custo = 0;
             for (int i = 0; i < quantidadeDeRecursos; i++)
                 custo = custo + recursos[i]->getCusto(getDuracao());
             return custo;
        }
        catch (invalid_argument *e) {
            cout << "Erro: " << e->what() << endl;
            delete e;
        }
    }
}

void AtividadeDePrazoFixo::imprimir() {
    try {
        cout << getNome() << " - " << getDuracao() << " dias - R$" << getCusto() << endl;
    }
    catch (logic_error *e) {
        cout << getNome() << " - " << getDuracao() << " dias - R$" << 0 << endl;
        delete e;
    }
}
