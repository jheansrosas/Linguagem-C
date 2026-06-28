#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Protótipos - Busca Sequencial
int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item);
int buscaSequencialRecursiva_aux(const char* lista[], int tamanho, const char* item, int indice);

// Protótipos - Busca Binária
int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva(const char* lista[], int tamanho, const char* item);
int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim);

// Função auxiliar para imprimir os resultados
void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado);

int main() {
    const char* listaDeCompras[] = {
        "arroz",
        "batata",
        "cebola",
        "detergente",
        "feijão",
        "leite",
        "macarrão",
        "oleo",
        "sal",
        "tomate"
    };

    int tamanhoDaLista = sizeof(listaDeCompras) / sizeof(listaDeCompras[0]);

    const char* itemExistente = "leite";
    const char* itemInexistente = "queijo";

    printf("--- DEMOSTRACAO DE ALGORITMOS DE BUSCA EM LISTA DE TEXTO ---\n");
    printf("Lista utilizada: [arroz, batata, cebola, detergente, feijao, leite, macarrao, oleo, sal, tomate, pao]\n");
    printf("--------------------------------------------------------------\n\n");

    // Busca Sequencial
    printf("--- 1. BUSCA SEQUENCIAL ---\n");

    int res1 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequecial Iterativa", itemExistente, res1);

    int res2 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequecial Iterativa", itemInexistente, res2);

    printf("\n");

    int res3 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequecial Recursiva", itemExistente, res3);

    int res4 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequecial Recursiva", itemInexistente, res4);

    printf("--------------------------------------------------------------\n\n");


    // Busca Binária
    printf("--- 2. BUSCA BINARIA (requer lista ordenada) ---\n");

    int res5 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Binaria Iterativa", itemExistente, res5);

    int res6 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Binaria Iterativa", itemInexistente, res6);

    printf("\n");

    int res7 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Binaria Recursiva", itemExistente, res7);

    int res8 = buscaBinariaRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Binaria Recursiva", itemInexistente, res8);

    printf("--------------------------------------------------------------\n");

    return 0;
}

// Busca sequencial com laço for
int buscaSequencialIterativa(const char* lista[], int tamanho, const char* item) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(lista[i], item) == 0) {
            return i;
        }
    }

    return -1;
}

// Função principal da busca sequencial recurciva
int buscaSequencialRecursiva(const char* lista[], int tamanho, const char* item) {
    return buscaSequencialRecursiva_aux(lista, tamanho, item, 0);
}

// Função auxiliar da busca sequencial recurciva
int buscaSequencialRecursiva_aux(const char* lista[], int tamanho, const char* item, int indice) {
    if (indice >= tamanho) {
        return -1;
    }

    if (strcmp(lista[indice], item) == 0) {
        return indice;
    }

    return buscaSequencialRecursiva_aux(lista, tamanho, item, indice + 1);
}

// Busca binária como laço while
int buscaBinariaIterativa(const char* lista[], int tamanho, const char* item) {
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;

        int comparacao = strcmp(lista[meio], item);

        if (comparacao == 0) {
            return meio;
        } else if (comparacao > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }  
    }
    
    return -1;
}

// Função principal da busca binária recursiva
int buscaBinariaRecursiva(const char* lista[], int tamanho, const char* item) {
    return buscaBinariaRecursiva_aux(lista, item, 0, tamanho - 1);
}

// Função auxiliar da busca binária recursiva
int buscaBinariaRecursiva_aux(const char* lista[], const char* item, int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista[meio], item);

    if (comparacao == 0) {
        return meio;
    } else if (comparacao > 0) {
        return buscaBinariaRecursiva_aux(lista, item, inicio, meio - 1);
    } else {
        return buscaBinariaRecursiva_aux(lista, item, meio + 1, fim);
    }
}

// Imprime o resultado do busca
void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado) {
    printf("[%s] Buscando por \"%s\"...\n", nomeDaBusca, item);

    if (resultado != -1) {
        printf("  -> Resultado: Item encontrado no indice %d.\n", resultado);
    } else {
        printf("  -> Resultado: Item nao encontrado na lista.\n");
    }
}