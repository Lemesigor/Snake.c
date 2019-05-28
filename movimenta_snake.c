#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>

//Defines para movimentar a Snake
#define LIMITE_COBRA 100
#define CIMA 80
#define BAIXO 72
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27

typedef struct {
    int x;
    int y;
} COORDENADA;

//movimenta_snake {int snake[2][LIMITE_COBRA], COORDENADA prox_pos, int tam_atual, int booleano}
int main()
{
    char seta;
    char vai_para = 'd';
    int snake[2][LIMITE_COBRA];
    int tam_cobra = 5;
    int x, i;

        snake[0][0] = 3;
        snake[1][0] = 7;

        snake[0][1] = 4;
        snake[1][1] = 7;

        gotoxy(7,3);
        while (seta != ESC)
        {
          while(seta != ESC &&!(seta = kbhit())) // LAÇO QUE FAZ A COBRA SE MOVER PARA UMA DIREÇÃO ATÉ QUE UMA TECLA SEJA PRESSIONADA
          {

             for( x = tam_cobra; x > 0; x--) // LAÇO PARA VER AS ÚLTIMAS POSIÇÕES QUE SERÃO APAGADAS
             {
                    snake[0][x] = snake[0][x - 1];
                    snake[1][x] = snake[1][x - 1];
             }

              switch (vai_para)
              {
                case 'b': snake[1][0]--;
                        break;

                case 'c': snake[1][0]++;
                        break;

                case 'd': snake[0][0] ++;
                        break;

                case 'e': snake[0][0] --;
                        break;
              }

            gotoxy(snake[0][tam_cobra],snake[1][tam_cobra]); // APAGA A ÚLTIMA POSIÇÃO DA COBRA
            printf(" ");

            textbackground(BROWN);
            textcolor (GREEN); // COBRA VERDE
            putchxy(snake[0][0],snake[1][0], 'o'); // IMPRIME A COBRA
            textcolor (WHITE); // VOLTA COR DO TEXTO NORMAL
            textbackground (BLACK);
          Sleep(100); // VELOCIDADE
          }

            seta = getch();

            if (seta == -32)
                seta = getch();

            switch (seta) // SWITCH QUE VAI RETORNA A PRÓXIMA COORDENADA DA COBRA
            {
                    case BAIXO: vai_para = 'b';
                    break;

                    case CIMA: vai_para = 'c';
                    break;

                    case DIREITA: vai_para = 'd';
                    break;

                    case ESQUERDA: vai_para = 'e';
                    break;

            }
        }

return 0;
}
