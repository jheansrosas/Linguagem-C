#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura que representa a pilha de peças reservadas
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// Protótipos das funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca();
void inserir(Fila *f, Peca p);
void remover(Fila *f, Peca *p);
void mostrarFila(Fila *f);
void preencherFilaInicial(Fila *f);
void exibirMenu();

void inicializarPilha(Pilha*p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void push(Pilha *p, Peca peca);
void pop(Pilha *p, Peca *peca);
void mostrarPilha(Pilha *p);

void trocarPecaAtual(Fila *fila, Pilha *pilha);
void trocarTresPecas(Fila *fila, Pilha *pilha);

int main() {
    srand(time(NULL));

    // Cria a fila principal do jogo
    Fila fila;
    Pilha pilha;
    int opcao;

    // Inicializa e preenche a fila com 5 peças
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    preencherFilaInicial(&fila);

    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);
        exibirMenu();

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {  // Remove a primeira peça da fila e gera uma nova automaticamente
                Peca jogada;

                remover(&fila, &jogada);

                printf("\nPeca jogada: [%c %d]\n", jogada.nome, jogada.id);

                inserir(&fila, gerarPeca());

                break;
            }

            case 2: {  // Move a peça da frente para a pilha e gera uma nova peça
                if (pilhaCheia(&pilha)) {
                    printf("\nA pilha de reserva esta cheia.\n");
                    break;
                }

                Peca reservada;

                remover(&fila, &reservada);
                push(&pilha, reservada);

                inserir(&fila, gerarPeca());
                break;
            }
                
            case 3: {
                if (pilhaVazia(&pilha)) {
                    printf("\nA pilha de reserva esta vazia.\n");
                    break;
                }
                
                Peca usada;
                
                pop(&pilha, &usada);

                printf("\nPeca utilizada da reserva: [%c %d]\n", 
                    usada.nome, 
                    usada.id);

                break;
            }
            
            case 4:
                trocarPecaAtual(&fila, &pilha);
                break;
                  
            case 5:
                trocarTresPecas(&fila, &pilha);
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila atingiu sua capacidade máxima
int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera automaticamente uma nova peça com tipo aleatório e ID único
Peca gerarPeca() {
    Peca p;

    char tipos[] = {'I', 'O', 'T', 'L'};
    static int proximoId = 1;
    
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

// Insere uma peça no final da fila circular
void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nA fila esta cheia.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

// Remove a peça localizada no início da fila
void remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}

// Preenche a fila inicial com 5 peças geradas automaticamente
void preencherFilaInicial(Fila *f) {
    for (int i = 0; i < MAX_FILA; i++) {
        inserir(f, gerarPeca());
    }
}

// Exibe todas as peças presentes na fila
void mostrarFila(Fila *f) {
    printf("\nFila de Pecas: ");

    for (int i = 0, idx = f->inicio;
         i < f->total;
         i++, idx = (idx + 1) % MAX_FILA) {

            printf("[%c %d] ", 
                    f->itens[idx].nome, 
                    f->itens[idx].id);
    }

    printf("\n");
}

// Inicializa a pilha de reserva vazia
void inicializarPilha(Pilha*p) {
    p->topo = -1;
}

// Verifica se a pilha atingiu sua capacidade máxima
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Insere uma peça no topo da pilha de reserva
void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("\nA pilha de reserva esta cheia.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = peca;
}

// Remove uma peça do topo da pilha reserva
void pop(Pilha *p, Peca *peca) {
    if (pilhaVazia(p)) {
        printf("\nA pilha de reserva esta vazia.\n");
        return;
    }

    *peca = p->itens[p->topo];
    p->topo--;
}

// Exibe as peças reservadas do topo para a base
void mostrarPilha(Pilha *p) {
    printf("\nPilha de reserva (Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("Vazia");
    } else {
        for (int i = p->topo; i>= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }

    printf("\n");
}

// Troca a peça da frente da fila com a peça do topo da pilha
void trocarPecaAtual(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila)) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    if (pilhaVazia(pilha)) {
        printf("\nA pilha de reserva esta vazia.\n");
        return;
    }

    Peca temporaria = fila->itens[fila->inicio];

    fila->itens[fila->inicio] = pilha->itens[pilha->topo];
    pilha->itens[pilha->topo] = temporaria;

    printf("\nTroca realizada entre a frente da fila e o topo da pilha.\n");
}

// Troca as três primeiras peças da fila com as três peças da pilha
void trocarTresPecas(Fila *fila, Pilha *pilha) {
    if (fila->total < 3){
        printf("\nA fila precisa ter pelo menos 3 pecas.\n");
        return;
    }

    if (pilha->topo < 2) {
        printf("\nA pilha precisa ter 3 pecas reservadas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int indiceFila = (fila->inicio + i) % MAX_FILA;
        int indicePilha = pilha->topo - i;

        Peca temporaria = fila->itens[indiceFila];

        fila->itens[indiceFila] = pilha->itens[indicePilha];
        pilha->itens[indicePilha] = temporaria;
    }

    printf("\nTroca realizada entre 3 primeiras pecas da fila e as 3 pecas da pilha.\n");
}

// Exibe o menu principal do jogo
void exibirMenu() {
    printf("\n1. Jogar peca\n");
    printf("2. Reservar peca\n");
    printf("3. Usar Peca Reservada\n");
    printf("4. Trocar peca da frente da fila com o topo da pilha\n");
    printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}