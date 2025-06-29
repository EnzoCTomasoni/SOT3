#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <cstddef>

typedef enum { FILE_TYPE, DIRECTORY_TYPE } NodeType;

typedef struct File {
    char* name;
    char* content;
    size_t size;
} File;

typedef struct Directory Directory;

typedef struct TreeNode {
    char* name;
    NodeType type;
    union {
        File* file;
        Directory* directory;
    } data;
} TreeNode;

typedef struct BTree BTree;

struct Directory {
    BTree* tree;
};

// Protótipos
BTree* btree_create(int t);
void btree_insert(BTree* tree, TreeNode* node);
void btree_delete(BTree* tree, const char* name);
TreeNode* btree_search(BTree* tree, const char* name);
void btree_traverse(BTree* tree);

TreeNode* create_txt_file(const char* name, const char* content);
void delete_txt_file(BTree* tree, const char* name);

TreeNode* create_directory(const char* name);
void delete_directory(BTree* tree, const char* name);

Directory* get_root_directory();
void change_directory(Directory** current, const char* path);
void list_directory_contents(Directory* dir);

#endif // FILESYSTEM_H
