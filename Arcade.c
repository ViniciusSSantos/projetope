#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<ctype.h>
#include <windows.h>
#include <process.h>

void vinteeum();


void main()
{
    printf("==========   Bem vindo ao Arcade do Juca   ==========");
    int arcade = 1;
    while (arcade)
    {
        int id;
        printf("\n==========          Menu inicial          ==========");
        printf("\n1 - Space Wars\n2 - 21\n3 - Jogo da Cobrinha\n0 - Sair do programa\n");
        scanf("%d", &id);
        switch (id)
        {
        case 1:
            spaceWarsGame();
            break;
        case 2:
            vinteeum();
            break;
        case 3:
            jogoCobra();
        case 0:
            arcade = 0;
            break;
        default:
            break;
        }
    }
}

// ===================== SPACE WARS =========================
#define LINHAS 30       // numero de linhas visiveis no jogo
#define COLUNAS 33      // numero de colunas visiveis no jogo (cada "espaco" possui 3 colunas)
#define SHOT_SPEED 10.0 // velocidade em linhas/segundo do tiro
#define FPS 15.0        // taxa de atualizacao visual do jogo
#define PLAYER 2        // constante que define um jogador
#define WALL 9          // constante que define uma parede
#define PLAYER_SHOT -1  // constante que define o tiro do jogador
#define ENEMY_SHOT 1    // constante que define o tiro do inimigo
#define EMPTY 0         // constante que define um espaco vazio
#define RIGHT 77        // constante que define a tecla seta direita
#define LEFT 75         // constante que define a tecla seta esquerda
#define SPACE 32        // constante que define a tecla seta espaco
#define BACKSPACE 8     // constante que define a tecla seta retorno

#define CLEAR_CONSOLE "cls"  // constante usada para limpar o console antes de cada atualizacao de tela

int** initGameBoard();                                     // funcao para inicializar a matriz de jogo
void updateGameBoard(int** gameBoard);                     // funcao para atualizar a janela de acordo com a matriz de jogo
void updateShotPosition(int** gameBoard);                  // funcao para atualizar a posicao dos tiros na matriz de jogo
void updatePlayer(int playerInput, int** gameBoard);       // funcao que atualiza a matriz de jogo com o input do jogador

int pY = LINHAS - 1, pX = COLUNAS / 3 / 2; // variaveis que definem o local do player

int spaceWarsGame()
{
    int** gameBoard = initGameBoard(); // inicializa matriz de jogo
    clock_t displayClock = clock();    // variavel auxiliar usada para atualizar a janela
    clock_t shotClock = clock();       // variavel auxiliar usada para atualizar a posicao dos tiro no jogo
    int game = 1;                      // variavel que indica que o jogo esta acontecendo

    // loop de jogo
    while (game)
    {
        // calcula quanto tempo passou desde a ultima atualizacao de tela
        double timeSinceLastScreenUpdate = (double)(clock() - displayClock) / CLOCKS_PER_SEC;

        // caso o tempo seja maior que o tempo de 1 frame ou seja um tempo negativo (para o caso quando o clock volte para '0')
        if (timeSinceLastScreenUpdate > 1 / FPS || timeSinceLastScreenUpdate < 0)
        {
            displayClock = clock();
            updateGameBoard(gameBoard);
        }

        // calcula quanto tempo passou desde a ultima atualizacao de posicao dos tiros na tela
        double timeSinceLastShotUpdate = (double)(clock() - shotClock) / CLOCKS_PER_SEC;

        // caso o tempo seja maior que o tempo de movimentacao do tiro
        if (timeSinceLastShotUpdate > 1 / SHOT_SPEED || timeSinceLastShotUpdate < 0)
        {
            shotClock = clock();
            updateShotPosition(gameBoard);
        }

        // caso o jogador tenha apertado uma tecla
        if (_kbhit()) {
            // busca input do jogador
            int playerInput = _getch();

            // se a tecla for backspace, sai do jogo
            if (playerInput == BACKSPACE)
                game = 0;
            else // atualiza a matriz de jogo
                updatePlayer(playerInput, gameBoard);
        }

    }
}

