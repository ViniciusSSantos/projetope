#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void encrypt(char *, char *);
void login(char *, char *, int *);
void saveUser(char *);
void saveTransfer(int *);

void main(){
    //Aqui eh apenas um exemplo de quem for implementar a parte de cadastro do usuario. A funcao Encrypt so precisa receber usuario e senha
    //Esse struct é usado para organizar o .txt e ajudar na hora de fazer o parse e validação de login e armazenamento de saques, depositos etc

    srand(time(NULL)); //necessário para o rand()

    struct client{
    char usuario[50];
    char senha[50];
    int agencia;
    float saldo;
    float saque;
    float deposito;
    float transferencias[5];
    };

    int id;
    printf("Bem vindo ao Banco XXXXX, pressione 1 para fazer login e 2 para criar uma nova conta: ");
    scanf("%d", &id);
    char usuarioDecrypt[50], senhaDecrypt[50];
    int agencia;

    switch(id){


    case 1:
        printf("Usuario: \n");
        gets(usuarioDecrypt);

        printf("Senha: \n");
        gets(senhaDecrypt);

        printf("Agência: ");
        scanf("%d", &agencia);

        break;

    case 2:
        printf("Usuário: ");
        gets(usuarioDecrypt);

        printf("Senha: ");
        gets(senhaDecrypt);

        agencia = rand()%((9999+1)-1000) + 1000;

        printf("sua agência é: %d", agencia);
        break;

    }


}

void encrypt(char *usuario, char *senha){

    int i;
    strcat(usuario, "-"); //Aqui esotu adicionando apenas esse traco para nao ocorrer o erro de termos dois usuarios diferentes mas com a mesma criptografia
    strcat(usuario, senha);
    for(i=0; i < strlen(usuario); i++){
        usuario[i] += 5;
    }

    saveUser(usuario);
}

void saveUser(char *str){
    FILE *fp;

    fp = fopen("./usuarios.txt", "a");
    fputs(str, fp);
    fputs("\n", fp);
    fclose(fp);
}

