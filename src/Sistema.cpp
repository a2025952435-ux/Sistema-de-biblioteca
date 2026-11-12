#include "Sistema.h"
#include "Aluno.h"
#include "Professor.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <algorithm>
using namespace std;
static string valor(const Registro& r,const string& k){auto i=r.find(k);return i==r.end()?"":i->second;}
static int numero(const Registro& r,const string& k){try{return stoi(valor(r,k));}catch(...){return 0;}}
string Sistema::somarDias(string d,int dias){tm t{};istringstream s(d);s>>get_time(&t,"%Y-%m-%d");if(s.fail()||d.size()!=10)return "";t.tm_hour=12;t.tm_isdst=-1;auto original=t;if(mktime(&t)==-1||t.tm_mday!=original.tm_mday||t.tm_mon!=original.tm_mon)return "";t.tm_mday+=dias;if(mktime(&t)==-1)return "";ostringstream o;o<<put_time(&t,"%Y-%m-%d");return o.str();}
string Sistema::hoje(int dias){auto n=time(nullptr);auto t=*localtime(&n);ostringstream o;o<<put_time(&t,"%Y-%m-%d");return somarDias(o.str(),dias);}
Sistema::Sistema(string caminho):arquivo(move(caminho)){
 ifstream f(arquivo);if(f){string c;size_t n;while(f>>quoted(c)>>n){if(n>100)throw runtime_error("Dados invalidos");Registro r;for(size_t i=0;i<n;i++){string k,v;if(!(f>>quoted(k)>>quoted(v)))throw runtime_error("Dados invalidos");r[k]=v;}dados[c].push_back(r);}if(!f.eof())throw runtime_error("Dados invalidos");return;}
 const string tit[]={"Dom Casmurro","O Hobbit","Capitães da Areia","O Pequeno Príncipe","1984"}, aut[]={"Machado de Assis","J. R. R. Tolkien","Jorge Amado","Antoine de Saint-Exupéry","George Orwell"}, nomes[]={"Ana Costa","Bruno Lima","Carla Mendes","Diego Souza","Elisa Rocha"};
 for(int i=0;i<5;i++){gravar("livros",{{"codigo",to_string(101+i)},{"titulo",tit[i]},{"autor",aut[i]}});gravar("usuarios",{{"codigo",to_string(201+i)},{"nome",nomes[i]},{"email","teste"+to_string(i+1)+"@example.com"},{"tipo",i%2?"Professor":"Aluno"}});}emprestar(101,201,hoje(-10));emprestar(102,202,hoje(-2));emprestar(103,203,hoje());
}
void Sistema::salvar()const{ofstream f(arquivo);if(!f)throw runtime_error("Falha ao salvar");for(auto& p:dados)for(auto& r:p.second){f<<quoted(p.first)<<' '<<r.size();for(auto& kv:r)f<<' '<<quoted(kv.first)<<' '<<quoted(kv.second);f<<'\n';}if(!f)throw runtime_error("Falha ao salvar");}
Registros Sistema::lista(const string& c)const{auto i=dados.find(c);return i==dados.end()?Registros{}:i->second;}
Registro Sistema::buscar(const string& c,int id)const{for(auto& r:lista(c))if(numero(r,"codigo")==id)return r;return {};}
string Sistema::nome(const string& c,int id)const{return valor(buscar(c,id),c=="livros"?"titulo":"nome");}
bool Sistema::ocupado(int id)const{for(auto& r:lista("emprestimos"))if(numero(r,"livro")==id&&valor(r,"situacao")=="Ativo")return true;return false;}
int Sistema::proximo(const string& c)const{int n=0;for(auto& r:lista(c))n=max(n,numero(r,"codigo"));return n+1;}
string Sistema::gravar(const string& c,Registro r,bool editar){int id=numero(r,"codigo");if(id<=0)return "Código inválido.";if(c!="livros"&&c!="usuarios")return "Cadastro inválido.";if(c=="livros"&&(valor(r,"titulo").empty()||valor(r,"autor").empty()))return "Título e autor obrigatórios.";if(c=="usuarios"&&(valor(r,"nome").empty()||valor(r,"email").find('@')==string::npos||(valor(r,"tipo")!="Aluno"&&valor(r,"tipo")!="Professor")))return "Dados do usuário inválidos.";for(auto& x:dados[c])if(numero(x,"codigo")==id){if(!editar)return "Código já cadastrado.";x=r;salvar();return "";}if(editar)return "Registro não encontrado.";dados[c].push_back(r);salvar();return "";}
string Sistema::excluir(const string& c,int id){if(c!="livros"&&c!="usuarios")return "Cadastro inválido.";for(auto k:{"emprestimos","reservas"})for(auto& r:lista(k))if(numero(r,c=="livros"?"livro":"usuario")==id)return "Registro vinculado a movimentações.";auto& a=dados[c];for(auto i=a.begin();i!=a.end();++i)if(numero(*i,"codigo")==id){a.erase(i);salvar();return "";}return "Registro não encontrado.";}
void Sistema::registrar(const string& acao,int l,int u,const string& d){dados["historico"].push_back({{"codigo",to_string(proximo("historico"))},{"acao",acao},{"livro",nome("livros",l)},{"usuario",nome("usuarios",u)},{"data",d}});salvar();}
string Sistema::emprestar(int l,int u,string d){auto p=buscar("usuarios",u);if(buscar("livros",l).empty()||p.empty()||somarDias(d,0).empty())return "Livro, usuário ou data inválidos.";if(ocupado(l))return "Livro indisponível.";auto& a=dados["reservas"];for(auto i=a.begin();i!=a.end();++i)if(numero(*i,"livro")==l){if(numero(*i,"usuario")!=u)return "Livro reservado para outro usuário.";a.erase(i);break;}
 // Polimorfismo: ponteiro da classe-base chama o método sobrescrito.
 unique_ptr<Usuario> leitor;if(valor(p,"tipo")=="Professor")leitor=make_unique<Professor>(valor(p,"nome"));else leitor=make_unique<Aluno>(valor(p,"nome"));
 dados["emprestimos"].push_back({{"codigo",to_string(proximo("emprestimos"))},{"livro",to_string(l)},{"usuario",to_string(u)},{"data",d},{"prazo",somarDias(d,leitor->getPrazoEmprestimoDias())},{"situacao","Ativo"}});registrar("Empréstimo",l,u,d);return "";}
