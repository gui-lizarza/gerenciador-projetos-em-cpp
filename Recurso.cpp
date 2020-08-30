#include "Recurso.h"
#include <iostream>

using namespace std;

Recurso::Recurso(string nome) {
    this->nome = nome;

}

Recurso::~Recurso() {

}

string Recurso::getNome() {
    return nome;
}
