#include "Ferramenta.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Ferramenta::Ferramenta(string nome, double custoDiario) : Recurso(nome) {
    if (custoDiario < 0)
        throw new invalid_argument ("Custo Diario negativo");
    this->custoDiario = custoDiario;
}

Ferramenta::~Ferramenta() {

}

double Ferramenta::getCustoDiario() {
    return custoDiario;
}

double Ferramenta::getCusto(int dias) {
    if (dias <= 0)
        throw new invalid_argument ("Quantidade de dias invalida");
    return dias*custoDiario;
}

void Ferramenta::imprimir() {
    cout << "Ferramenta: " << getNome() << " - R$" << custoDiario
    << " por dia" << endl;
}
