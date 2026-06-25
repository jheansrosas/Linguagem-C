#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// --- Constantes Globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// --- Definição da Instrutura (Struct) ---
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// --- Função para Limpar o buffer de entrada ---
void limparbufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// --- Função Principal (main) ---
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    // --- Laço Principal do Menu ---
    do {

        //Exibe o menu de opções.
        printf("============================\n");
        printf("   BIBLIOTECA - PARTE 1\n");
        printf("============================\n");
        printf("1 - Cadrastar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma opcao: ");

        //Lê a opção do usuário.
        scanf("%d", &opcao);
        limparbufferEntrada(); // Limpar o '\n' deixado pelo scanf.

        // --- Processamento da opção ---
        switch (opcao) {
            case 1: // CADASTRO DE LIVRO
                printf("--- Cadrastro de Novo Livro ---\n\n");

                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparbufferEntrada();

                    totalLivros++;

                    printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Não e possivel cadrastar mais livros.\n");
                }

                printf("\nPrecione Enter para coninuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu.
                break;

            case 2: // LISTAGEM DE LIVROS
                printf("--- Lista de Livros Cadastrados ---");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("-------------------------------\n");
                        printf("LVIRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("---------------------------------\n");
                }

                // A pausa é crucial para que o usuário veja a lista antes do próximo loop limpar a tela.
                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 0: // SAIR
                printf("\nSaindo do sistema...");
                break;

            default: //OPÇÃO INVÁLIDA
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

        }

    } while (opcao != 0);

    return 0; //Fim do programa.
}