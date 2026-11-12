#pragma once
#include <string>
#include <map>
#include <vector>
using Registro = std::map<std::string,std::string>;
using Registros = std::vector<Registro>;
class Sistema {
    std::map<std::string,Registros> dados;
    std::string arquivo;
    void salvar() const;
    int proximo(const std::string& chave) const;
    void registrar(const std::string& acao,int l,int u,const std::string& d);
public:
    explicit Sistema(std::string caminho);
    Registros lista(const std::string& c) const;
    Registro buscar(const std::string& c,int id) const;
    std::string nome(const std::string& c,int id) const;
    bool ocupado(int id) const;
    std::string gravar(const std::string& c,Registro r,bool editar=false);
    std::string excluir(const std::string& c,int id);
    std::string emprestar(int l,int u,std::string d);
    std::string devolver(int id,std::string d);
    std::string reservar(int l,int u);
    std::string cancelarReserva(int id);
    std::string lembrar(int id);
    static std::string hoje(int dias=0);
    static std::string somarDias(std::string d,int dias);
};
