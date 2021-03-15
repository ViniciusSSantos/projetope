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

// void encrypt(char *, char *, int);
void encrypt(struct client *cliente, char *);
void decrypt(char *);
void login(char *, char *, int *);
void saveUser(char *);
void saveTransfer(int *);
void itoa(int, char *);
void reverse(char *);
void getContaDisponivel(char *);
void cadastraCliente(struct client *cliente);

void main(){
    srand(time(NULL)); //necessário para o rand()

    int id;
    printf("Bem vindo ao Banco XXXXX, pressione 1 para fazer login e 2 para criar uma nova conta: ");
    scanf("%d", &id);
    char usuarioDecrypt[50], senhaDecrypt[50];
    struct client cliente;
    int conta;

    switch(id){


        case 1:

            printf("Usuario: \n");
            scanf("%s", usuarioDecrypt);

            printf("Senha: \n");
            scanf("%s", senhaDecrypt);

            printf("Agência: ");
            scanf("%d", &conta);

            // encrypt(usuarioDecrypt, senhaDecrypt, conta);

            /*
            Aqui a variável usuarioDecrypt estará já encriptada, da mesma forma que estará salva no .txt
            Então acredito que aqui o ideal seja verificar, linha a linha, o .txt em busca de um match para validar o login do usuário
            */

            break;

        case 2:
            printf("Nome: ");
            scanf("%s", cliente.nome);

            printf("Senha: ");
            scanf("%s", cliente.senha);

            cadastraCliente(&cliente);

            printf("Sua conta é: %s, salve esse número, você precisará dele para acessar sua conta.\n", cliente.conta);

            break;

    }
}

// funcao para cadastrar um cliente
void cadastraCliente(struct client *cliente) {
    // busca numero da conta disponivel e atribuiu ao cliente
    getContaDisponivel(cliente->conta);

    // criptografa as informacoes do cliente
    char usuarCrypt[200];
    encrypt(cliente, usuarCrypt);

    saveUser(usuarCrypt);
}

// void encrypt(char *usuario, char *senha, int conta){

//     int i;
//     char str[20];

//     itoa(conta, str);

//     strcat(usuario, "-"); //Aqui esotu adicionando apenas esse traco para nao ocorrer o erro de termos dois usuarios diferentes mas com a mesma criptografia
//     strcat(usuario, senha);
//     strcat(usuario, "-");
//     strcat(usuario, str);

//     for(i=0; i < strlen(usuario); i++){
//         usuario[i] += 5;
//     }

// }

void encrypt(struct client *client, char *str){

    int i;
    char aux[200], saldo[10];

    itoa(client->saldo, saldo);


    strcpy(aux, client->nome);
    strcat(aux, "/");
    strcat(aux, client->senha);
    strcat(aux, "/");
    strcat(aux, saldo);


    for(i=0; i < strlen(aux); i++){
        aux[i] += 2;
    }

    strcpy(str, client->conta);
    strcat(str, "1");
    strcat(str, aux);

}

void decrypt(char *str){

    int i;

    for(i=5; i < strlen(str); i++){
        str[i] -= 2;
    }
}


void saveUser(char *str){
    FILE *fp;

    fp = fopen("./usuarios.txt", "a");
    fputs(str, fp);
    fputs("\n", fp);
    fclose(fp);
}

// busca a ultima conta que foi cadastrada e retorna o numero da proxima conta
void getContaDisponivel(char * novaConta) {
    // abre o arquivo de usuarios no modo leitura
    FILE *fp = fopen("./usuarios.txt", "r");

    // inicializa variaveis
    char* registro = NULL;
    size_t size = 0;
    char ultimaConta[5] = "00000";

    // percorre todas as linhas até chegar na ultima
    // while (getline(&registro, &size, fp) != EOF) {
    //     strncpy(ultimaConta, registro, 5);
    // }

    // converte a ultima conta para inteiro e soma 1
    int contaNumerico = atoi(ultimaConta) + 1;

    // copia o numero da conta para uma nova string
    sprintf(novaConta, "%d", contaNumerico);

    // desloca a string para deixar o numero da conta a direita
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
                if (novaConta[j] != 0 && novaConta[j + 1] == 0) {
                    char aux = novaConta[j];
                    novaConta[j] = novaConta[j + 1];
                    novaConta [j + 1] = aux;
            }
        }
    }

    // completa com zeros a esquerda
    for (int i = 0; i < 5; i++)
        if (novaConta[i] == 0)
            novaConta[i] = '0';

    // fecha arquivo de texto
    fclose(fp);
}


//Essas duas próximas funções servem pra transformar um int em uma string. Em javascrpit seria como um parseInt()
 void reverse(char *s)
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

 void itoa(int n, char *s)
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

