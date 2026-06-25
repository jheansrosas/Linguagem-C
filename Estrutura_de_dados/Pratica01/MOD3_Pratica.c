#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimo {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro(struct Livro *biblioteca, int *totalLivros);
void listarLivros(const struct Livro *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos);

int main() {
    struct Livro *biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    struct Emprestimo *emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarLivro(biblioteca, &totalLivros);
                break;

            case 2:
                listarLivros(biblioteca, totalLivros);
                break;

            case 3:
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;

            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
                getchar();
                break;
        }

    } while (opcao != 0);

    liberarMemoria(biblioteca, emprestimos);

    return 0;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu() {
    printf("\n====================================\n");
    printf("       BIBLIOTECA - PARTE 3 (MESTRE)\n");
    printf("====================================\n");
    printf("1 - Cadastrar novo livro\n");
    printf("2 - Listar todos os livros\n");
    printf("3 - Realizar emprestimo\n");
    printf("4 - Listar emprestimos\n");
    printf("0 - Sair\n");
    printf("====================================\n");
    printf("Escolha uma opcao: ");
}

void cadastrarLivro(struct Livro *biblioteca, int *totalLivros) {
    printf("\n--- Cadastro de Novo Livro ---\n\n");

    if (*totalLivros < MAX_LIVROS) {
        int indice = *totalLivros;

        printf("Digite o nome do livro: ");
        fgets(biblioteca[indice].nome, TAM_STRING, stdin);

        printf("Digite o autor: ");
        fgets(biblioteca[indice].autor, TAM_STRING, stdin);

        printf("Digite a editora: ");
        fgets(biblioteca[indice].editora, TAM_STRING, stdin);

        biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0';
        biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0';
        biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0';

        printf("Digite a edicao: ");
        scanf("%d", &biblioteca[indice].edicao);
        limparBufferEntrada();

        biblioteca[indice].disponivel = 1;

        (*totalLivros)++;

        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("Biblioteca cheia!\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarLivros(const struct Livro *biblioteca, int totalLivros) {
    printf("\n--- Lista de Livros Cadastrados ---\n\n");

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("------------------------------------\n");
            printf("LIVRO %d\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
        }

        printf("------------------------------------\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void realizarEmprestimo(struct Livro *biblioteca, int totalLivros, struct Emprestimo *emprestimos, int *totalEmprestimos) {
    printf("\n--- Realizar Emprestimo ---\n\n");

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido!\n");
    } else {
        printf("Livros disponiveis:\n");

        int disponiveis = 0;

        for (int i = 0; i < totalLivros; i++) {
            if (biblioteca[i].disponivel) {
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }

        if (disponiveis == 0) {
            printf("Nenhum livro disponivel para emprestimo.\n");
        } else {
            int numLivro;

            printf("\nDigite o numero do livro que deseja emprestar: ");
            scanf("%d", &numLivro);
            limparBufferEntrada();

            int indice = numLivro - 1;

            if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                printf("Digite o nome do usuario: ");
                fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);

                emprestimos[*totalEmprestimos].nomeUsuario[
                    strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")
                ] = '\0';

                emprestimos[*totalEmprestimos].indiceLivro = indice;

                biblioteca[indice].disponivel = 0;

                (*totalEmprestimos)++;

                printf("\nEmprestimo realizado com sucesso!\n");
            } else {
                printf("\nNumero de livro invalido ou livro indisponivel.\n");
            }
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarEmprestimos(const struct Livro *biblioteca, const struct Emprestimo *emprestimos, int totalEmprestimos) {
    printf("\n--- Lista de Emprestimos ---\n\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            int indiceLivro = emprestimos[i].indiceLivro;

            printf("------------------------------------\n");
            printf("EMPRESTIMO %d\n", i + 1);
            printf("Livro: %s\n", biblioteca[indiceLivro].nome);
            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
        }

        printf("------------------------------------\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void liberarMemoria(struct Livro *biblioteca, struct Emprestimo *emprestimos) {
    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada com sucesso.\n");
}