#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Estrutura que representa uma pessoa
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura que representa uma pilha
typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

// Inicializa a pilha vazia 
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

//Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

// Insere uma pessoa no topo da pilha
void push(Pilha *p, Pessoa nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Nao e possivel inserir.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;
}

// Remove a pessoa do topo da pilha
void pop(Pilha *p, Pessoa *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nao e possivel remover.\n");
        return;
    }

    *removida = p->itens[p->topo];
    p->topo--;
}

// Visualiza a pessoa do topo sem removê-la
void peek(Pilha *p, Pessoa *visualizada) {
    if (pilhaVazia(p)) {
        printf("Pilhaa vazia. Nao para espiar.\n");
        return;
    }

    *visualizada = p->itens[p->topo];
}

// Exibe todos os elementos da pilha (do topo para a base)
void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");

    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->itens[i].nome, p->itens[i].idade);
    }

    printf("\n");
}

int main() {
    Pilha p;
    inicializarPilha(&p);

    Pessoa a = {"Ana", 20};
    Pessoa b = {"Bruno", 35};
    Pessoa c = {"Carlos", 28};

    // Empilha as pessoas
    push(&p, a);
    push(&p, b);
    push(&p, c);

    mostrarPilha(&p);

    // Remove a pessoa do topo
    Pessoa removida;
    pop(&p, &removida);

    printf("Removida: %s, %d\n\n", removida.nome, removida.idade);

    mostrarPilha(&p);

    // Visualiza o topo da pilha
    Pessoa topo;
    peek(&p, &topo);

    printf("Topo atual: %s, %d\n", topo.nome, topo.idade);

    return 0;
}