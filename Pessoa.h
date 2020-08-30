#ifndef PESSOA_H
#define PESSOA_H
#include <iostream>
#include "Recurso.h"

using namespace std;

class Pessoa : public Recurso {
private:
    static double valorPorHoraPadrao;
    double valorPorHora;
    int horasDiarias;
    bool recebeu;

public:
    Pessoa(string nome, double valorPorHora, int horasDiarias);
    Pessoa(string nome, int horasDiarias);
    virtual ~Pessoa();

    virtual double getValorPorHora();
    virtual int getHorasDiarias();
    virtual bool recebeValorPadrao();

    static void setValorPorHoraPadrao(double valor);
    static double getValorPorHoraPadrao();

    double getCusto(int dias);
    void imprimir();
};

#endif // PESSOA_H
