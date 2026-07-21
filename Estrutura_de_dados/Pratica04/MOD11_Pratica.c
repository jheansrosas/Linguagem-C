#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_ALFABETO 26
#define TAMANHO_TEXTO 100

// ==========================================================
// BTS: Árvore Binária de Busca
// ==========================================================

// Estrutura que representa um nó da BST
typedef struct NoBST {
    char valor[50];
    struct NoBST *esquerda;
    struct NoBST *direita;
} NoBST;

// Estrutura que representa um nó da Trie
typedef struct NoTrie {
    struct NoTrie *filhos[TAMANHO_ALFABETO];
    bool ehFimDePalavra;
} NoTrie;

// Protótipo das funções da BTS
NoBST *criarNoBST(const char *valor);
NoBST *inserirBST(NoBST *raiz, const char *valor);
bool buscarBST(NoBST *raiz, const char *chave);
void emOrdemBST(NoBST *raiz);
void liberarBST(NoBST *raiz);

// Protótipo das funções da Trie
NoTrie *criarNoTrie(void);
void normalizar(const char *entrada, char *saida);
void inserirTrie(NoTrie *raiz, const char *palavra);
bool buscarTrie(NoTrie *raiz, const char *palavra);
void listarPalavras(NoTrie *no, char *buffer, int nivel);
void liberarTrie(NoTrie *raiz);

int main() {
    // ===================================================
    // Demonstração da BST
    // ===================================================

    printf("\n===== BST =====\n");

    NoBST *raizBST = NULL;

    // Insere as pistas na árvore bináriaa de busca
    raizBST = inserirBST(raizBST, "Pegadas de Lama");
    raizBST = inserirBST(raizBST, "Chave perdida");
    raizBST = inserirBST(raizBST, "Livro com pagina faltando");
    raizBST = inserirBST(raizBST, "Lencol manchado");
    raizBST = inserirBST(raizBST, "Gaveta perdida");

    // Exibe os valores em ordem alfabética
    printf("Em ordem (BST): ");
    emOrdemBST(raizBST);
    printf("\n");

    // Realiza buscas na BTS
    printf(
        "Buscar 'Lencol manchado' (BTS): %s\n",
        buscarBST(raizBST, "Lencol manchado")
            ? "Encontrado"
            : "Nao encontrado"
    );

    printf(
        "Buscar 'Oculos' (BTS): %s\n",
        buscarBST(raizBST, "Oculos")
            ? "Encontrado"
            : "Nao encontrado"
    );

    // ====================================================
    // Demonstração da Trie
    // ====================================================

    printf("\n===== Trie =====\n");

    NoTrie *raizTrie = criarNoTrie();
    char normalizada[TAMANHO_TEXTO];

    // Normaliza e insere as palavras na Trie
    normalizar("Pegadas de Lama", normalizada);
    inserirTrie(raizTrie, normalizada);

    normalizar("Chave perdida", normalizada);
    inserirTrie(raizTrie, normalizada);

    normalizar("Livro com pagina faltando", normalizada);
    inserirTrie(raizTrie, normalizada);

    normalizar("Lencol manchado", normalizada);
    inserirTrie(raizTrie, normalizada);

    normalizar("Gaveta perdida", normalizada);
    inserirTrie(raizTrie, normalizada);

    // Exibe todas as palavras armazenadas em Trie
    printf("Palavras na Trie: ");

    char buffer[TAMANHO_TEXTO];
    listarPalavras(raizTrie, buffer, 0);

    printf("\n");

    // Normaliza antes de realizar a busca
    normalizar("Lencol manchado", normalizada);

    printf(
        "Buscar 'Lencolmanchado' (Trie): %s\n",
        buscarTrie(raizTrie, normalizada)
            ? "Encontrado"
            : "Nao encontrado"
    );

    normalizar("Oculos", normalizada);

    printf(
        "Buscar 'oculos' (Trie): %s\n",
        buscarTrie(raizTrie, normalizada)
            ? "Encontrado"
            : "Nao encontrado"
    );

    // Libera toda a memória alocada
    liberarBST(raizBST);
    liberarTrie(raizTrie);

    return 0;
}

// =======================================================
// Funções da BST
// =======================================================

