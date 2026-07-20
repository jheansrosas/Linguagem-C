#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_ALFABETO 26
#define TAMANHO_TEXTO 100

// ==========================================================
// BTS: Árvore Binária de Busca
// ==========================================================

// Estrutura que representa um nó da BTS
typedef struct NoBTS {
    char valor[50];
    struct NoBTS *esquerda;
    struct NoBTS *direita;
} NoBTS;

// EStrutura que representa um nó da Trie
typedef struct NoTrie {
    struct NoTrie *filhos[TAMANHO_ALFABETO];
    bool ehFimDePalavra;
} NoTrie;

// Protótipo das funções da BTS
NoBTS *criarNoBTS(const char *valor);
NoBTS *inserirBTS(NoBTS *raiz, const char *valor);
bool buscarBTS(NoBTS *raiz, const char *chave);
void emOrdemBTS(NoBTS *raiz);
void liberarBTS(NoBTS *raiz);

// Protótipo das funções da Trie
NoTrie *criarNoTrie(void);
void normalizar(const char *entrada, char *saida);
void inserirTrie(NoTrie *raiz, const char *palavra);
bool buscarTrie(NoTrie *raiz, const char *palavra);
void liberarPalavras(NoTrie *no, char *buffer, int nivel);
void liberarTrie(NoTrie *raiz);

int main() {
    // ===================================================
    // Demonstração da BTS
    // ===================================================

    printf("\n===== BTS =====\n");

    NoBTS *raizBTS = NULL;

    // Insere as pistas na árvore bináriaa de busca
    raizBTS = inserirBTS(raizBTS, "Pegadas de Lama");
    raizBTS = inserirBTS(raizBTS, "Chave perdida");
    raizBTS = inserirBTS(raizBTS, "Livro com pagina faltando");
    raizBTS = inserirBTS(raizBTS, "Lencol manchado");
    raizBTS = inserirBTS(raizBTS, "Gaveta perdida");

    // Exibe os valores em ordem alfabética
    printf("Em ordem (BTS): ");
    emOrdemBTS(raizBTS);
    printf("\n");

    // Realiza buscas na BTS
    printf(
        "Buscar 'Lencol manchado' (BTS): %s\n",
        buscarBTS(raizBTS, "Lencol manchado")
            ? "Encontrado"
            : "Nao encontrado"
    );

    printf(
        "Buscar 'Oculos' (BTS): %s\n",
        buscarBTS(raizBTS, "Oculos")
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
    liberarBTS(raizBTS);
    liberarTrie(raizTrie);

    return 0;
}