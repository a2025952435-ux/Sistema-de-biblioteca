#ifndef ITEMACERVO_H
#define ITEMACERVO_H

#include <string>
#include <queue>
#include <ctime>
#include "Usuario.h"

class ItemAcervo {
private:
    int codigo;
    std::string titulo;
    bool emprestado;
    std::string nomeLeitorAtual;
    std::string emailLeitorAtual;
    std::time_t dataDevolucao;
    std::queue<Usuario*> filaEspera;

public:
    ItemAcervo(int cod, std::string tit);
    virtual ~ItemAcervo();

    int getCodigo() const;
    std::string getTitulo() const;
    bool isEmprestado() const;
    std::string getNomeLeitorAtual() const;
    std::string getEmailLeitorAtual() const;
    std::time_t getDataDevolucao() const;

    // Métodos setCodigo e setTitulo foram removidos por serem anti-padrão (IDs não devem mudar)

    void adicionarNaFila(Usuario* usuario);
    Usuario* retirarDaFila();
    bool temFilaEspera() const;
    void mostrarFila() const;

    virtual bool emprestar(Usuario* leitor, const std::string& email);
    virtual bool devolver();

    int calcularDiasRestantes() const;
    std::string getDataDevolucaoFormatada() const;

    virtual void exibirDetalhes() const = 0;
    virtual std::string getTipo() const = 0;
};

#endif