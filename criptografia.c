#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void encrypt(char *, char *, int);
void login(char *, char *, int *);
void saveUser(char *);
void saveTransfer(int *);
void itoa(int, char *);
void reverse(char *);



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
            scanf("%s", usuarioDecrypt);

            printf("Senha: \n");
            scanf("%s", senhaDecrypt);

            printf("Agência: ");
            scanf("%d", &agencia);

            encrypt(usuarioDecrypt, senhaDecrypt, agencia);

            /*
            Aqui a variável usuarioDecrypt estará já encriptada, da mesma forma que estará salva no .txt
            Então acredito que aqui o ideal seja verificar, linha a linha, o .txt em busca de um match para validar o login do usuário
            */

            break;

        case 2:
            printf("Usuário: ");
            scanf("%s", usuarioDecrypt);

            printf("Senha: ");
            scanf("%s", senhaDecrypt);

            agencia = rand()%((9999+1)-1000) + 1000;

            printf("sua agência é: %d\n", agencia);

            //Como haverá número de agência, adicionei ele para fazer parte da encriptação do usuário e sua identificação posteriormente
            encrypt(usuarioDecrypt, senhaDecrypt, agencia);
            saveUser(usuarioDecrypt);

            break;

    }


}

void encrypt(char *usuario, char *senha, int agencia){

    int i;
    char str[20];

    itoa(agencia, str);

    strcat(usuario, "-"); //Aqui esotu adicionando apenas esse traco para nao ocorrer o erro de termos dois usuarios diferentes mas com a mesma criptografia
    strcat(usuario, senha);
    strcat(usuario, "-");
    strcat(usuario, str);

    for(i=0; i < strlen(usuario); i++){
        usuario[i] += 5;
    }

}


void saveUser(char *str){
    FILE *fp;

    fp = fopen("./usuarios.txt", "a");
    fputs(str, fp);
    fputs("\n", fp);
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

