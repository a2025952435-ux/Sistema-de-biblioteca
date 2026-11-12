#ifndef LIVRO_H
#define LIVRO_H

#include "ItemAcervo.h"

// Herança 1: Livro herda de ItemAcervo
class Livro : public ItemAcervo {
private:
    std::string autor;

public:
    Livro(int cod, std::string tit, std::string aut);

    std::string getAutor() const;
    void setAutor(const std::string& aut);

    // Sobrescrita Polimórfica
    void exibirDetalhes() const override;
    std::string getTipo() const override;
};

#endif