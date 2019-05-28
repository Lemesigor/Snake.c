#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h> /// INCLUIR

/// Definiçoes de movimentação da cobra
#define LIMITE_COBRA 100
#define CIMA 80
#define BAIXO 72
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define CABECA 0
/// Definições de mapa
#define LINHAS 24
#define COLUNAS 81
#define CORRECAOX 1
#define CORRECAOY 2

///Definições opções
#define VEL_MAX 50
#define VEL_MIN 200

///Definições de items
#define COMIDA 'C'
#define FASTER 'F'
#define SLOWER 'S'
#define SKIP   'K'
typedef struct {
    int x;
    int y;
} COORDENADA;

typedef struct {
    COORDENADA posicoes[LIMITE_COBRA];
    char dir;
    int tam_cobra;
} COBRA;

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void muda_direcao (COBRA *snake)
{
  switch (snake->dir)
              {
                case 'b': snake->posicoes[CABECA].y--;
                        break;

                case 'c': snake->posicoes[CABECA].y++;
                        break;

                case 'd': snake->posicoes[CABECA].x ++;
                        break;

                case 'e': snake->posicoes[CABECA].x --;
                        break;
              }
}

void nova_direcao (COBRA *snake, char seta)
{
  switch (seta) // SWITCH QUE VAI RETORNA A PRÓXIMA COORDENADA DA COBRA
            {
                    case BAIXO: if (snake->dir != 'c')
                                snake->dir = 'b';
                                break;

                    case CIMA: if (snake->dir != 'b')
                                snake->dir = 'c';
                                break;

                    case DIREITA: if (snake->dir != 'e')
                                  snake->dir = 'd';
                                  break;

                    case ESQUERDA: if (snake->dir != 'd')
                                    snake->dir = 'e';
                                    break;

            }
}



void desenha_snake (COORDENADA cabeca_cobra)
{
            textcolor (RED);
            textbackground(GREEN);
            putchxy(cabeca_cobra.x,cabeca_cobra.y, 'o'); // IMPRIME A COBRA
            textcolor(WHITE);
            textbackground(BLACK);
}

void desenha_interface (int vel, int cen, int pontu, int tam_cobra)
{
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Pontuacao:%d \t Nivel:%d \t Tamanho:%d \t Velocidade:%d", pontu, cen, tam_cobra, vel);
    textcolor(BLACK);
}