string Sistema::devolver(int id,string d){for(auto& r:dados["emprestimos"])if(numero(r,"codigo")==id&&valor(r,"situacao")=="Ativo"){if(somarDias(d,0).empty()||d<valor(r,"data"))return "Data inválida.";r["situacao"]="Devolvido";r["devolucao"]=d;registrar("Devolução",numero(r,"livro"),numero(r,"usuario"),d);return "";}return "Empréstimo ativo não encontrado.";}
string Sistema::reservar(int l,int u){if(buscar("livros",l).empty()||buscar("usuarios",u).empty())return "Registro inválido.";for(auto& r:lista("reservas"))if(numero(r,"livro")==l&&numero(r,"usuario")==u)return "Reserva já existe.";dados["reservas"].push_back({{"codigo",to_string(proximo("reservas"))},{"livro",to_string(l)},{"usuario",to_string(u)},{"data",hoje()}});registrar("Reserva",l,u,hoje());return "";}
string Sistema::cancelarReserva(int id){auto& a=dados["reservas"];for(auto i=a.begin();i!=a.end();++i)if(numero(*i,"codigo")==id){int l=numero(*i,"livro"),u=numero(*i,"usuario");a.erase(i);registrar("Cancelamento",l,u,hoje());return "";}return "Reserva não encontrada.";}
string Sistema::lembrar(int id){auto r=buscar("emprestimos",id);if(valor(r,"situacao")!="Ativo")return "Empréstimo ativo não encontrado.";registrar("Lembrete simulado",numero(r,"livro"),numero(r,"usuario"),hoje());return "";}
