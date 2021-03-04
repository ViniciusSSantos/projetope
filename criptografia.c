#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *, char*);
void saveUser(char *);

void main(){
    //Aqui eh apenas um exemplo de quem for implementar a parte de cadastro do usuario. A funcao Encrypt so precisa receber usuario e senha
    char usuario[50], senha[50];

    printf("Usuário: ");
    gets(usuario);

    printf("Senha: ");
    gets(senha);

    encrypt(usuario, senha);


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