#ifndef SGC_H
#define SGC_H

#define ADMIN 1
#define USER 2

// representa produtos
typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Produto;

// representa usuários
typedef struct {
    char nome[50];
    char senha[50];
    int nivelPrivilegio;
} Usuario;

// representa pedidos
typedef struct {
    char nomeProduto[50];
    int quantidade;
} Pedido;

// Funções de Verificação
    int Verificacao_Senha(char Senha[]);
    int getTipo_Usuario(char Senha[]);

// Funções compartilhadas
    void Adicionar_Produto();
    void Listar_Produto();
    void Adicionar_Usuario();
    void Deletar_Usuario();
    void Listar_Pedidos();
    void Fazer_Pedido();
    void Cancelar_Pedido();
    
    
// Funções de leitura e gravação de dados em arquivos
    int readProductsFromFile(Produto estoque[], int *numProdutos);
    int writeProductsToFile(Produto estoque[], int numProdutos);
    int readUsersFromFile(Usuario usuarios[], int *numUsuarios);
    int writeUsersToFile(Usuario usuarios[], int numUsuarios);
    int readOrdersFromFile(Pedido pedidos[], int *numPedidos);
    int writeOrdersToFile(Pedido pedidos[], int numPedidos);

#endif