// Cria dinamicamente um novo nó da BST
NoBST *criarNoBST(const char *valor) {
    NoBST *novo = malloc(sizeof(NoBST));

    if (novo == NULL) {
        printf("Erro ao alocar memoria para a BST.\n");
        exit(1);
    }

    strcpy(novo->valor, valor);

    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

// Inserir um valor na BST seguindo a ordem alfabética
NoBST *inserirBST(NoBST *raiz, const char *valor) {
    // Encontrou uma posição vazia
    if (raiz == NULL) {
        return criarNoBST(valor);
    }

    // Valores menores ficam na subárvore esquerda
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, valor);
    } else {
        // Valores maiores ou iguais ficam na subárvore direita
        raiz->direita = inserirBST(raiz->direita, valor);
    }

    return raiz;
}

// Procura uma chave na BST
bool buscarBST(NoBST *raiz, const char *chave) {
    // A chave não foi encontrada
    if (raiz == NULL) {
        return false;
    }

    int comparacao = strcmp(chave, raiz->valor);

    // A chave corresponde ao valor do nó atual
    if (comparacao == 0) {
        return true;
    }

    // Procura na subárvore esquerda
    if (comparacao < 0) {
        return buscarBST(raiz->esquerda, chave);
    }

    // Procura na subárvore direita
    return buscarBST(raiz->direita, chave);
}

// Exibe os elementos da BST em ordem alfabética
void emOrdemBST(NoBST *raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esquerda);

        printf("%s, ", raiz->valor);

        emOrdemBST(raiz->direita);
    }
}

// Libera recursivamente a memória usada pela BST
void liberarBST(NoBST *raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);

        free(raiz);
    }
}

// =======================================================
// Funções da Trie
// =======================================================

// Cria dinamicamente um novo nó da Trie
NoTrie *criarNoTrie(void) {
    NoTrie *novo = malloc(sizeof(NoTrie));

    if (novo == NULL) {
        printf("Erro ao alocar memoria para a Trie.\n");
        exit(1);
    }

    novo->ehFimDePalavra = false;

    // Todos os filhos começam vazios
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        novo->filhos[i] = NULL;
    }

    return novo;
}

// Converte letras maiúsculas em minúsculas e remove
// espaços, números, símbolos e outros caracteres
void normalizar(const char *entrada, char *saida) {
    int j = 0;

    for (int i = 0; entrada[i] != '\0'; i++) {
        char caractere = entrada[i];

        // Converte letra maiúscula para minúscula
        if (caractere >= 'A' && caractere <= 'Z') {
            caractere += 32;
        }

        // Copia apenas letras minúsculas sem acento
        if (caractere >= 'a' && caractere <= 'z') {
            saida[j] = caractere;
            j++;
        }
    }

    saida[j] = '\0';
}

// Insere uma palavra previamente normalizada na Trie
void inserirTrie(NoTrie *raiz, const char *palavra) {
    NoTrie *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        // Cria o caminho quando o caractere ainda não existe
        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNoTrie();
        }

        atual = atual->filhos[indice];
    }

    // Marca o último nó como fim de uma palavra válida
    atual->ehFimDePalavra = true;
}

// Procura uma palavra completa na Trie
bool buscarTrie(NoTrie *raiz, const char *palavra) {
    NoTrie *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        // O caminho necessário não existe
        if (atual->filhos[indice] == NULL) {
            return false;
        }

        atual = atual->filhos[indice];
    }

    // Só retorna verdadeiro quando a palavra termina nesse nó
    return atual != NULL && atual->ehFimDePalavra;
}

// Percorre a Trie e exibe as palavras em ordem lexicográfica
void listarPalavras(NoTrie *no, char *buffer, int nivel) {
    if (no == NULL) {
        return;
    }

    // Encontrou o fim de uma palavra
    if (no->ehFimDePalavra) {
        buffer[nivel] = '\0';
        printf("%s, ", buffer);
    }

    // Percorre os filhos de 'a' até 'z'
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;

            listarPalavras(
                no->filhos[i],
                buffer,
                nivel + 1
            );
        }
    }
}

// Libera recursivamente todos os nós da Trie
void liberarTrie(NoTrie *raiz) {
    if (raiz == NULL) {
        return;
    }

    // Libera primeiro todos os filhos
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        liberarTrie(raiz->filhos[i]);
    }

    free(raiz);
}