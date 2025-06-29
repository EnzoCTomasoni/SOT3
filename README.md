# SOT3
Trabalho desenvolvido por Enzo C Tomasoni e Ian Marcos, referente a um simulador de sistema de arquivos, proposto na disciplina de Sistemas Operacionais durante a M3.

O código foi desenvolvido em C++ e organizado em três arquivos, a main.cpp onde está localizada a parte referente a inicialização e menu do programa, a filesystem.cpp onde estão as funções utilizadas no programa e por fim a filesystem.h onde estão as estruturas e assinaturas de funções passadas como base no enunciado do projeto.

O sistema apresenta as seguintes funcionabilidades atráves do menu:

- Criação de arquivos
- Criação de diretórios
- Remoção de arquivos
- Remoção de diretórios
- Listagem de arquivos e diretórios
- Seleção de diretório

Entradas esperadas:

- mkdir {nome do diretório}
- rmdir {nome do diretório}
- touch {nome do arquivo .txt} {conteudo}
- rm {nome do arquivo .txt}
- ls
- cd {nome do diretório}
- cd .. (para voltar ao diretório root)
