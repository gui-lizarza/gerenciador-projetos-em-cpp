#include "Projeto.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

#include <vector>
#include <list>
#include "Atividade.h"
#include "Recurso.h"

using namespace std;

Projeto::Projeto(string nome) : nome (nome) {
    atividades = new vector<Atividade*>();
    recursos = new list<Recurso*>();
}

Projeto::~Projeto() {
    atividades->clear(); //Limpa o vetor, deletando todas as atividades
    delete atividades;
    recursos->clear(); //Limpa a lista, deletando todos os recursos
    delete recursos;
}

string Projeto::getNome() {
    return nome;
}

void Projeto::adicionar(Atividade* a) {
    atividades->push_back(a);
}

vector<Atividade*>* Projeto::getAtividades() {
    return atividades;
}

void Projeto::adicionar(Recurso* r) {
    list<Recurso*>::iterator i  = recursos->begin();
    while (i != recursos->end()) { //Teste já adicionado
        if((*i) == r) {
            throw new invalid_argument ("Recurso previamente adicionado");
        }
        i++;
    }
    recursos->push_back(r);
}

list<Recurso*>* Projeto::getRecursos() {
    return recursos;
}

int Projeto::getDuracao() {
    int dias = 0;
    for(unsigned int i = 0; i < atividades->size(); i++) {
        try {
            dias = dias + atividades->at(i)->getDuracao();
        }
        catch (logic_error *e) {
            delete e;
        }
    }
    return dias;
}

int Projeto::getDuracao(bool terminadas) {
    int dias = 0;
    for(unsigned int i = 0; i < atividades->size(); i++) {
        if(terminadas == atividades->at(i)->estaTerminada()) {
            try {
                dias = dias + atividades->at(i)->getDuracao();
            }
            catch (logic_error *e) {
                delete e;
            }
        }
    }
    return dias;
}

double Projeto::getCusto() {
    double custo = 0;
    for(unsigned int i = 0; i < atividades->size(); i++) {
        custo = custo + atividades->at(i)->getCusto();
    }
    return custo;
}

void Projeto::imprimir() {
    cout << getNome() << " - R$" << getCusto() << endl;
    cout << "Duracao:" << endl;
    cout << "- Feito " << getDuracao(true) << " dias" << endl;
    cout << "- Falta " << getDuracao(false) << " dias" << endl;
    cout << "- Total " << getDuracao() << " dias" << endl << "----" << endl;
    for(unsigned int i = 0; i < atividades->size(); i++) {
        atividades->at(i)->imprimir();
    }
}


