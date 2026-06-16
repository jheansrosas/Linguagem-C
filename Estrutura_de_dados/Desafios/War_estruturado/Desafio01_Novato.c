#include <stdio.h>
#include <string.h> // Para strcspn()

// --- Definição da Enstrutura (Struct) ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Função para Limpar o buffer de entrada ---
void limparbufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// --- Função Principal (main) ---
int main() {
    // Vetor que armazenará os 5 territórios
    struct Territorio territorios[5];
    
    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);

        // Remove o '\n' capturado pelo fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        limparbufferEntrada();
    }

    // Exibição dos territórios cadastrados
    printf("\n===== TERRITORIOS CADASTRADOS =====\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito(ex: vermelho, amarelo): %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0; //Fim do programa.
}