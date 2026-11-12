#include "../include/EmailService.h"
#include <iostream>

EmailService::EmailService(std::string server, std::string email, std::string senha)
    : smtpServer(server), remetenteEmail(email), senhaApp(senha) {}

bool EmailService::enviarEmail(const std::string& destinatario, const std::string& assunto, const std::string& mensagem) {
    if (destinatario.empty()) {
        std::cout << "[AVISO] E-mail de destino nao informado. Notificacao ignorada.\n";
        return false;
    }

    // Simulacao do envio de e-mail para nao travar o sistema nem exigir libcurl
    std::cout << "--------------------------------------------------\n";
    std::cout << "[SIMULACAO DE E-MAIL]\n";
    std::cout << "Para: " << destinatario << "\n";
    std::cout << "Assunto: " << assunto << "\n";
    std::cout << "Mensagem: " << mensagem << "\n";
    std::cout << "--------------------------------------------------\n";
    
    return true;
}