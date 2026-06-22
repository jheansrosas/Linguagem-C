#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()
#include <time.h>

#define QUANTIDADE_TERRITORIOS 5

// --- Definição da Estrutura (Struct) ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

typedef struct Territorio Territorio;

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n===== ATAQUE =====\n");
    printf("Atacante: %s tirou %d\n", atacante->nome, dadoAtacante);
    printf("Defensor: %s tirou %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu!\n");

        defensor->tropas--;

        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->cor, atacante->cor);
            printf("O territorio %s foi conquistado!\n", defensor->nome);
        }

    } else {
        printf("\nO defensor venceu!\n");

        atacante->tropas--;

        if (atacante->tropas < 0) {
            atacante->tropas = 0;
        }
        

    }
}

void exibirTerritorios(Territorio *territorios, int quantidade) {
    printf("\n===== MAPA DO MUNDO - ESTADO ATUAL =====\n");

    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s Exercito - %s, Tropas: %d\n",
            i + 1,
            territorios[i].nome,
            territorios[i].cor,
            territorios[i].tropas);
    }
}

void inicializarTerritorios(Territorio *territorios) {
    strcpy(territorios[0].nome, "America");
    strcpy(territorios[0].cor, "Azul");
    territorios[0].tropas = 3;

    strcpy(territorios[1].nome, "Europa");
    strcpy(territorios[1].cor, "Verde");
    territorios[1].tropas = 2;

    strcpy(territorios[2].nome, "Asia");
    strcpy(territorios[2].cor, "Vermelho");
    territorios[2].tropas = 4;

    strcpy(territorios[3].nome, "Africa");
    strcpy(territorios[3].cor, "Amarelo");
    territorios[3].tropas = 2;

    strcpy(territorios[4].nome, "Oceania");
    strcpy(territorios[4].cor, "Branco");
    territorios[4].tropas = 2;
}

int sorteMissao() {
    return rand() % 2;
}

void exibirMissao(int missao) {
    printf("\n===== SUA MISSAO =====\n");

    if (missao == 0) {
        printf("Destruir o exercito Verde.\n");
    } else {
        printf("Conquistar 3 territorios.\n");
    }
}

void exibirMenu() {
    printf("\n===== MENU =====\n");
    printf("1 - Atacar\n");
    printf("2 - Verficar Missao\n");
    printf("0 - sair\n");
    printf("Escolha uma opcao: \n");
}

// --- Função para Limpar o buffer de entrada ---
void limparbufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// --- Função Principal (main) ---
int main() {
    srand(time(NULL)); // Para gerar valores diferentes a cada execução.
    // Vetor que armazenará os 5 territórios
    Territorio *territorios;

    int quantidade = QUANTIDADE_TERRITORIOS;

    territorios = (Territorio *) calloc(quantidade, sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    inicializarTerritorios(territorios);

    int missao = sorteMissao();

    exibirMissao(missao);
    
    int atacante;
    int defensor;

    do {
        exibirTerritorios(territorios, quantidade);

        printf("\nEscolha o territorio atacante (1 a %d) ou 0 para sair: ", quantidade);
        scanf("%d", &atacante);

        if (atacante == 0) {
            printf("\nEncerrando o jogo...\n");
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", quantidade);
        scanf("%d", &defensor);

        limparbufferEntrada();

        atacante--;
        defensor--;

        if (atacante < 0 || atacante >= quantidade || defensor < 0 || defensor >= quantidade) {
            printf("\nEscolha invalida de territorio. Tente novamente.\n");
            continue;
        }

        if (atacante == defensor) {
            printf("\nO atacante e o defensor nao podem ser o mesmo territorio. Tente novamente.\n");
            continue;
        }

        if (territorios[atacante].tropas <= 0 || territorios[defensor].tropas <= 0) {
            printf("\nTerritorios com 0 tropas nao podem atacar ou defender.\n");
            continue;
        }

        atacar(&territorios[atacante], &territorios[defensor]);

    } while (1); 

    // Exibição dos territórios cadastrados
    exibirTerritorios(territorios, quantidade);

    free(territorios);

    return 0; //Fim do programa.
}