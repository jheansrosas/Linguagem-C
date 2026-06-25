#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50
#define TAM_MAX 10

typedef struct {
    char dados[TAM_MAX][MAX_STR_LEN];
    int quantidade;
} ListaEstatica;

typedef struct No {
    char *dado;
    struct No *proximo;
} No;

typedef No* ListaEncadeada;

//Prótotipos - Lista Estática
void inicializarListaEstatica(ListaEstatica *lista);
void inserirListaEstatica(ListaEstatica *lista, const char *texto);
void removerListaEstatica(ListaEstatica *lista, const char *texto);
void listarListaEstatica(const ListaEstatica *lista);

// Protótipo - lista Encadeada
void inicializarListaEncadeada(ListaEncadeada *lista);
void inserirListaEncadeada(ListaEncadeada *lista, const char *texto);
void removerListaEncadeada(ListaEncadeada *lista, const char *texto);
void listarListaEncadeada(const ListaEncadeada lista);
void liberarListaEncadeada(ListaEncadeada *lista);

// Menus
void menuListaEstatica();
void menuListaEncadeada();

int main() {
    int opcao;

    do {
        printf("\n--- MANIPULACAO DE LISTAS (TEXTO) ---\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair do Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuListaEstatica();
                break;

            case 2:
                menuListaEncadeada();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// LISTA ESTÁTICA
void inicializarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0;
}

void inserirListaEstatica(ListaEstatica *lista, const char *texto) {
    if (lista->quantidade == TAM_MAX) {
        printf("Erro: Lista cheia! Nao e possivel inserir.\n");
        return;
    }

    strcpy(lista->dados[lista->quantidade], texto);
    lista->quantidade++;

    printf("Texto \"%s\" inserido com sucesso.\n", texto);
}

void removerListaEstatica(ListaEstatica *lista, const char *texto) {
    int pos = -1;

    for (int i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: Texto \"%s\" nao encontrado na lista.\n", texto);
        return;
    }

    for (int i = pos; i < lista->quantidade - 1; i++) {
        strcpy(lista->dados[i], lista->dados[i + 1]);
    }

    lista->quantidade--;

    printf("Texto \"%s\" removido com sucesso.\n", texto);
}

void listarListaEstatica(const ListaEstatica *lista) {
    if (lista->quantidade == 0) {
        printf("A lista estatica esta vazia.\n");
        return;
    }

    printf("Itens da Lista Estatica: [ ");

    for (int i = 0; i < lista->quantidade; i++) {
        printf("\"%s\" ", lista->dados[i]);
    }

    printf("]\n");
}

// LISTA ENCADEADA
void inicializarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
}

void inserirListaEncadeada(ListaEncadeada *lista, const char *texto) {
    No *novoNo = (No *) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro: Falha na alocacao de memoria para o no.\n");
        return;
    }

    novoNo->dado = (char *) malloc(strlen(texto) + 1);

    if (novoNo->dado == NULL) {
        printf("Erro: Falha na alocacao de memoria para o texto.\n");
        free(novoNo);
        return;
    }

    strcpy(novoNo->dado, texto);

    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("Texto \"%s\" inserido com sucesso.\n", texto);
}

void removerListaEncadeada(ListaEncadeada *lista, const char *texto) {
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dado, texto) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Texto \"%s\" nao encontrado na lista.\n", texto);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual->dado);
    free(atual);

    printf("Texto \"%s\" removido com sucesso.\n", texto);
}

void listarListaEncadeada(const ListaEncadeada lista) {
    No *temp = lista;

    if (temp == NULL) {
        printf("A lista encadeada esta vazia.\n");
        return;
    }

    printf("Itens da Lista Encadeada: [ ");

    while (temp != NULL) {
        printf("\"%s\" ",temp->dado);
        temp = temp->proximo;
    }

    printf("]\n");
}

void liberarListaEncadeada(ListaEncadeada *lista) {
    No *atual = *lista;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual->dado);
        free(atual);
        atual = proximo;
    }

    *lista = NULL;
}

// MENUS

void menuListaEstatica() {
    ListaEstatica lista;
    int opcao;
    char texto[MAX_STR_LEN];

    inicializarListaEstatica(&lista);

    do {
        printf("\n--- LISTA ESTATICA ---\n");
        printf("1. Inserir texto\n");
        printf("2. Remover texto\n");
        printf("3. Listar textos\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o texto: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                inserirListaEstatica(&lista, texto);
                break;

            case 2:
                printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                removerListaEstatica(&lista, texto);
                break;

            case 3:
                listarListaEstatica(&lista);
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menuListaEncadeada() {
    ListaEncadeada lista;
    int opcao;
    char texto[MAX_STR_LEN];

    inicializarListaEncadeada(&lista);

    do {
        printf("\n--- LISTA ENCADEADA ---\n");
        printf("1. Inserir texto\n");
        printf("2. Remover texto\n");
        printf("3. Listar textos\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: 
                printf("Digite o texto: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                inserirListaEncadeada(&lista, texto);
                break;

            case 2:
            printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                removerListaEncadeada(&lista, texto);
                break;

            case 3:
                listarListaEncadeada(lista);
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    liberarListaEncadeada(&lista);
}