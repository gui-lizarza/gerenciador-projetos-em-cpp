#ifndef FERRAMENTA_H
#define FERRAMENTA_H
#include <iostream>
#include "Recurso.h"

using namespace std;

class Ferramenta : public Recurso {
private:
    double custoDiario;

public:
    Ferramenta(string nome, double custoDiario);
    virtual ~Ferramenta();

    virtual double getCustoDiario();

    double getCusto(int dias);
    void imprimir();
};

#endif // FERRAMENTA_H
