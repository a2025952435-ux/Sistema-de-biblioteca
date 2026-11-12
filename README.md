# Sistema de Biblioteca  

Sistema de gerenciamento de biblioteca desenvolvido como projeto acadêmico da disciplina de Programação Orientada a Objetos (POO).

O projeto foi desenvolvido em **C++**, utilizando conceitos de orientação a objetos e uma interface gráfica construída com **Qt Widgets**.

## Objetivo

Desenvolver um sistema que facilite o gerenciamento de livros, usuários, empréstimos e devoluções de uma biblioteca, aplicando os conceitos estudados durante a disciplina.

## Funcionalidades

- Cadastro e consulta de livros.
- Cadastro de usuários.
- Pesquisa de livros.
- Controle de disponibilidade do acervo.
- Realização de empréstimos e devoluções.
- Controle de prazos de empréstimo.
- Histórico de movimentações.
- Reservas de livros.
- Identificação de empréstimos atrasados.
- Simulação de lembretes.

## Conceitos de POO utilizados

**Encapsulamento:** organização dos atributos e métodos das classes, com controle de acesso aos dados.

**Herança:** utilização de classes derivadas para representar diferentes tipos de usuários, como `Aluno` e `Professor`.

**Polimorfismo:** utilização de métodos virtuais para definir comportamentos específicos conforme o tipo de usuário, incluindo o prazo de empréstimo.

**Abstração:** separação das responsabilidades entre as classes do sistema.

## Tecnologias utilizadas

- C++17
- Qt 6 Widgets
- CMake
- Ninja
- Git e GitHub
- Visual Studio Code

## Organização do projeto

```text
BibliotecaDesktop/
├── include/          # Arquivos de cabeçalho (.h)
├── src/              # Implementações (.cpp)
├── original/         # Referência do projeto anterior
├── CMakeLists.txt    # Configuração de compilação
└── LEIA-ME.txt       # Instruções adicionais
```

## Como executar

### Versão de terminal

Com um compilador C++ compatível com C++17, execute na pasta principal do projeto:

```bash
g++ -std=c++17 -Iinclude src/terminal.cpp src/Sistema.cpp src/Usuario.cpp src/Aluno.cpp src/Professor.cpp -o BibliotecaTerminal.exe
```

No Windows:

```powershell
.\BibliotecaTerminal.exe
```

### Versão gráfica

Para compilar a interface gráfica, é necessário ter Qt 6, CMake, Ninja e um compilador C++ configurados.

No ambiente MSYS2 UCRT64 utilizado no desenvolvimento:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
cmake --build build
.\build\Biblioteca.exe
```

## Versão de demonstração

O projeto está na versão **DEMO 1.2**, desenvolvida para apresentar a estrutura do sistema, a aplicação dos conceitos de POO e as funcionalidades principais.

A versão de demonstração contém livros e usuários fictícios para facilitar os testes.

## Observações

O envio de lembretes é simulado e não realiza o envio de e-mails reais.

O projeto está em desenvolvimento e poderá receber melhorias nas funcionalidades e na interface gráfica.
