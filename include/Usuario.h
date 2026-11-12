#ifndef USUARIO_H
#define USUARIO_H

#include <string>

// Classe Base para Usuários
class Usuario {
private:
    std::string nome;

public:
    Usuario(std::string n);
    virtual ~Usuario() = default;

    std::string getNome() const;
    void setNome(const std::string& n);

    // Método Virtual para Polimorfismo
    virtual int getPrazoEmprestimoDias() const = 0;
    virtual std::string getTipoUsuario() const = 0;
};

#endif