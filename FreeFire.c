#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// Estrutura que representa um item da mochila do jogador
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------------
// Funções que operam sobre a mochila do jogador
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// -----------------------------------------------------------
// Função principal
// -----------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do enter

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 2:
                removerItem(mochila, &total);
                listarItens(mochila, total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// -----------------------------------------------------------
// Função para cadastrar um novo item na mochila do jogador
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Cadastro de Item ---\n");
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove \n

    printf("Tipo do item (arma, munição, cura, etc): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// -----------------------------------------------------------
// Função para remover um item pelo nome
// -----------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, encontrado = -1;
    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem não encontrado!\n");
    } else {
        // desloca os itens para preencher o espaço vazio
        for (i = encontrado; i < *total - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*total)--;
        printf("\nItem removido com sucesso!\n");
    }
}

// -----------------------------------------------------------
// Função para listar todos os itens da mochila do jogador
// -----------------------------------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    printf("------------------------------------------------------------\n");
    printf("NOME\t\t| TIPO\t\t| QUANTIDADE\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-15s| %-10s | %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }

    printf("------------------------------------------------------------\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

// -----------------------------------------------------------
// Função de busca sequencial por nome
// -----------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}
