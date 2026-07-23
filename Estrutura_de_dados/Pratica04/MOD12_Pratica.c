#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

// =======================================================
// Tabela Hash com Encadeamento
// =======================================================

// Nó de lista ligada usada para tratar colisões
typedef struct Nodo {
    char valor[50];
    struct Nodo *proximo;
} Nodo;

// Cada posição aponta para o início de uma lista ligada
Nodo *tabela_chaining[TAMANHO_TABELA];

// =======================================================
// Tabelaa Hash com Sondagem Linear
// =======================================================

// Representa uma posição de tabela linear
typedef struct {
    char valor[50];

    // 0 = livre
    // 1 = ocupado
    // -1 = removido
    int ocupado;
} Entrada;

Entrada tabela_linear[TAMANHO_TABELA];

// Protótipos
int funcao_hash(const char *chave);

void inserir_chaining(const char *valor);
Nodo *buscar_chaining(const char *valor);
void remover_chaining(const char *valor);
void mostrar_chaining(void);
void liberar_chaining(void);

void inserir_linear(const char *valor);
int buscar_linear(const char *valor);
void remover_linear(const char *valor);
void mostrar_linear(void);

int main() {
    // Inicializa as duas tabelas
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_chaining[i] = NULL;
        tabela_linear[i].ocupado = 0;
    }

    // Valores utilizados na demonstração
    const char *palavras[] = {
        "Ana",
        "Bruno",
        "Carlos",
        "Amanda",
        "Paulo",
        "Lucas",
        "Marina",
        "Joana",
        "Roberta",
        "Clara",
        "Daniel"
    };

    int quantidade = sizeof(palavras) / sizeof(palavras[0]);

    // Insere os mesmos valores nas duas tabelas
    for (int i = 0; i < quantidade; i++) {
        inserir_chaining(palavras[i]);
        inserir_linear(palavras[i]);
    }

    // Mostra o estado das tabelas depois das inserções
    printf("\n====== TABELAS APOS INSERCOES =====\n");

    mostrar_chaining();
    mostrar_linear();

    // Realiza algumas buscas
    printf(
        "\nBuscando 'Bruno' (chaining): %s\n",
        buscar_chaining("Bruno") != NULL
            ? "Encontrado"
            : "Nao encontrado"
    );

    printf(
        "Buscando 'Joana' (linear): %s\n",
        buscar_linear("Joana") != -1
            ? "Encontrado"
            : "Nao encontrado"
    );

    printf(
        "Buscando 'Zeca' (chaining): %s\n",
        buscar_chaining("Zeca") != NULL
            ? "Encontrado"
            : "Nao encontrado"
    );

    // Remove valores existentes e inexistentes
    printf("\n===== REMOCOES =====\n");

    remover_chaining("Carlos");
    remover_linear("Carlos");

    remover_chaining("Zeca");
    remover_linear("Zeca");

    // Mostra o estado final
    printf("\n===== ESTADO FINAL DAS TABELAS =====\n");

    mostrar_chaining();
    mostrar_linear();

    // Libera a memória utilizada pelas listas ligadas
    liberar_chaining();

    return 0;
}

// =====================================================
// Função Hash
// =====================================================

// Soma os valores ASCII dos caracteres e calcula o índice
int funcao_hash(const char *chave) {
    int soma = 0;

    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }

    return soma % TAMANHO_TABELA;
}

// =====================================================
// Funções do Encadeamento
// =====================================================

// Insere um valor no início da lista correspondente ao índice
void inserir_chaining(const char *valor) {
    int indice = funcao_hash(valor);

    Nodo *novo = malloc(sizeof(Nodo));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(novo->valor, valor);

    // O novo nó passa a apontar para o antigo início
    novo->proximo = tabela_chaining[indice];

    // A tabela passa a apontar para o novo nó
    tabela_chaining[indice] = novo;
}

// Procura um valor na lista ligada correspondente
Nodo *buscar_chaining(const char *valor) {
    int indice = funcao_hash(valor);

    Nodo *atual = tabela_chaining[indice];

    while (atual != NULL) {
        if (strcmp (atual->valor, valor) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

// Remove um valor da lista ligada
void remover_chaining(const char *valor) {
    int indice = funcao_hash(valor);

    Nodo *atual = tabela_chaining[indice];
    Nodo *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->valor, valor) == 0) {
            // O elemento está no início da lista
            if (anterior == NULL) {
                tabela_chaining[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);

            printf("'%s' removido (chaining).\n", valor);
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("'%s' nao encontrado para remocao (chaining).\n", valor);
}

// Exibe todas as posições e listas da tabela
void mostrar_chaining(void) {
    printf("\nTabela Hash (chaining):\n");

    for (int i =0; i < TAMANHO_TABELA; i++) {
        printf("[%d]: ", i);

        Nodo *atual = tabela_chaining[i];

        while (atual != NULL) {
            printf("%s -> ", atual->valor);
            atual = atual->proximo;
        }

        printf("NULL\n");
    }
}

// Libera todos os nós criados dinamicamente
void liberar_chaining(void) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo *atual = tabela_chaining[i];

        while (atual != NULL) {
            Nodo *temporario = atual;
            atual = atual->proximo;

            free(temporario);
        }

        tabela_chaining[i] = NULL;
    }
}

// =====================================================
// Funções da Sondagem Linear
// =====================================================

// Procura uma posição disponível a partir do índice orignal
void inserir_linear(const char *valor) {
    int indice = funcao_hash(valor);

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int posicao = (indice + i) % TAMANHO_TABELA;

        // Pode inserir em posição livre ou anteriormente removida
        if (
            tabela_linear[posicao].ocupado == 0 ||
            tabela_linear[posicao].ocupado == -1
        ) {
            strcpy(tabela_linear[posicao].valor, valor);
            tabela_linear[posicao].ocupado = 1;

            return;
        }
    }

    printf(
        "Tabela cheia. Nao foi possivel inserir '%s'.\n",
        valor
    );
}

// Procura um valor percorrendo as posições seguintes
int buscar_linear(const char *valor) {
    int indice = funcao_hash(valor);

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int posicao = (indice + i) % TAMANHO_TABELA;

        // Uma posição nunca utilizada encerra a busca
        if (tabela_linear[posicao].ocupado == 0) {
            return -1;
        }

        if (
            tabela_linear[posicao].ocupado == 1 &&
            strcmp(tabela_linear[posicao].valor, valor) == 0
        ) {
            return posicao;
        }
    }

    return -1;
}

// Marca uma posição como removida
void remover_linear(const char *valor) {
    int posicao = buscar_linear(valor);

    if (posicao == -1) {
        printf(
            "'%s' nao encontrado para remocao (linear).\n",
            valor
        );

        return;
    }

    tabela_linear[posicao].ocupado = -1;

    printf("'%s' removido (linear).\n", valor);
}

// Exibe todas as posições da tabela linear
void mostrar_linear(void) {
    printf("\nTabela Hash (Linear Probing):\n");

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("[%d]: ", i);

        if (tabela_linear[i].ocupado == 1) {
            printf("%s\n", tabela_linear[i].valor);
        } else if (tabela_linear[i].ocupado == -1) {
            printf("<removido>\n");
        } else {
            printf("<livre>\n");
        }
    }
}
