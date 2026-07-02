#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10

void gerarListaOrdenada(int lista[], int n);
void gerarListaInversa(int lista[], int n);
void gerarListaAleatoria(int lista[], int n);

void bubbleSort(int lista[], int n);
void insertionSort(int lista[], int n);
void selectionSort(int lista[], int n);

void imprimirLista(const char *titulo, const int lista[], int n);
void copiarLista(int destino[], const int origem[], int n);

int main() {
    srand(time(NULL));

    int listaOrdenada[TAMANHO];
    int listaInversa[TAMANHO];
    int listaAleatoria[TAMANHO];
    int listaTemp[TAMANHO];

    printf("--- GERANDO LISTAS DE ENTRADA ---\n");
    gerarListaOrdenada(listaOrdenada, TAMANHO);
    gerarListaInversa(listaInversa, TAMANHO);
    gerarListaAleatoria(listaAleatoria, TAMANHO);
    printf("-------------------------------\n\n");

    printf("========== 1. BUBBLE SORT ==========\n");

    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaInversa, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);

    printf("========== 2. INSERTION SORT ==========\n");

    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaInversa, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);

    printf("========== 3. SELECTION SORT ==========\n");

    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaInversa, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);

    return 0;
}

void bubbleSort(int lista[], int n) {
    int i, j, temp;
    int trocou;

    for (i = 0; i < n - 1; i++) {
        trocou = 0;

        for (j = 0; j < n - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1;
            }
        }

        if (trocou == 0) {
            break;
        }
    }
}

void insertionSort(int lista[], int n) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = lista[i];
        j = i - 1;

        while (j >= 0 && lista[j] > chave) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }

        lista[j + 1] = chave;
    }
}

void selectionSort(int lista[], int n) {
    int i, j, indice_min, temp;

    for (i = 0; i < n - 1; i++) {
        indice_min = i;

        for (j = i + 1; j < n; j++) {
            if (lista[j] < lista[indice_min]) {
                indice_min = j;
            }
        }

        if (indice_min != i) {
            temp = lista[i];
            lista[i] = lista[indice_min];
            lista[indice_min] = temp;
        }
    }
}

void gerarListaOrdenada(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = i + 1;
    }

    imprimirLista("original - Ordenada", lista, n);
}

void gerarListaInversa(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = n - i;
    }

    imprimirLista("Original - Inversa", lista, n);
}

void gerarListaAleatoria(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = rand() % 100;
    }

    imprimirLista("Original - Aleatoria", lista, n);
}

void imprimirLista(const char *titulo, const int lista[], int n) {
    printf("%s: [ ", titulo);

    for (int i = 0; i < n; i++) {
        printf("%d ", lista[i]);
    }

    printf("]\n");
}

void copiarLista(int destino[], const int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

