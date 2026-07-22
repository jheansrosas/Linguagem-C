#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura que representa um no da BST de pistas
typedef struct NoBST {
    char pista[50];
    struct NoBST *esquerda;
    struct NoBST *direita;
} NoBST;

// Estrutura que representa cada comodo da mansao
typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala *criarSala(const char *nome, const char *pista);
void explorarSalas(Sala *atual, NoBST **raizPistas);
void liberarSalas(Sala *raiz);

NoBST *criarNoBST(const char *pista);
NoBST *inserirBST(NoBST *raiz, const char *pista);
void emOrdemBST(NoBST *raiz);
void liberarBST(NoBST *raiz);

// Cria dinamicamente uma nova sala sem caminhos definidos
Sala *criarSala(const char *nome, const char *pista) {
    Sala *novaSala = (Sala *) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

// Cria dinamicamente um novo no para a BST de pistas
NoBST *criarNoBST(const char *pista) {
    NoBST *novo = malloc(sizeof(NoBST));

    if (novo == NULL) {
        printf("Erro ao alocar memoria para a BST.\n");
        exit(1);
    }

    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

// Insere uma pista na BST seguindo a ordem alfabetica
NoBST *inserirBST(NoBST *raiz, const char *pista) {
    if (raiz == NULL) {
        return criarNoBST(pista);
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, pista);
    } else {
        raiz->direita = inserirBST(raiz->direita, pista);
    }

    return raiz;
}

// Exibe todas as pistas em ordem alfabetica
void emOrdemBST(NoBST *raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        emOrdemBST(raiz->direita);
    }
}

// Libera recursivamente toda a memoria da BST
void liberarBST(NoBST *raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);

        free(raiz);
    }
}

// Monta o mapa da mansao e inicia a exploracao
int main() {
    Sala *hall = criarSala("Hall de Entrada", "");

    hall->esquerda = criarSala("Sala de Estar", "Pegadas de lama");
    hall->direita = criarSala("Biblioteca", "Livro antigo");

    hall->esquerda->esquerda = criarSala("Cozinha", "Faca enferrujada");
    hall->esquerda->direita = criarSala("Jardim", "");

    hall->direita->esquerda = criarSala("Quarto", "Carta misteriosa");
    hall->direita->direita = criarSala("Escritorio", "Chave enferrujada");

    NoBST *raizPistas = NULL;
    explorarSalas(hall, &raizPistas);

    printf("\n===== PISTAS ENCONTRADAS =====\n");

    if (raizPistas == NULL) {
        printf("Nenhuma pista foi encontrada.\n");
    } else {
        emOrdemBST(raizPistas);
    }

    liberarSalas(hall);
    liberarBST(raizPistas);

    return 0;
}

// Permite ao jogador navegar pela arvore a partir da sala atual
void explorarSalas(Sala *atual, NoBST **raizPistas) {
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);

            *raizPistas = inserirBST(*raizPistas, atual->pista);

            printf("Pista adicionada ao inventario.\n");

            atual->pista[0] = '\0';
        }

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Este comodo nao possui outras passagens.\n");
            printf("Exploracao concluida!\n");
            break;
        }

        printf("Escolha um caminho:\n");
        printf("e - esquerda\n");
        printf("d - direita\n");
        printf("s - sair\n");
        printf("Opcao: ");

        scanf(" %c", &opcao);
        opcao = tolower(opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\nNao existe caminho pela esquerda.\n");
            }
        } else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\nNao existe caminho pela direita.\n");
            }
        } else if (opcao == 's') {
            printf("\nExploracao encerrada.\n");
            break;
        } else {
            printf("\nOpcao invalida.\n");
        }
    }
}

// Liberar recursivamente toda a memoria alocada para a arvore de salas
void liberarSalas(Sala *raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}