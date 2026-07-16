#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um nó da árvore binária
typedef struct No {
    char valor[50];
    struct No *esquerda;
    struct No *direita;
} No;

// Protótipos das funções
No *criarNo(const char *valor);
No *inserir(No *raiz, const char *valor);

void preOrdem(No *raiz);
void emOrdem(No *raiz);
void posOrdem(No *raiz);

void liberar(No *raiz);

int main() {
    // Inicializa a árvore vazia
    No *raiz = NULL;

    // Insere os valores iniciais na árvore
    raiz = inserir(raiz, "Hall de Entrada");
    raiz = inserir(raiz, "Sala de Estar");
    raiz = inserir(raiz, "Biblioteca");
    raiz = inserir(raiz, "Quarto");

    // Exibe a árvore em pré-ordem
    printf("Pre-ordem: ");
    preOrdem(raiz);
    printf("\n");

    // Exibe a árvore em ordem
    printf("Em ordem: ");
    emOrdem(raiz);
    printf("\n");
    
    // Exibe a árvore em pós-ordem
    printf("Pos-ordem: ");
    posOrdem(raiz);
    printf("\n");
    
    // Liberar toda a memória usada pela árvore
    liberar(raiz);

    return 0;
}

// Cria um novo nó da árvore
No *criarNo(const char *valor) {
    // Aloca memória dinamicamente para o novo nó
    No *novo = malloc(sizeof(No));

    //Verifica se a alocação de memória funcionou
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    // Copia o valor reecebido para o campo do nó
    strcpy(novo->valor, valor);

    // O novo nó começa sem filhos
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

// Insere um novo valor na árvore binária de busca
No *inserir(No *raiz, const char *valor) {
    // Se a árvore ou subárvore esetiver vazia, cria um novo nó
    if (raiz == NULL) {
        return criarNo(valor);
    }

    // Valores aalfabeticamente menores ficam à esquerda
    if (strcmp(valor, raiz->valor) < 0) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        // Valores maiores ou iguais ficam à direita
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

// Percorre a árvore em pré-ordem: raiz, esquerda e direita
void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Percorre a árvore em ordem: esquerda, raiz e direita
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Percorre a árvore em pós-ordem: esquerda, direita e raiz
void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%s ", raiz->valor);
    }
}

// Libera recursivamente toda a memória alocada pela árvore
void liberar(No *raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}