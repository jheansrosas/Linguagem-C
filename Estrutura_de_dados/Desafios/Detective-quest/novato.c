#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala *criarSala(const char *nome);
void explorarSalas(Sala *atual);
void liberarSalas(Sala *raiz);

Sala *criarSala(const char *nome) {
    Sala *novaSala = (Sala *) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

int main() {
    Sala *hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Biblioteca");

    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Jardim");

    hall->direita->esquerda = criarSala("Quarto");
    hall->direita->direita = criarSala("Esecritorio");

    explorarSalas(hall);

    liberarSalas(hall);

    return 0;
}

void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVoce chegou a: %s\n", atual->nome);
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

// Liberar toda a memória alocada para a árvore
void liberarSalas(Sala *raiz) {
    if (raiz != NULL) {
        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);
        free(raiz);
    }
}