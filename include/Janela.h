#pragma once
#include <QMainWindow>
#include <functional>
#include "Biblioteca.h"
class QStackedWidget; class QTableWidget; class QLineEdit; class QVBoxLayout; class QComboBox;
class Janela: public QMainWindow {
 Biblioteca biblioteca;
 QStackedWidget* paginas;
 void atualizar();
 void abrir(int pagina);
 void cadastro(QString chave,int id=0);
 void movimento(bool reserva);
 void tabela(QVBoxLayout* layout,QString chave,QStringList campos,QStringList titulos,int modo=0);
 void executar(const std::function<QString()>& acao);
public: Janela();
};