void desenha_cenario ()
{
    int lin, col, cen;
    char cenario1 [24][81] = {"1111111111111111111111111111111111111111111111111111111111111111111111111111111",
                              "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                              "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1111111111111111111111111111111111111111111111111111111111111111111111111111111"}, cenario2[0][0], cenario3[0][0];



        cen =1;

            switch (cen)
            {
                case 1: for (lin = 0; lin < 25; lin++)
                        {
                            for (col = 0; col < 81; col++)
                                if (cenario1[lin][col] == '1')
                                {
                                    textcolor (BLACK);
                                    textbackground(LIGHTBLUE);
                                   putchxy(col + CORRECAOX, lin + CORRECAOY ,'x');
                                }
                        }
                        textcolor(WHITE);
                        textbackground(BLACK);
                        break;

                case 2: for (lin = 0; lin < 25; lin++)
                        {
                            for (col = 0; col < 81; col++)
                                if (cenario2[lin][col] == '1')
                                   putchxy(col + CORRECAOX, lin + CORRECAOY ,'x');
                        }
                        break;

                case 3: for (lin = 0; lin < 25; lin++)
                        {
                            for (col = 0; col < 81; col++)
                                if (cenario3[lin][col] == '1')
                                   putchxy(col + CORRECAOX, lin + CORRECAOY ,'x');
                        }
                        break;
            }

                    }


char escolhe_item ()
{
    int item_sorteado;

        srand(time(0));


       item_sorteado = (rand() % ((100 - 1) + 1) + 1);

       if (item_sorteado <= 67)
        {
            textcolor(LIGHTRED);
            return COMIDA; ///comida
        }

       if (item_sorteado > 67 && item_sorteado <= 87)
        {
            textcolor(LIGHTGREEN);
            return FASTER; ///faster
        }

       if (item_sorteado > 87 && item_sorteado <= 97)
        {
            textcolor(LIGHTMAGENTA);
            return SLOWER; ///slower
        }

       if(item_sorteado > 97 && item_sorteado <= 100)
       {
            textcolor(LIGHTCYAN);
            return SKIP; /// skip
       }


}


void gera_item (char cenario[][COLUNAS])
{
   int eixox, eixoy, testa_obstaculo;
   char item;
        testa_obstaculo = 1;

        srand(time(0));


        while (testa_obstaculo)
        {
            eixoy = rand() % 24;
            eixox = rand() % 81;
            if (cenario[eixoy][eixox] == '0')
                testa_obstaculo = 0;
        }
        item = escolhe_item(); /// Gera um item

        putchxy (eixox + CORRECAOX, eixoy + CORRECAOY,item); /// desenha o item na tela
        textcolor (WHITE);

        cenario[eixoy][eixox] = item;  /// Coloca o item no arranjo para testar se cabeça da cobra come ou não o item

}

int colidiu (int *pontu, COBRA *snake, int *vel, int *sair, char colisao)
{


    switch(colisao)
    {
        case '1': *sair = 0;
                   //printf(" perdeu");
                   return 0;
                   break;

        case COMIDA: *pontu = *pontu + 2;
                  snake->tam_cobra++;
                   //printf(" comi");
                   return 1;
                   break;

        case SLOWER: *pontu = *pontu + 1;
                  if (*vel < VEL_MIN )
                      *vel = *vel + 50; /// slower, diminui velocidade
                   //printf(" v-");
                   return 1;
                   break;

        case FASTER: *pontu = *pontu + 3;
                  if (*vel > VEL_MAX)
                      *vel = *vel - 50; /// faster, aumenta velocidade
                   //printf(" v+");
                   return 1;
                   break;

        case SKIP: *pontu = *pontu + 40;
                  *sair = 2; /// faz pular o nível
                   //printf(" n");
                   return 1;
                   break;

        default: return 0;
                 //printf("nada");
                 break;

    }
}

///movimenta_snake (COBRA snake, char cenario)
int main()
{
    char cenario1 [25][81] = {"1111111111111111111111111111111111111111111111111111111111111111111111111111111",
                              "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                              "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1000000000000000000000000000000000000000000000000000000000000000000000000000001",
                            "1111111111111111111111111111111111111111111111111111111111111111111111111111111"};
    char seta;
    COBRA snake;
    int x, i;
    int velocidade = 100; ///VAI VIR POR PONTEIRO
    int sair = 1, pontu = 0; /// CONDIÇAO DE QUANDO A COBRA BATE EM UMA PAREDE
    char bateu; /// char onde ficará armazenado a colisão ou não da cobra

        /// posição inicial onde a cobra vai nascer
        snake.posicoes[0].x = 3;
        snake.posicoes[0].y = 13;

        snake.posicoes[1].x = 2;
        snake.posicoes[1].y = 13;

        snake.tam_cobra = 10;

        snake.dir = 'd';

        /// VAI VIR ANTES DO LAÇO DE MOVIMENTAÇÃO
        hidecursor();
        desenha_interface(velocidade,sair,pontu,snake.tam_cobra);
        desenha_cenario();


        ///tem um for aqui para o número de vezes da opção
        gera_item(cenario1);

        while (seta != ESC && sair)
        {
          while(seta != ESC &&!(seta = kbhit()) && sair)
          {

             for( i = snake.tam_cobra; i > 0; i--)
             {
                    snake.posicoes[i].x = snake.posicoes[i - 1].x;
                    snake.posicoes[i].y = snake.posicoes[i - 1].y;
             }

             muda_direcao(&snake);

            gotoxy(snake.posicoes[snake.tam_cobra].x,snake.posicoes[snake.tam_cobra].y);
            printf(" ");

            ///COLIDIU VEM AQUI
            ///SE COLIDIU = 1, GERA UM NOVO ITEM
            bateu = cenario1[snake.posicoes[CABECA].y - CORRECAOY][snake.posicoes[CABECA].x - CORRECAOX];
            if (colidiu(&pontu, &snake, &velocidade, &sair, bateu))
            {
                cenario1[snake.posicoes[CABECA].y - CORRECAOY][snake.posicoes[CABECA].x - CORRECAOX] = 0; // Coloca um 0 novamente no mapa onde antes tinha um item que foi comido
                gera_item(cenario1);
                desenha_interface(velocidade,sair,pontu,snake.tam_cobra);
            }

            desenha_snake(snake.posicoes[CABECA]);

            Sleep(velocidade);

             for(i = 1; i < snake.tam_cobra; i++)
             {
                if (snake.posicoes[CABECA].x == snake.posicoes[i].x && snake.posicoes[CABECA].y == snake.posicoes[i].y)
                    sair = 0;
             }

          }

          seta = getch();

          if (seta == -32)
              seta = getch();

          nova_direcao(&snake, seta);
        }

return 0;
}
