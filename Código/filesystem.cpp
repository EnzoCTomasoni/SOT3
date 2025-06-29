#include "filesystem.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring> // for strdup, strcmp
#include <cstdlib> // for malloc/free

using namespace std;

struct BTree {
    vector<TreeNode*> keys;
    int t;
};

BTree* btree_create(int t) {
    BTree* tree = new BTree();
    tree->t = t;
    return tree;
}

TreeNode* create_txt_file(const char* name, const char* content) {
    File* file = new File();
    file->name = strdup(name);
    file->content = strdup(content);
    file->size = strlen(content);

    TreeNode* node = new TreeNode();
    node->name = strdup(name);
    node->type = FILE_TYPE;
    node->data.file = file;
    
    cout << "Arquivo criado" << endl;
    return node;
}

TreeNode* create_directory(const char* name) {
    Directory* dir = new Directory();
    dir->tree = btree_create(2);

    TreeNode* node = new TreeNode();
    node->name = strdup(name);
    node->type = DIRECTORY_TYPE;
    node->data.directory = dir;
    
    cout << "Diretório criado" << endl;
    return node;
}

TreeNode* btree_search(BTree* tree, const char* name) {
    if (!tree) return nullptr;
    for (auto node : tree->keys) {
        if (strcmp(node->name, name) == 0) {
            return node;
        }
    }
    return nullptr;
}

void btree_insert(BTree* tree, TreeNode* node) {
    if (!tree || !node) return;

    for (auto existing : tree->keys) {
        if (strcmp(existing->name, node->name) == 0) {
            cout << "Erro: já existe um " << (existing->type == DIRECTORY_TYPE ? "diretório" : "arquivo")
                 << " com nome '" << node->name << "' neste diretório." << endl;
            // Libera memória
            if (node->type == FILE_TYPE) {
                free(node->data.file->name);
                free(node->data.file->content);
                delete node->data.file;
            } else {
                // liberar árvore simplificado
                delete node->data.directory->tree;
                delete node->data.directory;
            }
            free(node->name);
            delete node;
            return;
        }
    }

    tree->keys.push_back(node);
}

void btree_delete(BTree* tree, const char* name) {
    if (!tree) return;

    for (auto it = tree->keys.begin(); it != tree->keys.end(); ++it) {
        if (strcmp((*it)->name, name) == 0) {
            TreeNode* node = *it;
            tree->keys.erase(it);

            if (node->type == FILE_TYPE) {
                free(node->data.file->name);
                free(node->data.file->content);
                delete node->data.file;
            } else {
                // Libera árvore simples
                for (auto subnode : node->data.directory->tree->keys) {
                    btree_delete(node->data.directory->tree, subnode->name);
                }
                delete node->data.directory->tree;
                delete node->data.directory;
            }

            free(node->name);
            delete node;
            return;
        }
    }
    cout << "Item '" << name << "' não encontrado para remoção." << endl;
}

void btree_traverse(BTree* tree) {
    if (!tree) return;
    for (auto node : tree->keys) {
        cout << node->name << " [" << (node->type == DIRECTORY_TYPE ? "DIR" : "FILE") << "]" << endl;
    }
}

void delete_txt_file(BTree* tree, const char* name) {
    TreeNode* node = btree_search(tree, name);
    if (node && node->type == FILE_TYPE) {
        btree_delete(tree, name);
        cout << "Arquivo '" << name << "' deletado." << endl;
    } else {
        cout << "Arquivo '" << name << "' não encontrado." << endl;
    }
}

void delete_directory(BTree* tree, const char* name) {
    TreeNode* node = btree_search(tree, name);
    if (node && node->type == DIRECTORY_TYPE) {
        if (node->data.directory->tree->keys.empty()) {
            btree_delete(tree, name);
            cout << "Diretório '" << name << "' deletado." << endl;
        } else {
            cout << "Diretório '" << name << "' não está vazio." << endl;
        }
    } else {
        cout << "Diretório '" << name << "' não encontrado." << endl;
    }
}

Directory* get_root_directory() {
    Directory* root = new Directory();
    root->tree = btree_create(2);
    return root;
}

void change_directory(Directory** current, const char* path) {
    TreeNode* node = btree_search((*current)->tree, path);
    if (node && node->type == DIRECTORY_TYPE) {
        *current = node->data.directory;
        cout << "Diretório alterado para '" << path << "'." << endl;
    } else {
        cout << "Diretório '" << path << "' não encontrado." << endl;
    }
}

void list_directory_contents(Directory* dir) {
    if (!dir) return;
    cout << "Conteúdo do diretório:" << endl;
    btree_traverse(dir->tree);
}
