#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX 10
#define TAM_STRING 50

// Estrutura que representa um item da mochila
typedef struct {
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
    int prioridade;
} Item;

void adicionarItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void exibirMenu(int totalItens, bool ordenadoPorNome);
void buscarItemPorNome(Item mochila[], int totalItens);

void ordenarMochila(Item mochila[], int totalItens, bool *ordenadoPorNome);
void insertionSort(Item mochila[], int totalItens, int criterio, int *comparacoes);
int buscaBinaraiaPorNome(Item mochila[], int totalItens, const char nomeBusca[]);
void buscarItemBinario(Item mochila[], int totalItens, bool ordenadoPorNome);

int main() {
    // Vetor estático que armazena os itens da mochila
    Item mochila[TAM_MAX];
    
    int totalItens = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        exibirMenu(totalItens, ordenadoPorNome);
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &totalItens);
                ordenadoPorNome = false;
                break;

            case 2:
                removerItem(mochila, &totalItens);
                ordenadoPorNome = false;
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                ordenarMochila(mochila, totalItens, &ordenadoPorNome);
                break;

            case 5:
                buscarItemBinario(mochila, totalItens, ordenadoPorNome);
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        } 
    } while (opcao != 0);

    return 0;
}

// Exibe o menu principal e a quantidade atual de itens na mochila
void exibirMenu(int totalItens, bool ordenadoPorNome) {
    printf("\n=====================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - ILHA\n");
    printf("\n=====================================\n");
    printf("Itens na Mochila: %d/%d\n", totalItens, TAM_MAX);
    printf("Status de Ordenacao por Nome: %s\n",
            ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
    printf("---------------------------------------\n");
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Organizar Mochila (Ordenar Itens)\n");
    printf("5. Busca Binaria por Nome\n");
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

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[*totalItens].prioridade);
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
    printf("%-20s | %-15s | %-10s | %s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-15s | %-10d | %d\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade,
            mochila[i].prioridade);
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

    printf("\nItem removido com sucesso!\n");
}

// Busca um item pelo nome usando busca sequencial
void buscarItemPorNome(Item mochila[], int totalItens) {
    char nomeBusca[TAM_STRING];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, TAM_STRING, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Percorre todos os itens procurando pelo nome informado
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            encontrado = 1;
            break;
        }
    }

    if  (encontrado == 0) {
        printf("\nItem nao encontrado na mochila.\n");
    }
}