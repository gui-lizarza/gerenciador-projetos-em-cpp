#include "PersistenciaDeProjeto.h"
#include "Pessoa.h"
#include "Ferramenta.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include <fstream>
#include <stdexcept>
#include <list>
#include <string>
#include "ErroDeArquivo.h"

using namespace std;

PersistenciaDeProjeto::PersistenciaDeProjeto() {

}

PersistenciaDeProjeto::~PersistenciaDeProjeto() {

}

Projeto* PersistenciaDeProjeto::carregar(string arquivo) {
    ifstream in;
    in.open(arquivo);
    if (in.fail()) {
        throw new ErroDeArquivo ("Erro ao abrir arquivo");
        in.close();
    }
    // Nome do Projeto
    string nome;
    in >> nome;
    if (!in.good())
        throw new ErroDeArquivo ("Erro na leitura");
    Projeto* p = new Projeto(nome);
    //Recursos
    int i; //Contador de recursos
    in >> i;
    if (!in.good())
        throw new ErroDeArquivo ("Erro na leitura");
    //Adicionar recursos
    for(int j = 0; j < i; j++) {
        char ch; //P(pessoa), F(ferramenta)
        in >> ch;
        if (!in.good())
            throw new ErroDeArquivo ("Erro na leitura");
        //Adicionar pessoa
        if(ch == 'P') {
            in >> nome;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            double valor;
            in >> valor;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            int horas;
            in >> horas;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            if (valor == -1) { //Caso pessoa ganhe valor padrão
                Pessoa *x = new Pessoa(nome, horas);
                p->adicionar(x);
            }
            else {
                Pessoa *x = new Pessoa(nome, valor, horas);
                p->adicionar(x);
            }
        }
        //Adicionar ferramenta
        if(ch == 'F') {
            in >> nome;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            double custo;
            in >> custo;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            Ferramenta *x = new Ferramenta(nome, custo);
            p->adicionar(x);
        }
    }
    //Atividades
    in >> i; //Contador de atividades
    if (!in.good())
        throw new ErroDeArquivo ("Erro na leitura");
    for(int l = 0; l < i; l++) { //Adicionar atividades
        char ch; //P(prazo fixo), E(esforço fixo)
        in >> ch;
        if (!in.good())
            throw new ErroDeArquivo ("Erro na leitura");
        //Adicionar atividade de prazo fixo
        if(ch == 'P') {
            in >> nome;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            int dias;
            in >> dias;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            AtividadeDePrazoFixo *a = new AtividadeDePrazoFixo(nome, dias);
            //Término da atividade
            char terminada;
            in >> terminada;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            if(terminada == 'T') {
                int duracaoReal;
                in >> duracaoReal;
                if (!in.good())
                    throw new ErroDeArquivo ("Erro na leitura");
                a->terminar(duracaoReal);
            }
            //Recursos da atividade
            int quantidadeRecursos;
            in >> quantidadeRecursos;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            for (int k = 0; k < quantidadeRecursos; k++) {
                string recurso; //Nome do recurso
                in >> recurso;
                if (!in.good())
                    throw new ErroDeArquivo ("Erro na leitura");
                bool achou = false;
                list<Recurso*>::iterator cont = p->getRecursos()->begin();
                while (cont != p->getRecursos()->end() && achou ==false) {
                    if ((*cont)->getNome() == recurso) {
                        a->adicionar((*cont));
                        achou = true;
                    }
                    cont++;
                }
            }
            p->adicionar(a);
        }
        //Adicionar atividade de esforço fixo
        if(ch == 'E') {
            in >> nome;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            int horas;
            in >> horas;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            AtividadeDeEsforcoFixo *a = new AtividadeDeEsforcoFixo(nome, horas);
            //Término
            char terminada;
            in >> terminada;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            if(terminada == 'T') {
                int duracaoReal;
                in >> duracaoReal;
                if (!in.good())
                    throw new ErroDeArquivo ("Erro na leitura");
                a->terminar(duracaoReal);
            }
            //Recursos da atividade
            int quantidadeRecursos;
            in >> quantidadeRecursos;
            if (!in.good())
                throw new ErroDeArquivo ("Erro na leitura");
            for (int k = 0; k < quantidadeRecursos; k++) {
                string recurso; //Nome do recurso
                in >> recurso;
                if (!in.good())
                    throw new ErroDeArquivo ("Erro na leitura");
                bool achou = false;
                list<Recurso*>::iterator cont = p->getRecursos()->begin();
                while (cont != p->getRecursos()->end() && achou == false) {
                    if ((*cont)->getNome() == recurso) {
                        a->adicionar((*cont));
                        achou = true;
                    }
                    cont++;
                }
            }
            p->adicionar(a);
        }
    }
    in.close();
    return p;
}

void PersistenciaDeProjeto::salvar(Projeto* p, string arquivo) {
    ofstream out;
    out.open(arquivo);
    if(out.fail()) {
        throw new ErroDeArquivo ("Erro ao abrir arquivo");
        out.close();
    }

    out << p->getNome() << endl;
    //Recursos
    out << p->getRecursos()->size() << endl;
    list<Recurso*>::iterator i = p->getRecursos()->begin();
    while(i != p->getRecursos()->end()) {
        Pessoa* pessoa = dynamic_cast<Pessoa*>((*i));
        if (pessoa != NULL) {
            out << "P " << pessoa->getNome() << " ";
            if(pessoa->recebeValorPadrao() == true) {
                out << "-1 ";
            }
            else out << pessoa->getValorPorHora() << " ";
            out << pessoa->getHorasDiarias() << endl;
        }
        else {
            Ferramenta* ferramenta = dynamic_cast<Ferramenta*>((*i));
            out << "F " << ferramenta->getNome() << " " << ferramenta->getCustoDiario() << endl;
        }
        i++;
    }
    //Atividades
    out << p->getAtividades()->size() << endl;
    for(unsigned int i = 0; i < p->getAtividades()->size(); i++) {
        AtividadeDePrazoFixo* prazo = dynamic_cast<AtividadeDePrazoFixo*>(p->getAtividades()->at(i));
        if (prazo != NULL) { //Atividade de prazo fixo
            out << "P " << prazo->getNome() << " " << prazo->getPrazo();
            if (prazo->estaTerminada() == true) {
                out << " T " << p->getAtividades()->at(i)->getDuracao() << endl;
            }
            else out << " N" << endl;
        }
        else { //Atividade de esforço fixo
            AtividadeDeEsforcoFixo* esforco = dynamic_cast<AtividadeDeEsforcoFixo*>(p->getAtividades()->at(i));
            out << "E " << esforco->getNome() << " " << esforco->getHorasNecessarias();
            if (esforco->estaTerminada() == true) {
                out << " T " << esforco->getDuracao() << endl;
            }
            else out << " N" << endl;
        }
        //Recursos de cada atividade
        int quantidade = p->getAtividades()->at(i)->getQuantidadeDeRecursos();
        out << quantidade << endl;
        for(int j = 0; j < p->getAtividades()->at(i)->getQuantidadeDeRecursos(); j++) {
            out << p->getAtividades()->at(i)->getRecursos()[j]->getNome() << " ";
        }
        if (quantidade != 0) out << endl;
    }
    out << endl;
    out.close();
}

