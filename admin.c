#include <stdio.h>
#include <string.h>
#include "sgc.h"

// Declaração de variáveis para armazenar os produtos, usuários e pedidos
Produto estoque[100];  
Usuario usuarios[100]; 
Pedido pedidos[100];   
int numProdutos = 0;   
int numUsuarios = 0;   
int numPedidos = 0;    
// verifica a senha dos administradores
int Verificacao_Senha(char Senha_Admin[]) {
    char admin_Senha[] = "Admin";

    if (strcmp(Senha_Admin, admin_Senha) == 0) {
        return 1; // Verificação bem-sucedida
    }

    return 0; // Verificação falhou
}

// adiciona um novo produto ao estoque
void Adicionar_Produto() {

    if (!readProductsFromFile(estoque, &numProdutos)) {
        printf("Erro ao ler os produtos.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
            scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    // Ler os dados do novo produto
    Produto novoProduto;
    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto.nome);
    printf("Digite o preço do produto: ");
    scanf("%f", &novoProduto.preco);
    printf("Digite a quantidade disponível: ");
    scanf("%d", &novoProduto.quantidade);

    // Valida os dados do novo produto
    if (novoProduto.preco <= 0 || novoProduto.quantidade < 0) {
        printf("Dados do produto inválidos. O produto não foi adicionado.\n");
        return;
    }

    // Verifica se o produto já existe no estoque
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(novoProduto.nome, estoque[i].nome) == 0) {
            printf("Produto já existe no estoque. Atualizando informações.\n");
            estoque[i] = novoProduto; // Atualiza os detalhes do produto existente
            if (writeProductsToFile(estoque, numProdutos)) {
                printf("Produto atualizado com sucesso.\n");
            } else {
                printf("Erro ao atualizar o produto.\n");
            }
            return;
        }
    }

    // Adiciona o novo produto à lista de produtos
    if (numProdutos < 100) { // Verifica se há espaço na lista
        estoque[numProdutos] = novoProduto;
        numProdutos++;

        if (writeProductsToFile(estoque, numProdutos)) {
            printf("Produto adicionado com sucesso.\n");
        } else {
            printf("Erro ao adicionar o produto.\n");
        }
    } else {
        printf("Não é possível adicionar mais produtos. Limite de estoque atingido.\n");
    }
}

