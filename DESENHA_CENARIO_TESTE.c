#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <windows.h>
#define ESC 27


//Constantes do Score
#define TAM_SCORE 10
#define TAM_JOGADOR 4
#define TAM1 20

/// Definições de mapa
#define LINHAS 24
#define COLUNAS 81
#define CORRECAOX 1
#define CORRECAOY 2
#define TAM_MAPA 10

void carrega_mapa (char *nome_arq_mapa, char mapa_jogo[LINHAS][COLUNAS])
{
    FILE *arq1;
    int i;
       if ((arq1 = fopen(nome_arq_mapa, "r")) == NULL)
       {
           printf("Erro no arquivo 1 ");
           fclose(arq1);
       }

       else
          for(i = 0; i < LINHAS; i++)
          {
             fgets(mapa_jogo[i],COLUNAS, arq1);
             //puts(mapa_jogo[i]);
            //printf("Lendo \n");
          }
        fclose(arq1);
}

void desenha_cenario (char cenario[LINHAS][COLUNAS],int nivel)
{
    int lin, col;
    char mapa1[TAM_MAPA] = {"map1.txt"};
    char mapa2[TAM_MAPA] = {"map2.txt"};
    char mapa3[TAM_MAPA] = {"map3.txt"};

        switch(nivel)
        {
            case 1: carrega_mapa(mapa1,cenario);
                    break;

            case 2: carrega_mapa(mapa2,cenario);
                    break;

            case 3: carrega_mapa(mapa3,cenario);
                    break;
        }


         for (lin = 0; lin < LINHAS; lin++)
            {
                for (col = 0; col < COLUNAS; col++)
                    if (cenario[lin][col] == '1')
                    {
                        textcolor (BLACK);
                        textbackground(LIGHTBLUE);
                        putchxy(col + CORRECAOX, lin + CORRECAOY ,'x');
                    }
            }
        textcolor(LIGHTGRAY);
        textbackground(BLACK);
}

main()
{
    char cenario[LINHAS][COLUNAS];
    int nivel = 1;

    desenha_cenario(cenario, nivel);
    return 0;
}
