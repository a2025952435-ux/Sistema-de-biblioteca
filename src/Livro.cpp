#include "../include/Livro.h"
#include <iostream>

Livro::Livro(int cod, std::string tit, std::string aut)
    : ItemAcervo(cod, tit), autor(aut) {}

std::string Livro::getAutor() const { return autor; }

void Livro::setAutor(const std::string& aut) {
    if (!aut.empty()) autor = aut;
}

void Livro::exibirDetalhes() const {
    std::cout << "ID/Codigo : " << getCodigo() << "\n";
    std::cout << "Tipo      : " << getTipo() << "\n";
    std::cout << "Titulo    : " << getTitulo() << "\n";
    std::cout << "Autor     : " << autor << "\n";
    if (isEmprestado()) {
        std::cout << "Status    : [EMPRESTADO] para " << getNomeLeitorAtual() << "\n";
        std::cout << "Espera    : ";
        mostrarFila();
    } else {
        std::cout << "Status    : [DISPONIVEL] na estante\n";
    }
}

std::string Livro::getTipo() const {
    return "Livro";
}