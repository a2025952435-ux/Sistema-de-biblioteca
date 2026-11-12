#include <QApplication>
#include <QMessageBox>
#include "Janela.h"
int main(int argc,char** argv){QApplication app(argc,argv);app.setOrganizationName("COLTEC");app.setApplicationName("BibliotecaDesktopDemo12");try{Janela janela;janela.show();return app.exec();}catch(const std::exception& e){QMessageBox::critical(nullptr,"Erro",e.what());return 1;}}
