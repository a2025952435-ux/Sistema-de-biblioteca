#include "Biblioteca.h"
#include <QStandardPaths>
#include <QDir>
static std::string caminho(){auto p=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);QDir().mkpath(p);return (p+"/biblioteca.txt").toStdString();}
static QJsonObject converter(const Registro& r,const QString& c){QJsonObject o;for(auto& kv:r){auto k=QString::fromStdString(kv.first),v=QString::fromStdString(kv.second);if(k=="codigo"||((c=="emprestimos"||c=="reservas")&&(k=="livro"||k=="usuario")))o[k]=v.toInt();else o[k]=v;}return o;}
Biblioteca::Biblioteca():sistema(caminho()){}
QJsonArray Biblioteca::lista(const QString& c)const{QJsonArray a;for(auto& r:sistema.lista(c.toStdString()))a.append(converter(r,c));return a;}
QJsonObject Biblioteca::buscar(const QString& c,int id)const{return converter(sistema.buscar(c.toStdString(),id),c);}
QString Biblioteca::nome(const QString& c,int id)const{return QString::fromStdString(sistema.nome(c.toStdString(),id));}
bool Biblioteca::ocupado(int id)const{return sistema.ocupado(id);}
QString Biblioteca::gravar(const QString& c,QJsonObject o,bool e){Registro r;for(auto i=o.begin();i!=o.end();++i)r[i.key().toStdString()]=i.value().toVariant().toString().toStdString();return QString::fromStdString(sistema.gravar(c.toStdString(),r,e));}
QString Biblioteca::excluir(const QString& c,int id){return QString::fromStdString(sistema.excluir(c.toStdString(),id));}
QString Biblioteca::emprestar(int l,int u,QDate d){return QString::fromStdString(sistema.emprestar(l,u,d.toString(Qt::ISODate).toStdString()));}
QString Biblioteca::devolver(int id,QDate d){return QString::fromStdString(sistema.devolver(id,d.toString(Qt::ISODate).toStdString()));}
QString Biblioteca::reservar(int l,int u){return QString::fromStdString(sistema.reservar(l,u));}
QString Biblioteca::cancelarReserva(int id){return QString::fromStdString(sistema.cancelarReserva(id));}
QString Biblioteca::lembrar(int id){return QString::fromStdString(sistema.lembrar(id));}
