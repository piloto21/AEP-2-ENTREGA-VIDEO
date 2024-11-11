#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string criptografar(string senha) {
    for (size_t i = 0; i < senha.size(); i++) {
        senha[i] += 3; 
    }
    return senha;
}

string descriptografar(string senha) {
    for (size_t i = 0; i < senha.size(); i++) {
        senha[i] -= 3;
    }
    return senha;
}

void adicionarUsuario() {
    string nome, senha;
    cout << "Digite o nome do usuario: ";
    cin >> nome;
    cout << "Digite a senha: ";
    cin >> senha;

    senha = criptografar(senha);

    ofstream arquivo("usuarios.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << nome << " " << senha << endl;
        arquivo.close();
        cout << "Usuario adicionado com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

void listarUsuarios() {
    string nome, senha;
    ifstream arquivo("usuarios.txt");
    if (arquivo.is_open()) {
        cout << "Lista de usuarios:" << endl;
        while (arquivo >> nome >> senha) {
            cout << "Nome: " << nome << ", Senha criptografada: " << senha << endl;
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

void alterarUsuario() {
    string nome, novaSenha;
    cout << "Digite o nome do usuario para alterar a senha: ";
    cin >> nome;
    cout << "Digite a nova senha: ";
    cin >> novaSenha;

    novaSenha = criptografar(novaSenha);

    ifstream arquivo("usuarios.txt");
    ofstream temp("temp.txt");

    bool usuarioEncontrado = false;

    if (arquivo.is_open() && temp.is_open()) {
        string usuario, senha;
        while (arquivo >> usuario >> senha) {
            if (usuario == nome) {
                temp << usuario << " " << novaSenha << endl;
                usuarioEncontrado = true;
            } else {
                temp << usuario << " " << senha << endl;
            }
        }
        arquivo.close();
        temp.close();

        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");

        if (usuarioEncontrado) {
            cout << "Senha do usuario alterada com sucesso!" << endl;
        } else {
            cout << "Usuario nao encontrado." << endl;
        }
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

void deletarUsuario() {
    string nome;
    cout << "Digite o nome do usuario a ser deletado: ";
    cin >> nome;

    ifstream arquivo("usuarios.txt");
    ofstream temp("temp.txt");

    bool usuarioEncontrado = false;

    if (arquivo.is_open() && temp.is_open()) {
        string usuario, senha;
        while (arquivo >> usuario >> senha) {
            if (usuario == nome) {
                usuarioEncontrado = true;
            } else {
                temp << usuario << " " << senha << endl;
            }
        }
        arquivo.close();
        temp.close();

        remove("usuarios.txt");
        rename("temp.txt", "usuarios.txt");

        if (usuarioEncontrado) {
            cout << "Usuario deletado com sucesso!" << endl;
        } else {
            cout << "Usuario nao encontrado." << endl;
        }
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

void menu() {
    int opcao;
    do {
        cout << "\nSistema de Gerenciamento de Usuarios\n";
        cout << "1. Adicionar usuario\n";
        cout << "2. Listar usuarios\n";
        cout << "3. Alterar usuario\n";
        cout << "4. Deletar usuario\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarUsuario();
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                alterarUsuario();
                break;
            case 4:
                deletarUsuario();
                break;
            case 5:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 5);
}

int main() {
    menu();
    return 0;
}

