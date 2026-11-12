#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Usuario.h"

// Herança 2 (Segundo Tipo): Professor herda de Usuario
class Professor : public Usuario {
public:
    Professor(std::string n);
    int getPrazoEmprestimoDias() const override;
    std::string getTipoUsuario() const override;
};

#endif