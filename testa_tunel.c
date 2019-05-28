#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>
#define TAM1 20


typedef struct {
    int x;
    int y;
} COORDENADA;
typedef struct {
    COORDENADA posicao_tunel;
    char id_entrada;
    char dir;
    char id_saida;
} TUNEL;

void carrega_tunel (TUNEL *tunel,int nivel)
{
    FILE *arq;
    int quant_tuneis = 0;
    char arq_tunel[TAM1];
    TUNEL buffer;

        switch (nivel)
        {
          case 2: strcpy(arq_tunel,"tuneis_map2");
                        break;

          case 3: strcpy(arq_tunel,"tuneis_map3");
                      break;
        }

        if(!(arq = fopen(arq_tunel,"rb")))
            printf("Arquivo nao-lido");


        while(!feof(arq))
        {
            if (fread (&buffer, sizeof (TUNEL),1,arq)== 1)
            {
                tunel[quant_tuneis] = buffer;
                quant_tuneis++;
                printf("pos x %d, pos y %d", tunel[quant_tuneis].posicao_tunel.x, tunel[quant_tuneis].posicao_tunel.y);
            }


        }
        fclose(arq);
}
