#ifndef ALUNO_H
#define ALUNO_H

#include "Usuario.h"

// Herança 2: Aluno herda de Usuario
class Aluno : public Usuario {
public:
    Aluno(std::string n);
    int getPrazoEmprestimoDias() const override;
    std::string getTipoUsuario() const override;
};

#endif