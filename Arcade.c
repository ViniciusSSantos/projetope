#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void vinteeum();

void main()
{
    printf("==========   Bem vindo ao Arcade do Juca   ==========");
    int arcade = 1;
    while (arcade)
    {
        int id;
        printf("\n==========          Menu inicial          ==========");
        printf("\n1 - Space Wars\n2 - 21\n\n0 - Sair do programa\n");
        scanf("%d", &id);
        switch (id)
        {
        case 1:
            spaceWarsGame();
            break;
        case 2:
            vinteeum();
            break;
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