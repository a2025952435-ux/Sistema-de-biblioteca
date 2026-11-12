#include "../include/Historico.h"
#include <iostream>

Historico::Historico(int cod, std::string tit, std::string ac)
    : codigoItem(cod), tituloItem(tit), acao(ac) {}

void Historico::exibir() const {
    std::cout << "[" << acao << "] Codigo: " << codigoItem << " | Item: " << tituloItem << "\n";
}