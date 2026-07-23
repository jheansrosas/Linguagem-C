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
    char suspeito[50];

    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

#define TAMANHO_HASH 10

typedef struct Associacao {
    char pista[50];
    char suspeito[50];
    struct Associacao *proximo;
} Associacao;

Associacao *tabelaHash[TAMANHO_HASH];

Sala *criarSala(const char *nome, const char *pista, const char *suspeito);
void explorarSalas(Sala *atual, NoBST **raizPistas);
void liberarSalas(Sala *raiz);

NoBST *criarNoBST(const char *pista);
NoBST *inserirBST(NoBST *raiz, const char *pista);
void emOrdemBST(NoBST *raiz);
void liberarBST(NoBST *raiz);

int funcaoHash(const char *pista);
void inicializarHash();
void inserirNaHash(const char *pista, const char *suspeito);
void exibirAssociacao();
void liberarHash();

// Cria dinamicamente uma nova sala sem caminhos definidos
Sala *criarSala(const char *nome, const char *pista, const char *suspeito) {
    Sala *novaSala = (Sala *) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    strcpy(novaSala->suspeito, suspeito);

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

// Calcula o indice sa tabela com base na soma dos caracteres da pista
int funcaoHash(const char *pista) {
    int soma = 0;

    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }

    return soma % TAMANHO_HASH;
}

// Inicializa todas as posicoes da tabela hash como vazias
void inicializarHash() {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

// Insere uma associacao entre pista e suspeito na tabela hash
void inserirNaHash(const char *pista, const char *suspeito) {
    int indice = funcaoHash(pista);

    Associacao *nova = malloc(sizeof(Associacao));

    if (nova == NULL) {
        printf("Erro ao alocar memoria para a tabela hash.\n");
        exit(1);
    }

    strcpy(nova->pista, pista);
    strcpy(nova->suspeito, suspeito);

    nova->proximo = tabelaHash[indice];
    tabelaHash[indice] = nova;
}

// Monta o mapa da mansao e inicia a exploracao
int main() {
    inicializarHash();

    Sala *hall = criarSala("Hall de Entrada", "", "");

    hall->esquerda = criarSala("Sala de Estar", "Pegadas de lama", "Carlos");
    hall->direita = criarSala("Biblioteca", "Livro antigo", "Amanda");

    hall->esquerda->esquerda = criarSala("Cozinha", "Faca enferrujada", "Carlos");
    hall->esquerda->direita = criarSala("Jardim", "", "");

    hall->direita->esquerda = criarSala("Quarto", "Carta misteriosa", "Bruno");
    hall->direita->direita = criarSala("Escritorio", "Chave enferrujada", "Carlos");

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
            printf("Suspeito relacionado: %s\n", atual->suspeito);

            *raizPistas = inserirBST(*raizPistas, atual->pista);
            inserirNaHash(atual->pista, atual->suspeito);

            printf("Pista adicionada ao inventario.\n");

            atual->pista[0] = '\0';
            atual->suspeito[0] = '\0';
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