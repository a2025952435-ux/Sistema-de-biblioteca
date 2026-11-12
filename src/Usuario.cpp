#include "../include/Usuario.h"

Usuario::Usuario(std::string n) : nome(n) {}

std::string Usuario::getNome() const { return nome; }

void Usuario::setNome(const std::string& n) {
    if (!n.empty()) nome = n;
}