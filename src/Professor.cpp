#include "../include/Professor.h"

Professor::Professor(std::string n) : Usuario(n) {}

int Professor::getPrazoEmprestimoDias() const {
    return 14; // Professores têm prazo estendido de 14 dias
}

std::string Professor::getTipoUsuario() const {
    return "Professor";
}