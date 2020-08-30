#include "Pessoa.h"
#include <iostream>
#include <stdexcept>

using namespace std;

double Pessoa::valorPorHoraPadrao = 10;

Pessoa::Pessoa(string nome, double valorPorHora, int horasDiarias) : Recurso(nome) {
    if (valorPorHora <= 0 || horasDiarias <= 0)
        throw new invalid_argument ("Valores nao positivos");

    recebeu = false;

    this->valorPorHora = valorPorHora;
    this->horasDiarias = horasDiarias;
}

Pessoa::Pessoa(string nome, int horasDiarias) : Recurso(nome) {
    if (horasDiarias <= 0)
        throw new invalid_argument ("Valores nao positivos");

    recebeu = true;

    valorPorHora = Pessoa::valorPorHoraPadrao;
    this->horasDiarias = horasDiarias;
}

Pessoa::~Pessoa() {

}

double Pessoa::getValorPorHora() {
    if(recebeu)
        valorPorHora = Pessoa::valorPorHoraPadrao; //Caso valorPorHora padrão tenha sido atualizado
    return valorPorHora;
}

int Pessoa::getHorasDiarias() {
    return horasDiarias;
}

bool Pessoa::recebeValorPadrao() {
    return recebeu;
}

void Pessoa::setValorPorHoraPadrao(double valor) {
    if (valor <= 0)
        throw new invalid_argument ("Valor nao positivo");

    Pessoa::valorPorHoraPadrao = valor;
}

double Pessoa::getValorPorHoraPadrao() {
    return Pessoa::valorPorHoraPadrao;
}

double Pessoa::getCusto(int dias) {
    if (dias <= 0)
        throw new invalid_argument ("Quantidade de dias invalida");

    return dias*horasDiarias*valorPorHora;
}

void Pessoa::imprimir() {
    cout << "Pessoa: " << getNome() << " - R$" << getValorPorHora() << " - "
    << horasDiarias << "h por dia" << endl;
}
