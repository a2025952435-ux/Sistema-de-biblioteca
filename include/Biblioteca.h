#pragma once
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <memory>
#include "Sistema.h"
#include "Livro.h"
#include "Aluno.h"
#include "Professor.h"
class Biblioteca {
    Sistema sistema;
public:
    Biblioteca();
    QJsonArray lista(const QString& chave) const;
    QString gravar(const QString& chave,QJsonObject registro,bool editar=false);
    QString excluir(const QString& chave,int codigo);
    QString emprestar(int livro,int usuario,QDate data);
    QString devolver(int codigo,QDate data);
    QString reservar(int livro,int usuario);
    QString cancelarReserva(int codigo);
    QString lembrar(int codigo);
    QJsonObject buscar(const QString& chave,int codigo) const;
    QString nome(const QString& chave,int codigo) const;
    bool ocupado(int codigo) const;

};
