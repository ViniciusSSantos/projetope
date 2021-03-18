#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Esse struct é usado para organizar o .txt e ajudar na hora de fazer o parse e validação de login e armazenamento de saques, depositos etc
struct transferencias {
    struct tm dataHora;
    float valor;
};

struct client{
    char nome[50];
    char senha[50];
    char conta[5];
    float saldo;
    struct transferencias transferencias[50];
};

struct client bancoDados[1000];

void encrypt(struct client *client);
void decrypt(struct client *client);
void saveClient(struct client cliente);
struct client getClientByConta(char *conta);
char* getContaDisponivel();

void main(){
    printf("==========   Bem vindo ao Banco Digital   ==========\n");
    int bancoDigital = 1;
    while(bancoDigital) {
        int id;
        printf("\n==========          Menu inicial          ==========\n");
        printf("\n1 - Login\n2 - Cadastrar nova conta\n3 - Sair do programa\n");
        scanf("%d", &id);
        getchar(); // remove \n apos input
        
        switch(id){
            case 1:
                printf("\n==========             Login              ==========\n");
                printf("Insira seu número de conta: ");
                struct client cliente;
                scanf("%s", cliente.conta);
                getchar(); // remove \n apos input
              
                char senha[50];
                printf("Insira sua senha: ");
                fgets(senha, 50, stdin);

                cliente = getClientByConta(cliente.conta);
                decrypt(&cliente);

                if(strcmp(senha, cliente.senha) == 0){
                    // menu depois de ter logado
                    int logado = 1;
                    while(logado) { 
                        printf("\n==========           Menu conta           ==========\n");
                        printf("Olá %s\nO que deseja fazer hoje?\n",cliente.nome);
                        printf("\n1 - Ver saldo\n2 - Depósito\n3 - Saque\n4 - Transferência\n5 - Sair\n");
                        
                        int opcao;
                        scanf("%d", &opcao);
                        getchar(); // remove \n apos input
                        switch(opcao){
                            case 5:
                                logado = 0;
                                break;
                            default:
                                printf("\nFavor inserir uma opção válida.\n");
                        }
                    }
                
                } else
                    printf("Senha incorreta ou conta inexistente.\n");

                break;

            case 2:
                printf("\n==========    Cadastramento de contas     ==========\n");
                printf("Qual é seu nome? ");
                struct client novoCliente;
                fgets(novoCliente.nome, 50, stdin);

                printf("Insira uma senha para acessar sua conta (máximo de 50 caracteres): ");
                fgets(novoCliente.senha, 50, stdin);

                encrypt(&novoCliente);
                strncpy(novoCliente.conta, getContaDisponivel(novoCliente.conta), 5);
                struct client cliente2 = getClientByConta(novoCliente.conta); // se eu tirar essa linha, comeca a dar ruim na hora de gravar, nao sei pq
                saveClient(novoCliente);
                
                printf("\nSeu número de conta é: %s, salve esse número, você precisará dele para acessar sua conta.\n", novoCliente.conta);
                
                printf("\nPressione 'ENTER' para voltar ao menu inicial.\n");
                getchar();
                break;
            case 3:
                bancoDigital = 0;
                break;
            default:
                printf("\nFavor inserir uma opção válida.\n");
        }
    }
}

void encrypt(struct client *client) {
    for(int i = 0; i < strlen(client->nome); i++){
        (*client).nome[i] += 2;
    }

    for(int i = 0; i < strlen(client->senha); i++){
        (*client).senha[i] += 2;
    }
}

void decrypt(struct client *client){

    for(int i = 0; i < strlen(client->nome); i++){
        (*client).nome[i] -= 2;
    }

    for(int i = 0; i < strlen(client->senha); i++){
        (*client).senha[i] -= 2;
    }
}


void saveClient(struct client cliente) {
    for (int i = 0; i < 1000; i++) {
        if (strcmp(bancoDados[i].conta, cliente.conta) == 0
        || strcmp(bancoDados[i].conta, "") == 0) {
            bancoDados[i] = cliente;
            break;
        }
    }
}

struct client getClientByConta(char *conta) {
    struct client *cliente = malloc(sizeof(struct client));

    for (int i = 0; i < 1000; i++) {
        if (strcmp(bancoDados[i].conta, conta) == 0) {
            cliente = &bancoDados[i];
            break;
        }
    }

    return *cliente;
}

// busca a ultima conta que foi cadastrada e retorna o numero da proxima conta
char* getContaDisponivel() {

    // inicializa variaveis
    char *ultimaConta = malloc(5);
    strncpy(ultimaConta, "00000", 5);

    // percorre todas as linhas até chegar na ultima
    for (int i = 0; i < 1000; i++) {
        if (strlen(bancoDados[i].conta) > 0 )
            strncpy(ultimaConta, bancoDados[i].conta, 5);
        else 
            break;
    }

    // converte a ultima conta para inteiro e soma 1
    int contaNumerico = atoi(ultimaConta) + 1;

    char conta[5];
    // copia o numero da conta para uma nova string
    sprintf(conta, "%d", contaNumerico);
    
    for (int i = 4; i >= 0; i--) {
        if (conta[4 - i])
            ultimaConta[i] = conta[4 - i];
        else
            break;
    }
        

    return ultimaConta;
}
