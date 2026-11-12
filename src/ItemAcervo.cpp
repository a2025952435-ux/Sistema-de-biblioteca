#include "../include/ItemAcervo.h"
#include <iostream>

ItemAcervo::ItemAcervo(int cod, std::string tit) 
    : codigo(cod), titulo(tit), emprestado(false), nomeLeitorAtual(""), emailLeitorAtual(""), dataDevolucao(0) {}

ItemAcervo::~ItemAcervo() {
    while (!filaEspera.empty()) {
        delete filaEspera.front();
        filaEspera.pop();
    }
}

int ItemAcervo::getCodigo() const { return codigo; }
std::string ItemAcervo::getTitulo() const { return titulo; }
bool ItemAcervo::isEmprestado() const { return emprestado; }
std::string ItemAcervo::getNomeLeitorAtual() const { return nomeLeitorAtual; }
std::string ItemAcervo::getEmailLeitorAtual() const { return emailLeitorAtual; }
std::time_t ItemAcervo::getDataDevolucao() const { return dataDevolucao; }

void ItemAcervo::adicionarNaFila(Usuario* usuario) {
    filaEspera.push(usuario);
    std::cout << "⏳ " << usuario->getNome() << " foi adicionado(a) a fila de espera do item '" << titulo << "'.\n";
}

Usuario* ItemAcervo::retirarDaFila() {
    if (filaEspera.empty()) return nullptr;
    Usuario* proximo = filaEspera.front();
    filaEspera.pop();
    return proximo;
}

bool ItemAcervo::temFilaEspera() const { return !filaEspera.empty(); }

void ItemAcervo::mostrarFila() const {
    if (filaEspera.empty()) {
        std::cout << "Ninguem aguardando na fila.\n";
        return;
    }
    std::queue<Usuario*> temp = filaEspera;
    while (!temp.empty()) {
        std::cout << "[" << temp.front()->getNome() << " (" << temp.front()->getTipoUsuario() << ")] -> ";
        temp.pop();
    }
    std::cout << "(FIM DA FILA)\n";
}

bool ItemAcervo::emprestar(Usuario* leitor, const std::string& email) {
    if (emprestado) return false;
    
    emprestado = true;
    nomeLeitorAtual = leitor->getNome();
    emailLeitorAtual = email;

    std::time_t agora = std::time(nullptr);
    int segundosPrazo = leitor->getPrazoEmprestimoDias() * 24 * 60 * 60;
    dataDevolucao = agora + segundosPrazo;

    return true;
}

bool ItemAcervo::devolver() {
    if (!emprestado) return false;
    
    if (temFilaEspera()) {
        Usuario* proximo = retirarDaFila();
        nomeLeitorAtual = proximo->getNome();
        emailLeitorAtual = ""; // Fica vazio pois o utilizador da fila não forneceu e-mail ao entrar
        
        // CORREÇÃO: Calcular o novo prazo de devolução para a pessoa que estava na fila!
        std::time_t agora = std::time(nullptr);
        int segundosPrazo = proximo->getPrazoEmprestimoDias() * 24 * 60 * 60;
        dataDevolucao = agora + segundosPrazo;

        std::cout << "🔄 Item repassado para o proximo da fila: " << nomeLeitorAtual 
                  << " (" << proximo->getTipoUsuario() << "). Novo prazo: " << getDataDevolucaoFormatada() << "\n";
        
        delete proximo; // Agora podemos limpar a memória com segurança
    } else {
        emprestado = false;
        nomeLeitorAtual = "";
        emailLeitorAtual = "";
        dataDevolucao = 0;
    }
    return true;
}

int ItemAcervo::calcularDiasRestantes() const {
    if (!emprestado) return 0;
    std::time_t agora = std::time(nullptr);
    double segundos = std::difftime(dataDevolucao, agora);
    return static_cast<int>(segundos / (60 * 60 * 24));
}

std::string ItemAcervo::getDataDevolucaoFormatada() const {
    if (!emprestado) return "N/A";
    char buffer[80];
    struct std::tm* timeinfo = std::localtime(&dataDevolucao);
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return std::string(buffer);
}