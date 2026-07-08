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
            case 1: // Remove a primeira peça da fila e gera uma nova automaticamente
                Peca jogada;

                remover(&fila, &jogada);

                printf("\nPeca jogada: [%c %d]\n", jogada.nome, jogada.id);

                inserir(&fila, gerarPeca());

                break;

            case 2: // Insere uma nova peça no final da fila
                Peca reservada;

                remover(&fila, &reservada);
                push(&pilha, reservada);

                inserir(&fila, gerarPeca());
                break;
                
            case 3: 
                Peca usada;
                
                pop(&pilha, &usada);

                printf("\nPeca utilizada da reserva: [%c %d]\n", 
                    usada.nome, 
                    usada.id);

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

void inicializarPilha(Pilha*p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("\nA pilha de reserva esta cheia.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = peca;
}

void pop(Pilha *p, Peca *peca) {
    if (pilhaVazia(p)) {
        printf("\nA pilha de reserva esta vazia.\n");
        return;
    }

    *peca = p->itens[p->topo];
    p->topo--;
}

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

// Exibe o menu principal do jogo
void exibirMenu() {
    printf("\n1. Jogar peca\n");
    printf("2. Reservar peca\n");
    printf("3. Usar Peca Reservada\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}