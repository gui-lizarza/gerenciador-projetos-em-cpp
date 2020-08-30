#include <iostream>
#include <vector>
#include <list>
#include "Atividade.h"


#ifndef PROJETO_H
#define PROJETO_H
#include "Pessoa.h"

class Projeto {
private:
    string nome;
    vector<Atividade*>* atividades;
    list<Recurso*>* recursos;

public:
    Projeto(string nome);
    virtual ~Projeto();
    virtual string getNome();

    virtual void adicionar(Atividade* a);
    virtual vector<Atividade*>* getAtividades();
    virtual void adicionar(Recurso* r);
    virtual list<Recurso*>* getRecursos();

    virtual int getDuracao();
    virtual int getDuracao(bool terminadas);
    virtual double getCusto();
    virtual void imprimir();
};



#endif // PROJETO_H
