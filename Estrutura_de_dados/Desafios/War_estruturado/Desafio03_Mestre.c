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

void atacar(Territorio *atacante, Territorio *defensor, int *territoriosConquistados) {
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
            (*territoriosConquistados)++;
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
        printf("%d. %s: Exercito - %s, Tropas: %d\n",
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

int verificarMissao(Territorio *territorios, int quantidade, int missao, int territoriosConquistados) {
    if (missao == 0) {
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(territorios[i].cor, "Verde") == 0) {
                return 0;
            }
        }

        return 1;
    }

    if (missao == 1) {
        if (territoriosConquistados >= 3) {
            return 1;
        }
        return 0;
    }

    return 0;
}

void exibirMenu() {
    printf("\n========== MENU ==========\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
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

    printf("\n===== INICIANDO JOGO WAR =====\n");

    exibirMissao(missao);
    
    int atacante;
    int defensor;

    int opcao;

    int territoriosConquistados = 0;

    do {
        exibirTerritorios(territorios, quantidade);
        exibirMenu();
        scanf("%d", &opcao);
        limparbufferEntrada();

        switch (opcao) {
            case 1:
                printf("\nOpcao atacar escolhida.\n");

                printf("\n========================================\n");
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

                if (territorios[atacante].tropas <= 0) {
                    printf("\nTerritorios com 0 tropas nao pode atacar.\n");
                    continue;
                }

                atacar(
                    &territorios[atacante], 
                    &territorios[defensor],
                    &territoriosConquistados
                );

                break;

            case 2:
                exibirMissao(missao);

                if (verificarMissao(territorios, quantidade, missao, territoriosConquistados)) {
                    printf("\nParabens! Voce completou sua missao!\n");
                } else {
                    printf("\nMissao ainda nao concluida.\n");
                }
                break;

            case 0:
                printf("\nSaindo do jogo...");
                break;

            default: 
                printf("Opcao invalida. tente novamente.\n");
                break;        
        }

        

    } while (opcao != 0); 

    // Exibição dos territórios cadastrados
    exibirTerritorios(territorios, quantidade);

    free(territorios);

    return 0; //Fim do programa.
}