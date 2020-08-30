#include "Atividade.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Atividade::Atividade(string nome) {
    quantidadeDeRecursos = 0;
    terminou = false;

    this->nome = nome;
}

Atividade::~Atividade() {

}

string Atividade::getNome() {
    return nome;
}

void Atividade::adicionar(Recurso* r) {
    if (quantidadeDeRecursos >= MAX_RECURSOS)
        throw new overflow_error ("Nao foi possivel adicionar recurso");

    for (int i = 0; i < quantidadeDeRecursos; i++)
        if (recursos[i] == r)
            throw new invalid_argument ("Nao foi possivel adicionar recurso");

    recursos[quantidadeDeRecursos] = r;
    quantidadeDeRecursos++;
}

Recurso** Atividade::getRecursos() {
    return recursos;
}

int Atividade::getQuantidadeDeRecursos() {
    return quantidadeDeRecursos;
}

void Atividade::terminar(int duracaoReal) {
    if (duracaoReal <= 0)
        throw new invalid_argument ("Duracao nao positiva");

    terminou = true;

    this->duracaoReal = duracaoReal;
}

bool Atividade::estaTerminada() {
    return terminou;
}
