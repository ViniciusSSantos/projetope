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

int isNew = 0;
int operacao;

struct client bancoDados[1000];

void encrypt(struct client *client);
void decrypt(struct client *client);
void saveClient(struct client cliente);
float saque(float *saldo);
float deposito(float *saldo);
int transfer(struct client *cliente1, char *nome, int value);
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
                        printf("Olá %s",cliente.nome);
                        

                        if(isNew == 0){

                            // Primeiro Depósito
                            printf("Realize seu primeiro depósito para sua conta:");
                            scanf("%f", &cliente.saldo);
                            // Não é mais novo
                            isNew = 1;
                            // Operações
                            printf("\nO que quer fazer hoje?\nSaldo em Conta: R$%.2f\n", cliente.saldo);
                        }
                        else{
                            printf("\nDeseja fazer algo mais?\nSaldo em Conta: R$%.2f\n", cliente.saldo);
                            
                        }

                        printf("Selecione uma das opções:");
                        printf("\n1 - Saque\n2 - Depósito\n3 - Cartão Virtual\n4 - Transferência\n5 - Sair\n");
                        scanf("%d", &operacao);

                      switch(operacao){

                        case 1:
                        cliente.saldo = saque(&cliente.saldo);
                        printf("Saldo após o saque: %.2f", cliente.saldo);
                        break;

                        case 2:
                        cliente.saldo = deposito(&cliente.saldo);
                        printf("Saldo após o depósito: %.2f", cliente.saldo);
                        break;

                        case 3:
                        srand(time(0));

                        printf("Numero do Cartao: ");

                        for(int i = 0; i < 4; i++)
                        {
                            printf("%i ", 1000 + rand() %9000);
                        }
                        printf("\n");

                        printf("Codigo de Seguranca: ");

                        for(int i = 0; i < 1; i++)
                        {
                            printf("%i ", 100 + rand() %1000);
                        }

                        printf("\n");

                        time_t data;
                        data = time(NULL);
                        struct tm tm = *localtime(&data);
                        printf("Data de validade: %d/%d \n", tm.tm_mon + 1, tm.tm_year + 1900 + 10);   
                        break;

                        case 4:

                            printf("digite o nome do usuário que será o recipiente da sua transferência\n");
                            char nome;
                            scanf("%s",&nome);
                            printf("Qual é o valor que deseja transferir ?\n");
                            int din;
                            scanf("%d", &din);

                            transfer(&cliente, &nome, din);
                            break;
                        case 5:
                            logado = 0;
                            break;
                        default:
                            printf("\nFavor inserir uma opção válida.\n");

                      }
                        printf("\nPressione 'ENTER' para voltar ao menu.\n");
                        getchar();getchar();
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

float saque(float *saldo){

  float saque = 0;

  printf("Insira a quantia que quer sacar:");
  scanf("%f", &saque);


  while(*saldo - saque < 0){
    printf("Saque inválido, é necessário ter saldo em conta. Digite novamente:");
    scanf("%f", &saque);
  }

  return *saldo -= saque;

}

float deposito(float *saldo){

  float deposito = 0;

  printf("Insira a quantia para depositar:");
  scanf("%f", &deposito);

  return *saldo += deposito;


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

int transfer(struct client *cliente1, char *nome, int value){


     if(cliente1->saldo < value){
        printf("Saldo insuficiente para transferência.\n");
        return 0;

    }


    struct client *cliente2 = malloc(sizeof(struct client));

      for (int i = 0; i < 1000; i++) {
        if (strcmp(bancoDados[i].nome, nome) == 0) {
            cliente2 = &bancoDados[i];
            break;
        }
    }


    (*cliente1).saldo -= value;
    (*cliente2).saldo += value;
    printf("transferência efetuada com sucesso");
    printf("cliente 1: %f cliente 2: %f", cliente1->saldo, cliente2->saldo);


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
