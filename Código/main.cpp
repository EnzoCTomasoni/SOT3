#include <iostream>
#include <string>
#include "filesystem.h"

using namespace std;

int main() {
    Directory* root = get_root_directory();
    Directory* current = root;

    string command;

    cout << "Sistema de arquivos iniciado.\n";
    cout << "Comandos: mkdir NOME | touch NOME | cd NOME | cd .. | ls | rm NOME | rmdir NOME | exit\n";

    while (true) {
        cout << "\n>> ";
        cin >> command;

        if (command == "mkdir") {
            string name;
            cin >> name;
            TreeNode* dirNode = create_directory(name.c_str());
            btree_insert(current->tree, dirNode);

        } else if (command == "touch") {
            string name;
            cin >> name;
            cin.ignore(); // limpar buffer para getline
            cout << "Conteúdo do arquivo (máx 1MB): ";
            string content;
            getline(cin, content);
            if (content.size() > 1048576) {
                cout << "Erro: conteúdo maior que 1MB. Arquivo não criado.\n";
            } else {
                TreeNode* fileNode = create_txt_file(name.c_str(), content.c_str());
                btree_insert(current->tree, fileNode);
            }

        } else if (command == "cd") {
            string path;
            cin >> path;

            if (path == "..") {
                // Voltar para o diretório raiz
                current = root;
                cout << "Voltando para o diretório raiz.\n";
            } else {
                change_directory(&current, path.c_str());
            }

        } else if (command == "ls") {
            list_directory_contents(current);

        } else if (command == "rm") {
            string name;
            cin >> name;
            delete_txt_file(current->tree, name.c_str());

        } else if (command == "rmdir") {
            string name;
            cin >> name;
            delete_directory(current->tree, name.c_str());

        } else if (command == "exit") {
            cout << "Saindo do sistema de arquivos.\n";
            break;

        } else {
            cout << "Comando desconhecido.\n";
        }
    }

    return 0;
}
