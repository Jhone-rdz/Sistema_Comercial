#include <stdio.h>
#include <string.h>
#include "sgc.h"

// faz um pedido de um produto
void Fazer_Pedido() {
    int numProdutos;
    Produto estoque[100]; // Ajuste conforme precisar

    if (!readProductsFromFile(estoque, &numProdutos)) {
        printf("Erro ao ler os produtos. Pedido não pode ser feito.\n");
        return;
    }

    Pedido novoPedido;
    printf("Digite o nome do produto: ");
    scanf("%s", novoPedido.nomeProduto);
    printf("Digite a quantidade desejada: ");
    scanf("%d", &novoPedido.quantidade);

    // Validação do pedido
    int produtoEncontrado = 0;
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(novoPedido.nomeProduto, estoque[i].nome) == 0) {
            produtoEncontrado = 1;
            if (novoPedido.quantidade <= 0 || novoPedido.quantidade > estoque[i].quantidade) {
                printf("Quantidade inválida. Pedido não pode ser feito.\n");
                return;
            }
        }
    }

    if (!produtoEncontrado) {
        printf("Produto não encontrado. Pedido não pode ser feito.\n");
        return;
    }

    // Atualizar o estoque após a validação do pedido
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(novoPedido.nomeProduto, estoque[i].nome) == 0) {
            estoque[i].quantidade -= novoPedido.quantidade;
        }
    }

    if (writeProductsToFile(estoque, numProdutos)) {
        // Salve a lista de produtos atualizada após a dedução do estoque
        // Aqui você pode adicionar o novo pedido à lista de pedidos
        int numPedidos;
        Pedido pedidos[100]; // Pode ajustar o tamanho conforme necessário

        if (readOrdersFromFile(pedidos, &numPedidos)) {
            // Adicione o novo pedido à lista
            pedidos[numPedidos] = novoPedido;
            numPedidos++;

            // Salve a lista atualizada de pedidos no arquivo
            if (writeOrdersToFile(pedidos, numPedidos)) {
                printf("Pedido realizado com sucesso!\n");
            } else {
                printf("Erro ao salvar o pedido.\n");
            }
        } else {
            printf("Erro ao ler os pedidos.\n");
        }
    } else {
        printf("Erro ao atualizar o estoque. Pedido não pode ser feito.\n");
    }
}

// Função para listar os produtos disponíveis no estoque
void Listar_Produto() {
    int numProdutos;
    Produto estoque[100]; // Pode ajustar o tamanho conforme necessário

    if (!readProductsFromFile(estoque, &numProdutos)) {
        printf("Erro ao ler os produtos.\n");
        return;
    }

    if (numProdutos > 0) {
        printf("Produtos disponíveis no estoque:\n");
        for (int i = 0; i < numProdutos; i++) {
            printf("Nome: %s", estoque[i].nome);
            printf("Preço: %.2f\n", estoque[i].preco);
            printf("Quantidade: %d\n", estoque[i].quantidade);
            printf("\n");
        }
    } else {
        printf("Nenhum produto disponível no estoque.\n");
    }
}

// Função para listar os pedidos feitos pelos usuários convencionais
void Listar_Pedidos() {
    int numPedidos;
    Pedido pedidos[100]; // Pode ajustar o tamanho conforme necessário

    if (!readOrdersFromFile(pedidos, &numPedidos)) {
        printf("Erro ao ler os pedidos.\n");
        return;
    }

    if (numPedidos > 0) {
        printf("Pedidos feitos pelos usuários convencionais:\n");
        for (int i = 0; i < numPedidos; i++) {
            printf("Nome do Produto: %s", pedidos[i].nomeProduto);
            printf("Quantidade: %d\n", pedidos[i].quantidade);
            printf("\n");
        }
    } else {
        printf("Nenhum pedido feito pelos usuários convencionais.\n");
    }
}