int** initGameBoard()
{
    int** matrix = malloc(LINHAS * sizeof(int*));

    for (size_t i = 0; i < LINHAS; i++)
    {
        matrix[i] = calloc(COLUNAS / 3, sizeof(int));
        matrix[i][0] = WALL;
        matrix[i][COLUNAS / 3 - 1] = WALL;
    }

    matrix[pY][pX] = PLAYER;
    return matrix;
}

void updateGameBoard(int** gameBoard)
{
    system(CLEAR_CONSOLE);
    for (size_t i = 0; i < LINHAS; i++)
    {
        for (size_t j = 0; j < COLUNAS; j = j + 3)
        {
            switch (gameBoard[i][j / 3])
            {
            case EMPTY:
                printf("   ");
                break;
            case PLAYER:
                printf("<^>");
                break;
            case PLAYER_SHOT:
                printf(" ^ ");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
}

void updateShotPosition(int** gameBoard)
{
    for (size_t i = 0; i < LINHAS; i++)
    {
        for (size_t j = 0; j < COLUNAS / 3; j++)
        {
            if (gameBoard[i][j] == PLAYER_SHOT)
            {
                gameBoard[i][j] = EMPTY;
                if (i != 0)
                    gameBoard[i - 1][j] = PLAYER_SHOT;
            }
        }
    }
}

void updatePlayer(int playerInput, int** gameBoard)
{

    switch (playerInput)
    {
    case LEFT:
        gameBoard[pY][pX] = EMPTY;

        if (pX > 1)
            pX--;

        gameBoard[pY][pX] = PLAYER;
        break;
    case RIGHT:
        gameBoard[pY][pX] = EMPTY;

        if (pX < COLUNAS / 3 - 2)
            pX++;

        gameBoard[pY][pX] = PLAYER;
        break;
    case SPACE:
        gameBoard[pY - 1][pX] = PLAYER_SHOT;
    default:
        break;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//Parte do Gustavo

struct Node {
    int value;
    struct Node *next;
};

struct Node* createNode(int value){
     struct Node *node = (struct Node*) malloc(sizeof(struct Node));
     node->value = value;

     return node;
};

void vinteeum(){
    srand(time(NULL));
    int numeroJogador = rand()%9 + 1;
    int numeroMesa = rand()%9 + 1;
    int opcao;
    struct Node *jogador[1];
    struct Node *mesa[1];

    printf("==========          Jogo do 21!          ==========\n\n");

    jogador[0] = createNode(numeroJogador);
    mesa[0] = createNode(numeroMesa);

    struct Node *nodeJogador = jogador[0];
    struct Node *nodeMesa = mesa[0];

    printf("Mão da mesa: %d\n\n",numeroMesa);
    printf("Sua mão: %d\n\n",numeroJogador);

    while(opcao != 2){
        printf("Selecione a opção que deseja:\n(1)- Comprar mais uma carta\n(2)- Sair\n");
        printf("\n");
        scanf("%d", &opcao);

        if(opcao == 1){
            int totalMesa1=0;
            struct Node *nodePercorreMesa1 = mesa[0];

            while(nodePercorreMesa1){
                totalMesa1 += nodePercorreMesa1->value;
                nodePercorreMesa1 = nodePercorreMesa1->next;
            }

            if(totalMesa1 <18){
                int totalMesa2=0;
                struct Node *nodePercorreMesa2 = mesa[0];
                int numeroMesa = rand()%9 + 1;


                while(nodePercorreMesa2){
                    if(nodePercorreMesa2->next == NULL){
                        nodePercorreMesa2 -> next = createNode(numeroMesa);
                        break;
                    }
                    nodePercorreMesa2 = nodePercorreMesa2->next;
                }
                printf("===================================================\n\n");
                printf("Mão da mesa: ");
                struct Node *nodePercorreMesa3 = mesa[0];
                while(nodePercorreMesa3){
                    printf("%d ", nodePercorreMesa3->value);
                    totalMesa2 += nodePercorreMesa3->value;
                    nodePercorreMesa3 = nodePercorreMesa3->next;
                }
                printf("\nTotal da Mesa: %d\n", totalMesa2);
                printf("\n");
                printf("\n");
                if(totalMesa2 >= 21){
                    break;
                }

            }else{
                printf("===================================================\n\n");
                printf("Mão da mesa: ");
                int totalMesa2=0;
                struct Node *nodePercorreMesa3 = mesa[0];
                while(nodePercorreMesa3){
                    printf("%d ", nodePercorreMesa3->value);
                    totalMesa2 += nodePercorreMesa3->value;
                    nodePercorreMesa3 = nodePercorreMesa3->next;
                }
                printf("\nTotal da Mesa: %d\n", totalMesa2);
                printf("\n");
                printf("\n");
            }
            int numeroJogador = rand()%9 + 1;
            struct Node *nodePercorreJogador = jogador[0];

            while(nodePercorreJogador){
                if(nodePercorreJogador->next == NULL){
                    nodePercorreJogador -> next = createNode(numeroJogador);
                    break;
                }
                nodePercorreJogador = nodePercorreJogador->next;
            }
            printf("Sua mão: ");
            int total=0;
            struct Node *nodePercorreJogador2 = jogador[0];
            while(nodePercorreJogador2){
                printf("%d ", nodePercorreJogador2->value);
                total += nodePercorreJogador2->value;
                nodePercorreJogador2 = nodePercorreJogador2->next;
            }
            printf("\nTotal sua mão: %d\n", total);
            printf("\n");
            printf("\n");
            printf("===================================================\n\n");
            if(total>=21){
                break;
            }
        }

    }

    int mesaValidacao=0;
    struct Node *nodePercorreMesaValidacao = mesa[0];

    while(nodePercorreMesaValidacao){
        mesaValidacao += nodePercorreMesaValidacao->value;
        nodePercorreMesaValidacao = nodePercorreMesaValidacao->next;
    }

    while(mesaValidacao <=16){
        int totalMesa4=0;
        struct Node *nodePercorreMesa4 = mesa[0];
        int numeroMesa4 = rand()%9 + 1;


        while(nodePercorreMesa4){
            if(nodePercorreMesa4->next == NULL){
                nodePercorreMesa4 -> next = createNode(numeroMesa4);
                break;
            }
            nodePercorreMesa4 = nodePercorreMesa4->next;
        }
        printf("Mão da mesa: ");
        struct Node *nodePercorreMesa5 = mesa[0];
        while(nodePercorreMesa5){
            printf("%d ", nodePercorreMesa5->value);
            totalMesa4 += nodePercorreMesa5->value;
            nodePercorreMesa5 = nodePercorreMesa5->next;
        }
        printf("\nTotal da Mesa: %d\n", totalMesa4);
        printf("\n");
        printf("\n");
        mesaValidacao = totalMesa4;
    }

    int mesaFinal=0;
    struct Node *nodePercorreMesaFinal = mesa[0];

    while(nodePercorreMesaFinal){
        mesaFinal += nodePercorreMesaFinal->value;
        nodePercorreMesaFinal = nodePercorreMesaFinal->next;
    }

    int jogadorFinal=0;
    struct Node *nodePercorreJogadorFinal = jogador[0];

    while(nodePercorreJogadorFinal){
        jogadorFinal += nodePercorreJogadorFinal->value;
        nodePercorreJogadorFinal = nodePercorreJogadorFinal->next;
    }
    printf("===================================================\n\n");

    if(mesaFinal > 21){
        printf("Você Ganhou!!\n\n");
    } else if(jogadorFinal>21){
        printf("Você perdeu!!\n\n");
    }else{
        if(mesaFinal > jogadorFinal){
        printf("Você Perdeu!!\n\n");
        } else if(mesaFinal < jogadorFinal){
            printf("Você Ganhou!!\n\n");
        }else{
            printf("Empatou!!\n\n");
        }
    }
    printf("===================================================\n\n");

}


//------------------------------------------------------------------------------------------------------------
// Parte do Vinicius


#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length; // tamanho inicial da cobra
int bend_no; //posição da cauda onde acontece a dobra
int len; // tamanho da cauda ganha pela cobra durante o jogo
char key; // entrada do teclado
int vidas; // número de vidas inicial

int jogoCobra();//inicia o jogo
void Print(); //Printa todas informações iniciais
void load(); // carrega o jogo
void Delay(long double); // Emula um delay
void Move(); // Permite a movimentação da cobra
void Comida(); // Gera aleatóriamente na tela um asterisco que representa a comida
int Ponti(); // retorna a pontuação do jogador
void gotoxy(int x, int y); // Funções padrões de que permitem inserir algo em qualquer lugar da tela *precisam ser declaradas no Code:blocks*
void GotoXY(int x,int y); // Funções padrões de que permitem inserir algo em qualquer lugar da tela *precisam ser declaradas no Code:blocks*
void Bend(); // Permite que a cauda da cobra se dobre
void Borda(); // Gera os limites do jogo
void Baixo(); // Permite a movimentação para baixo
void Esq(); // Permite a movimentação para esquerda
void Cima(); // Permite a movimentação para cima
void Dir(); // Permite a movimentação para direita
void Sair(); // checa se os critérios para que o jogador perca foram atingidos

struct coord{
    int x;
    int y;
    int direcao;
};
//

// gera o struct que armazena as coordenadas da cabeça, onde a cauda ira se dobrar, comida e a cauda
struct coord cabeca, bend[500],comida,cauda[30];

int jogoCobra(){

    Print();

    system("cls");

    load();

    length=5;

    cabeca.x=25;

    cabeca.y=20;

    cabeca.direcao=DOWN;

    Borda();

    Comida();

    vidas=5;

    bend[0]=cabeca;

    Move();
    return 0;


}


void Print(){

    system("cls");
    printf("\n Bem Vindo ao jogo da cobrinha, aperte qualquer botao pra começar a jogar!");
    if(getch()==27)
        exit(0);
}

void load(){

    int r,q;
    gotoxy(36,14);
    printf("CARREGANDO...");
    gotoxy(30,15);
    for(r=1; r<=20; r++){
        for(q=0; q<=100000000; q++);
        printf("%c",177);
    }
    getch();
}

void Delay(long double k){
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}

void Move(){
    int a,i;
    do{
        Comida();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++){

            cauda[i].x=0;

            cauda[i].y=0;

            if(i==length)

                break;
        }

        Delay(length);

        Borda();

        if(cabeca.direcao==RIGHT)

            Dir();

        else if(cabeca.direcao==LEFT)

            Esq();

        else if(cabeca.direcao==DOWN)

            Baixo();

        else if(cabeca.direcao==UP)

            Cima();

        Sair();

    }
    while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&cabeca.direcao!=LEFT&&cabeca.direcao!=RIGHT)||(key==LEFT&&cabeca.direcao!=RIGHT&&cabeca.direcao!=LEFT)||(key==UP&&cabeca.direcao!=DOWN&&cabeca.direcao!=UP)||(key==DOWN&&cabeca.direcao!=UP&&cabeca.direcao!=DOWN))

    {

        bend_no++;

        bend[bend_no]=cabeca;

        cabeca.direcao=key;

        if(key==UP)

            cabeca.y--;

        if(key==DOWN)

            cabeca.y++;

        if(key==RIGHT)

            cabeca.x++;

        if(key==LEFT)

            cabeca.x--;

        Move();

    }

    else if(key==27){

        system("cls");

        exit(0);

    }

    else{
        printf("\a");
        Move();
    }
}

void Comida(){

    if(cabeca.x==comida.x&&cabeca.y==comida.y){
        length++;
        time_t a;
        a=time(0);
        srand(a);
        comida.x=rand()%70;
        if(comida.x<=10)
            comida.x+=11;
        comida.y=rand()%30;
        if(comida.y<=10)

            comida.y+=11;
    }

    else if(comida.x==0){
        comida.x=rand()%70;
        if(comida.x<=10)
            comida.x+=11;
        comida.y=rand()%30;
        if(comida.y<=10)
            comida.y+=11;
    }
}

int Score(){

    int score;
    GotoXY(20,8);
    score=length-5;
    printf("Pontuação: %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Vidas: %d",vidas);
    return score;
}


void gotoxy(int x, int y){

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y){
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}


void Bend(){

    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--){
        if(bend[i].x==bend[i-1].x){

            diff=bend[i].y-bend[i-1].y;

            if(diff<0)
                for(j=1; j<=(-diff); j++){
                    cauda[len].x=bend[i].x;
                    cauda[len].y=bend[i].y+j;
                    GotoXY(cauda[len].x,cauda[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++){
                    cauda[len].x=bend[i].x;
                    cauda[len].y=bend[i].y-j;
                    GotoXY(cauda[len].x,cauda[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }


        else if(bend[i].y==bend[i-1].y){
            diff=bend[i].x-bend[i-1].x;

            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++){
                    cauda[len].x=bend[i].x+j;
                    cauda[len].y=bend[i].y;
                    GotoXY(cauda[len].x,cauda[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }

            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++){
                    cauda[len].x=bend[i].x-j;
                    cauda[len].y=bend[i].y;
                    GotoXY(cauda[len].x,cauda[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}

void Borda(){

    system("cls");
    int i;
    GotoXY(comida.x,comida.y);
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}

void Baixo(){
    int i;
    for(i=0; i<=(cabeca.y-bend[bend_no].y)&&len<length; i++){
        GotoXY(cabeca.x,cabeca.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        cauda[len].x=cabeca.x;
        cauda[len].y=cabeca.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        cabeca.y++;
}

void Esq()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-cabeca.x)&&len<length; i++)
    {
        GotoXY((cabeca.x+i),cabeca.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        cauda[len].x=cabeca.x+i;
        cauda[len].y=cabeca.y;
        len++;
    }
    Bend();
    if(!kbhit())
        cabeca.x--;

}
void Dir()
{
    int i;
    for(i=0; i<=(cabeca.x-bend[bend_no].x)&&len<length; i++)
    {
        cauda[len].x=cabeca.x-i;
        cauda[len].y=cabeca.y;
        GotoXY(cauda[len].x,cauda[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }

        len++;
    }
    Bend();
    if(!kbhit())
        cabeca.x++;
}


void Cima()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-cabeca.y)&&len<length; i++)
    {
        GotoXY(cabeca.x,cabeca.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        cauda[len].x=cabeca.x;
        cauda[len].y=cabeca.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        cabeca.y--;
}


void Sair(){
    int i,check=0;
    for(i=4; i<length; i++){
        if(cauda[0].x==cauda[i].x&&cauda[0].y==cauda[i].y){
            check++;
        }
        if(i==length||check!=0)
            break;
    }
    if(cabeca.x<=10||cabeca.x>=70||cabeca.y<=10||cabeca.y>=30||check!=0){
        vidas--;
        if(vidas>=0){
            cabeca.x=25;
            cabeca.y=20;
            bend_no=0;
            cabeca.direcao=DOWN;
            Move();
        }
        else{
            system("cls");
            printf("Voce Perdeu! Pressione qualquer tecla para sair do jogo");
            exit(0);
        }
    }
}
