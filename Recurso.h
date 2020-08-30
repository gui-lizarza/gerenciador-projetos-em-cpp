#ifndef RECURSO_H
#define RECURSO_H
#include <iostream>

using namespace std;

class Recurso {
private:
    string nome;

public:
    Recurso(string nome);
    virtual ~Recurso();

    virtual string getNome();
    virtual double getCusto(int dias) = 0;
    virtual void imprimir() = 0;
};

#endif // RECURSO_H
