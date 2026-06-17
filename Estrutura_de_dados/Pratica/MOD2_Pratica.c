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

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return 1;
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("\n==================================\n");
        printf("       BIBLIOTECA - PARTE 2\n");
        printf("\n==================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimo\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n");
        printf("\n==================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("\n--- Cadastro de Novo Livro ---\n");

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
                    limparBufferEntrada();

                    biblioteca[totalLivros].disponivel = 1;

                    totalLivros++;

                    printf("\nLIvro cadastradoo com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!\n");
                }

                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 2: 
                printf("\n--- Lista de Livros Cadastrados ---\n");

                if (totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++) {
                        printf("-----------------------------------\n");
                        printf("Livro %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                        printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
                    }
                    printf("-----------------------------------\n");
                }

                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 3:  
                printf("\n--- Realizar Emprestimo ---\n");

                if  (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingidos!\n");
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
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);

                            emprestimos[totalEmprestimos].nomeUsuario[
                                strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")
                            ] = '\0';

                            emprestimos[totalEmprestimos].indiceLivro = indice;

                            biblioteca[indice].disponivel = 0;

                            totalEmprestimos++;

                            printf("\nEmprestimo realizado com sucesso!");
                        } else {
                            printf("\nNumero de livro invalido ou livro indisponivel.\n");
                        }
                    }
                }

                printf("\nPrecione Enter para continuar...");
                getchar();
                break;
            
            case 4:
                printf("\n--- Lista de Emprestimos ---\n");

                if (totalEmprestimos == 0) {
                    printf("Nenhum emprestimo realizado.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;

                        printf("--------------------------------------\n");
                        printf("EMPRESTIMO %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("--------------------------------------\n");
                }

                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;
               
            default:
                printf("\nOpcao invalida!\n");
                printf("\nPrecione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    free(biblioteca);
    free(emprestimos);

    printf("Memoria liberada com sucesso.\n");

    return 0;
}