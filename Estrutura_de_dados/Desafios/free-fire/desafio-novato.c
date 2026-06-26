#include <stdio.h>
#include <string.h>

#define TAM_MAX 10
#define TAM_STRING 50

// EStrutura que representa um item da mochila
typedef struct {
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
} Item;

void adicionarItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void exibirMenu(int totalItens);

int main() {
    // Vetor estático que armazena os itens da mochila
    Item mochila[TAM_MAX];
    
    int totalItens = 0;
    int opcao;

    do {
        exibirMenu(totalItens);
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nopcao invalida. Tente novamente.\n");
        } 
    } while (opcao != 0);

    return 0;
}

// Exibe o menu principal e a quantidade atual de intens na mochila
void exibirMenu(int totalItens) {
    printf("\n=====================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - ILHA\n");
    printf("\n=====================================\n");
    printf("Itens na Mochila: %d/%d\n", totalItens, TAM_MAX);
    printf("---------------------------------------\n");
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na mochila\n");
    printf("0. Sair\n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// Adiciona um novo item ao vetor, respeitando o limite máximo da mochila
void adicionarItem(Item mochila[], int *totalItens) {
    if (*totalItens == TAM_MAX) {
        printf("\nA mochila esta cheia!\n");
        return;
    }

    printf("\n==== ADICIONAR ITEM ====\n");

    printf("Nome do item: ");
    fgets(mochila[*totalItens].nome, TAM_STRING, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(mochila[*totalItens].tipo, TAM_STRING, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    getchar();

    (*totalItens)++;

    printf("\nItem adicionado com sucesso!\n");
}

// Lista todos os itens cadastrados em formato de tabela 
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nA mochila esta vazia.");
        return;
    }

    printf("\n===== ITENS NA MOCHILA =====\n");
    printf("%-20s | %-15s | %s\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-15s | %d\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade);
    }
}

// Remove um item pelo nome e reorganiza o vetor após a remoção
void removerItem(Item mochila[], int *totalItens) {
    char nome[TAM_STRING];
    int posicao = -1;

    if (*totalItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\nNome do item a remover: ");
    fgets(nome, TAM_STRING, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Procura o item pelo nome
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }

    // Desloca os itens para preencher o espaço vazio
    for (int i = posicao; i < *totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--;

    printf("\nItem removido com sucesso!");
}