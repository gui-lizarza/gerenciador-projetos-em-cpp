#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <vector>
#include "Recurso.h"
#include "Pessoa.h"
#include "Ferramenta.h"
#include "Atividade.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "Projeto.h"
#include "PersistenciaDeProjeto.h"
#include "ErroDeArquivo.h"

using namespace std;

void comando(int *n) {
    cout << endl; //Pular linha para facilitar a leitura dom usuário
    cout << "1 - Adicionar recurso" << endl
         << "2 - Adicionar atividade" << endl
         << "3 - Terminar atividade" << endl
         << "4 - Imprimir projeto" << endl
         << "5 - Definir valor por hora padrao" << endl
         << "6 - Salvar" << endl
         << "0 - Sair" << endl
         << "Escolha a opcao: ";
    cin >> *n;
    cout << endl;
}

void imprimirPessoas(Projeto* pr) {
    cout << endl;
    list<Recurso*>* r = pr->getRecursos();
    list<Recurso*>::iterator i  = r->begin();
    int cont = 1;
    while (i != r->end()) { //Teste já adicionado
        cout << cont << " - ";
        (*i)->imprimir();
        i++;
        cont++;
    }
}

void imprimirAtividades(Projeto* pr) {
    vector<Atividade*>* atividades = pr->getAtividades();
    for(unsigned int i = 0; i < atividades->size(); i++)
        cout << i+1 << " - " << atividades->at(i)->getNome() << endl;
}

void adRecurso(Projeto* pr) {
    cout << "Ferramenta (f) ou Pessoa (p): ";
    char rec;
    cin >> rec;
    if (rec == 'f') {
        cout << "Nome: ";
        string nomeF;
        cin >> nomeF;
        cout << "Custo diario: ";
        double custo;
        cin >> custo;
        Ferramenta* f = new Ferramenta(nomeF, custo);
        pr->adicionar(f);
    }
    else if (rec == 'p') {
        cout << "Nome: ";
        string nomeP;
        cin >> nomeP;
        cout << "Horas diarias: ";
        int horas;
        cin >> horas;
        cout << "Valor por hora padrao (s/n)? ";
        char opc;
        cin >> opc;
        if (opc == 's') {
            Pessoa* p = new Pessoa(nomeP, horas);
            pr->adicionar(p);
        }
        else if (opc == 'n') {
            cout << "Valor por hora (em R$): ";
            double valor;
            cin >> valor;
            Pessoa* p = new Pessoa(nomeP, valor, horas);
            pr->adicionar(p);
        }
    }
}

void atividadeAdRecurso (Projeto* pr, Atividade* a) {
    cout << "Deseja adicionar um recurso (s/n)? ";
    char ch;
    cin >> ch;
    while (ch == 's') {
        imprimirPessoas(pr);
        cout << "Escolha um recurso ou 0 para cancelar: ";
        int n;
        cin >> n;
        if (n != 0) {
            list<Recurso*>* r = pr->getRecursos();
            list<Recurso*>::iterator i  = r->begin();
            int cont = 1;
            bool achou = false;
            while (i != r->end() && achou == false) {
                if(cont == n) {
                    achou = true;
                    try {
                        a->adicionar((*i));
                    }
                    catch (invalid_argument *e) {
                        cout << e->what() << endl;
                        delete e;
                    }
                    catch (overflow_error *e) {
                        cout << e->what() << endl;
                        delete e;
                    }
                }
                i++;
                cont++;
            }
        }
        cout << "Deseja adicionar um recurso (s/n)? ";
        cin >> ch;
    }
}

void adAtividade(Projeto* pr) {
    cout << "Nome: ";
    string nomeA;
    cin >> nomeA;
    //Tipo de atividade
    cout << "Prazo fixo (p) ou trabalho fixo (t)? ";
    char opc;
    cin >> opc;
    if (opc == 'p') {
        cout << "Dias necessarios: ";
        int dias;
        cin >> dias;
        AtividadeDePrazoFixo* a = new AtividadeDePrazoFixo(nomeA, dias);
        atividadeAdRecurso(pr, a);
        pr->adicionar(a);
    }
    else if (opc == 't') {
        cout << "Horas necessarias: ";
        int horas;
        cin >> horas;
        AtividadeDeEsforcoFixo* a = new AtividadeDeEsforcoFixo(nomeA, horas);
        atividadeAdRecurso(pr, a);
        pr->adicionar(a);
    }
}


void terminarAtividade (Projeto* pr) {
    imprimirAtividades(pr);
    cout << "Escolha uma atividade ou 0 para cancelar: ";
    unsigned int opc;
    cin >> opc;
    if (opc != 0) {
        bool achou = false;
        vector<Atividade*>* atividades = pr->getAtividades();
        for(unsigned int i = 0; i < atividades->size() && achou == false; i++) {
            if(i+1 == opc) {
                if (atividades->at(i)->estaTerminada() == false) {
                    cout << "Duracao real: ";
                    int duracao;
                    cin >> duracao;
                    atividades->at(i)->terminar(duracao);
                }
                else cout << "Atividade ja esta terminada" << endl;
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    //Início
    cout << "Deseja carregar um novo projeto (s/n)? ";
    char ch;
    cin >> ch;
    Projeto* proj;
    if(ch == 'n') {
        cout << "Digite o nome do projeto: ";
        string nome;
        cin >> nome;
        proj = new Projeto(nome);
    }
    else {
        cout << "Digite o nome do arquivo: ";
        string arquivo;
        cin >> arquivo;
        try {
            PersistenciaDeProjeto* pDP = new PersistenciaDeProjeto();
            proj = pDP->carregar(arquivo);
        }
        catch (ErroDeArquivo *e) {
            cout << "Erro: " << e->what() << endl;
            delete e;
            return 0;
        }
    }
    //Opções
    int opcao;
    opcao = true;
    while(opcao != 0) {
        comando(&opcao);
        switch (opcao) {
            //Adicionar recurso
            case 1: {
                try {
                    adRecurso(proj);
                }
                catch (invalid_argument *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
            //Adicionar atividade
            case 2: {
                try {
                    adAtividade(proj);
                }
                catch (invalid_argument *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
            //Terminar atividade
            case 3: {
                 try {
                    terminarAtividade(proj);
                }
                catch (invalid_argument *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
            //Imprimir projeto
            case 4: {
                try {
                    proj->imprimir();
                }
                catch (logic_error *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
            //Definir valor por hora padrao
            case 5: {
                cout << "Valor atual: " << Pessoa::getValorPorHoraPadrao() << endl;
                cout << "Novo valor: ";
                double valor;
                cin >> valor;
                try {
                    Pessoa::setValorPorHoraPadrao(valor);
                }
                catch (invalid_argument *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
            //Salvar
            case 6: {
                cout << "Nome do arquivo: ";
                string arquivo;
                cin >> arquivo;
                PersistenciaDeProjeto* pDP = new PersistenciaDeProjeto();
                try {
                    pDP->salvar(proj, arquivo);
                }
                catch (ErroDeArquivo *e) {
                    cout << "Erro: " << e->what() << endl;
                    delete e;
                    return 0;
                }
                break;
            }
        }
    }
    proj->~Projeto();
    return 0;
}
