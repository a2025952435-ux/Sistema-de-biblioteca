#ifndef HISTORICO_H
#define HISTORICO_H

#include <string>

class Historico {
private:
    int codigoItem;
    std::string tituloItem;
    std::string acao; // "EMPRESTADO", "DEVOLVIDO", "REMOVIDO"

public:
    Historico(int cod, std::string tit, std::string ac);

    void exibir() const;
};

#endif