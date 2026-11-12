#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <string>

class EmailService {
private:
    std::string smtpServer;
    std::string remetenteEmail;
    std::string senhaApp;

public:
    EmailService(std::string server = "smtps://smtp.gmail.com:465", 
                 std::string email = "seu_email@gmail.com", 
                 std::string senha = "sua_senha_de_app");

    bool enviarEmail(const std::string& destinatario, 
                     const std::string& assunto, 
                     const std::string& mensagem);
};

#endif