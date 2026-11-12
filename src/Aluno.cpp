#include "../include/Aluno.h"

Aluno::Aluno(std::string n) : Usuario(n) {}

int Aluno::getPrazoEmprestimoDias() const {
    return 7; // Alunos têm 7 dias de prazo
}

std::string Aluno::getTipoUsuario() const {
    return "Aluno";
}