// lista os produtos disponíveis no estoque
void Listar_Produto() {

    if (!readProductsFromFile(estoque, &numProdutos)) {
        printf("Erro ao ler os produtos.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
    scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    if (numProdutos > 0) {
        printf("\n");
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

//  adiciona um novo usuário ao sistema
void Adicionar_Usuario() {
    
    if (!readUsersFromFile(usuarios, &numUsuarios)) {
        printf("Erro ao ler os usuários.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
    scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    // Ler os dados do novo usuário
    Usuario novoUsuario;
    printf("Digite o nome de usuário: ");
    scanf("%s", novoUsuario.nome);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);
    printf("Digite o nível de privilégio (1 para administrador, 0 para usuário convencional): ");
    scanf("%d", &novoUsuario.nivelPrivilegio);

    // Valida os dados do novo usuário
    if (novoUsuario.nivelPrivilegio != 0 && novoUsuario.nivelPrivilegio != 1) {
        printf("Nível de privilégio inválido. O usuário não foi adicionado.\n");
        return;
    }

    // Verifica se o nome de usuário já existe
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(novoUsuario.nome, usuarios[i].nome) == 0) {
            printf("Nome de usuário já existe. O usuário não foi adicionado.\n");
            return;
        }
    }

    // Adiciona o novo usuário à lista de usuários
    if (numUsuarios < 100) { // Verifica se há espaço na lista
        usuarios[numUsuarios] = novoUsuario;
        numUsuarios++;

        if (writeUsersToFile(usuarios, numUsuarios)) {
            printf("Usuário adicionado com sucesso.\n");
        } else {
            printf("Erro ao adicionar o usuário.\n");
        }
    } else {
        printf("Não é possível adicionar mais usuários. Limite de usuários atingido.\n");
    }
}

// exclui um usuário do sistema
void Deletar_Usuario() {
    if (!readUsersFromFile(usuarios, &numUsuarios)) {
        printf("Erro ao ler os usuários.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
    scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    char nomeUsuario[50];
    printf("Digite o nome de usuário a ser excluído: ");
    scanf("%s", nomeUsuario);

    int encontrado = 0;

    // Procura o usuário a ser excluído
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(nomeUsuario, usuarios[i].nome) == 0) {
            encontrado = 1;
            // Remove o usuário da lista
            for (int j = i; j < numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            numUsuarios--;

            // Salva a lista de usuários atualizada no arquivo
            if (writeUsersToFile(usuarios, numUsuarios)) {
                printf("Usuário excluído com sucesso.\n");
            } else {
                printf("Erro ao excluir o usuário.\n");
            }

            break; // Sai do loop assim que o usuário for encontrado e excluído
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado. Nenhum usuário foi excluído.\n");
    }
}

// lista os pedidos feitos pelos usuários
void Listar_Pedidos() {
    
     if (!readOrdersFromFile(pedidos, &numPedidos)) {
        printf("Erro ao ler os pedidos.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
    scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    if (numPedidos > 0) {
        printf("\n");
        printf("Pedidos feitos pelos usuários:\n");
        for (int i = 0; i < numPedidos; i++) {
            printf("Nome do Produto: %s", pedidos[i].nomeProduto);
            printf("Quantidade: %d\n", pedidos[i].quantidade);
            printf("\n");
        }
    } else {
        printf("Nenhum pedido feito pelos usuários.\n");
    }
}

// Cancela um pedido de produto
void Cancelar_Pedido() {
    if (!readOrdersFromFile(pedidos, &numPedidos)) {
        printf("Erro ao ler os pedidos.\n");
        return;
    }
    
    char Senha_Admin[50];
    printf("Digite a senha de administrador para continuar a ação: ");
    scanf("%s", Senha_Admin);

    if (Verificacao_Senha(Senha_Admin)) {
        printf("\n");
    }else{
        printf("Senha incorreta. Ação não autorizada.\n");
    }

    char nomeProduto[50];
    printf("Digite o nome do produto do pedido a ser cancelado: ");
    scanf("%s", nomeProduto);

    int quantidadeCancelada;
    printf("Digite a quantidade a ser cancelada: ");
    scanf("%d", &quantidadeCancelada);

    int encontrado = 0;

    // Procura o pedido a ser cancelado
    for (int i = 0; i < numPedidos; i++) {
        if (strcmp(nomeProduto, pedidos[i].nomeProduto) == 0) {
            encontrado = 1;
            if (quantidadeCancelada <= pedidos[i].quantidade) {
                // Atualiza o estoque
                for (int j = 0; j < numProdutos; j++) {
                    if (strcmp(nomeProduto, estoque[j].nome) == 0) {
                        estoque[j].quantidade += quantidadeCancelada;
                        break;
                    }
                }
                // Atualiza o pedido
                pedidos[i].quantidade -= quantidadeCancelada;
                if (pedidos[i].quantidade == 0) {
                    // Remove o pedido se a quantidade for 0
                    for (int j = i; j < numPedidos - 1; j++) {
                        pedidos[j] = pedidos[j + 1];
                    }
                    numPedidos--;
                }
                // Salva as alterações
                if (writeProductsToFile(estoque, numProdutos) && writeOrdersToFile(pedidos, numPedidos)) {
                    printf("Pedido cancelado com sucesso.\n");
                } else {
                    printf("Erro ao cancelar o pedido.\n");
                }
            } else {
                printf("Quantidade a ser cancelada maior do que a quantidade do pedido.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Pedido não encontrado. Nenhum pedido foi cancelado.\n");
    }
}


int readProductsFromFile(Produto estoque[], int *numProdutos) {
    FILE *estoqueFile = fopen("estoque.txt", "r");
    if (estoqueFile == NULL) {
        // lembrar de tratar de erros de abertura do arquivo
        return 0;
    }

    int i = 0;
    while (fscanf(estoqueFile, "%49[^,],%f,%d\n", estoque[i].nome, &estoque[i].preco, &estoque[i].quantidade) == 3) {
        i++;
    }
    *numProdutos = i;
    fclose(estoqueFile);
    return 1;
}

int writeProductsToFile(Produto estoque[], int numProdutos) {
    FILE *estoqueFile = fopen("estoque.txt", "w");
    if (estoqueFile == NULL) {
        // lembrar de tratar de erros de abertura do arquivo
        return 0;
    }

    for (int i = 0; i < numProdutos; i++) {
        fprintf(estoqueFile, "%s,%.2f,%d\n", estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }

    fclose(estoqueFile);
    return 1;
}

// Função para ler informações dos usuários a partir de um arquivo
int readUsersFromFile(Usuario usuarios[], int *numUsuarios) {
    FILE *usuariosFile = fopen("usuarios.txt", "r");
    if (usuariosFile == NULL) {
        // Trate erros de abertura do arquivo
        return 0;
    }

    int i = 0;
    while (fscanf(usuariosFile, "%49[^,],%49[^,],%d\n", usuarios[i].nome, usuarios[i].senha, &usuarios[i].nivelPrivilegio) == 3) {
        i++;
    }
    *numUsuarios = i;
    fclose(usuariosFile);
    return 1;
}

// Função para escrever informações dos usuários em um arquivo
int writeUsersToFile(Usuario usuarios[], int numUsuarios) {
    FILE *usuariosFile = fopen("usuarios.txt", "w");
    if (usuariosFile == NULL) {
        // lembrar de tratar de erros de abertura do arquivo
        return 0;
    }

    for (int i = 0; i < numUsuarios; i++) {
        fprintf(usuariosFile, "%s,%s,%d\n", usuarios[i].nome, usuarios[i].senha, usuarios[i].nivelPrivilegio);
    }

    fclose(usuariosFile);
    return 1;
}

// Função para ler informações dos pedidos a partir de um arquivo
int readOrdersFromFile(Pedido pedidos[], int *numPedidos) {
    FILE *pedidosFile = fopen("pedidos.txt", "r");
    if (pedidosFile == NULL) {
        // lembrar de tratar de erros de abertura do arquivo
        return 0;
    }

    int i = 0;
    while (fscanf(pedidosFile, "%49[^,],%d\n", pedidos[i].nomeProduto, &pedidos[i].quantidade) == 2) {
        i++;
    }
    *numPedidos = i;
    fclose(pedidosFile);
    return 1;
}

// Função para escrever informações dos pedidos em um arquivo
int writeOrdersToFile(Pedido pedidos[], int numPedidos) {
    FILE *pedidosFile = fopen("pedidos.txt", "w");
    if (pedidosFile == NULL) {
        // lembrar de tratar de erros de abertura do arquivo
        return 0;
    }

    for (int i = 0; i < numPedidos; i++) {
        fprintf(pedidosFile, "%s,%d\n", pedidos[i].nomeProduto, pedidos[i].quantidade);
    }

    fclose(pedidosFile);
    return 1;
}
