#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>

// Defini�oes de movimenta��o da cobra
#define LIMITE_COBRA 101
#define CIMA 80
#define BAIXO 72
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define CABECA 0
#define CAUDA 1
#define POS_INICIAL_CABECA 3
#define POS_INICIAL_CAUDA 2
#define POS_INICIAL_CY 13

typedef struct {
    int x;
    int y;
} COORDENADA;

typedef struct {
    COORDENADA posicoes[LIMITE_COBRA];
    char dir;
    int tam_cobra;
} COBRA;

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
  switch (seta) // SWITCH QUE VAI RETORNA A PR�XIMA COORDENADA DA COBRA
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

void movimenta_snake (COBRA snake)
{
    char seta;
    //char vai_para = 'd';
    int x, i;
    int velocidade = 150;
    int sair =1;
        // tamanho inicial que sempre � cinco
         snake.tam_cobra = 5;

        // posi��o inicial onde a cobra vai nascer
        snake.posicoes[CABECA].x = POS_INICIAL_CABECA;
        snake.posicoes[CABECA].y = POS_INICIAL_CY;

        snake.posicoes[CAUDA].x = POS_INICIAL_CAUDA;
        snake.posicoes[CAUDA].y = POS_INICIAL_CY;

        //Dire��o inicial da cobra
        snake.dir = 'd';


        while (seta != ESC)
        {
          while(seta != ESC &&!(seta = kbhit())&& sair) // LA�O QUE FAZ A COBRA SE MOVER PARA UMA DIRE��O AT� QUE UMA TECLA SEJA PRESSIONADA
          {

             for( i = snake.tam_cobra; i > 0; i--) // LA�O PARA VER AS �LTIMAS POSI��ES QUE SER�O APAGADAS
             {
                    snake.posicoes[i].x = snake.posicoes[i - 1].x;
                    snake.posicoes[i].y = snake.posicoes[i - 1].y;
             }

            muda_direcao(&snake); ///La�o que vai movendo a cobra

            putchxy(snake.posicoes[snake.tam_cobra].x,snake.posicoes[snake.tam_cobra].y, ' '); // APAGA A �LTIMA POSI��O DA COBRA


            desenha_snake(snake.posicoes[CABECA]); // IMPRIME A COBRA

            Sleep(velocidade); // VELOCIDADE DA COBRA

            ///Testa se a cobra colidiu com ela mesma
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

}

int main()
{
    COBRA snake_principal;
     // depois ser� escolhido nas op��es

      //CHAMA MENU INICIAL
      movimenta_snake(snake_principal);
return 0;

}
