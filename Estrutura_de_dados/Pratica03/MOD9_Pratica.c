#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Estrutura que representa uma pessoa
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura da fila
typedef struct {
    Pessoa dados[MAX];
    int inicio;
    int fim;
} Fila;

// Estrutura da pilha
typedef struct {
    Pessoa dados[MAX];
    int topo;
} Pilha;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

// Inicializaa a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Insere uma pessoa no final da fila
void inserir(Fila *f, Pessoa p) {
    if (f->fim < MAX) {
        f->dados[f->fim++] = p;
    }
}

// Remove a primeira pessoa da fila
Pessoa remover(Fila *f) {
    return f->dados[f->inicio++];
}

// Empilha uma pessoa
void push(Pilha *p, Pessoa pessoa) {
    if (p->topo < MAX - 1) {
        p->dados[++p->topo] = pessoa;
    }
}

// Remove a pessoa do topo da pilha
Pessoa pop(Pilha *p) {
    return p->dados[p->topo--];
}

// Exibi todos os elementos da fila
void exibirFila(Fila f){
    for (int i = f.inicio; i < f.fim; i++) {
        printf("Nome: %s | Idade: %d\n",
            f.dados[i].nome,
            f.dados[i].idade);
    }
}

int main() {
    // Cria as duas filas e uma pilha auxiliar
    Fila filaOriginal, filaInvertida;
    Pilha auxiliar;

    // Inicializa todas as estruturas
    inicializarFila(&filaOriginal);
    inicializarFila(&filaInvertida);
    inicializarPilha(&auxiliar);

    // Pessoas utilizadas no exemplo
    Pessoa pessoas[] = {
        {"Carlos", 45},
        {"Joana", 62},
        {"Lucas", 30},
        {"Maria", 75}
    };

    // Insere as pessoas na fila original
    for (int i = 0; i < 4; i++) {
        inserir(&filaOriginal, pessoas[i]);
    }

    printf("Fila original:\n");
    exibirFila(filaOriginal);

    // Move todos os elementos da fila para a pilha
    while (filaOriginal.inicio < filaOriginal.fim) {
        push(&auxiliar, remover(&filaOriginal));
    }

    // Move os elementos da pilha para uma nova fila
    while (auxiliar.topo >= 0) {
        inserir(&filaInvertida, pop(&auxiliar));
    }

    printf("\nFila invertida:\n");
    exibirFila(filaInvertida);

    return 0;
}