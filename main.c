#include <stdio.h>
#include <string.h>
#include "sgc.h"

int main() {
    int Tipo_Usuario;
    int Escolha_Usuario = 0;

    do {
        // Escolher entre entrar como usuário ou administrador ou fechar o programa
        printf("\n");
        printf("Bem-vindo ao Sistema de Gestão Comercial!\n");
        printf("Escolha o tipo de usuário:\n");
        printf("1. Administrador\n");
        printf("2. Usuário Convencional\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &Tipo_Usuario);
        printf("\n");

        if (Tipo_Usuario == 1) {
            char Senha_Admin[50];

            // Verificação do administrador
            printf("Digite a senha de administrador: ");
            scanf("%s", Senha_Admin);

            if (Verificacao_Senha(Senha_Admin)) {
                // Verificação bem-sucedida
                do {
                    // Menu para administradores
                    printf("\n");
                    printf("Menu de Administrador\n");
                    printf("1. Adicionar Novo Produto\n");
                    printf("2. Exibir Lista de Produtos\n");
                    printf("3. Adicionar Novo Usuário\n");
                    printf("4. Excluir Usuário\n");
                    printf("5. Exibir Lista de Pedidos\n");
                    printf("6. Cancelar Pedido\n");
                    printf("7. Sair\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &Escolha_Usuario);
                    printf("\n");

                    switch (Escolha_Usuario) {
                        case 1:
                            Adicionar_Produto();
                            break;
                        case 2:
                            Listar_Produto();
                            break;
                        case 3:
                            Adicionar_Usuario();
                            break;
                        case 4:
                            Deletar_Usuario();
                            break;
                        case 5:
                            Listar_Pedidos();
                            break;
                        case 6:
                            Cancelar_Pedido();
                            break;
                        case 7:
                            // Sair do loop do menu de administrador e ir para o principal
                            break;
                        default:
                            printf("Opção inválida!\n");
                            break;
                    }
                } while (Escolha_Usuario != 7);
            } else {
                printf("Senha incorreta!\n");
            }
        } else if (Tipo_Usuario == 2) {
            do {
                // Menu para usuários convencionais
                printf("\n");
                printf("Menu de Usuário Convencional\n");
                printf("1. Fazer um Pedido\n");
                printf("2. Exibir Lista de Produtos\n");
                printf("3. Exibir Lista de Pedidos\n");
                printf("4. Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &Escolha_Usuario);
                printf("\n");

                switch (Escolha_Usuario) {
                    case 1:
                        Fazer_Pedido();
                        break;
                    case 2:
                        Listar_Produto();
                        break;
                    case 3:
                        Listar_Pedidos();
                        break;
                    case 4:
                        // Sair do loop do menu de usuário convencional e ir para o principal
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
                }
            } while (Escolha_Usuario != 4);
        } else if (Tipo_Usuario == 3) {
            // Sair do programa
            printf("Saindo do programa. Obrigado!\n");
            break;
        } else {
            printf("Opção errada!\n");
        }
    } while (1);

    return 0;
}

