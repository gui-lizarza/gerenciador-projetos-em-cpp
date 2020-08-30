#ifndef ERRODEARQUIVO_H
#define ERRODEARQUIVO_H
#include <stdexcept>
#include <string>

using namespace std;

class ErroDeArquivo : public logic_error {
public:
    ErroDeArquivo(string mensagem);
};

#endif // ERRODEARQUIVO_H
