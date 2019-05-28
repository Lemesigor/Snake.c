#define TAM_MAXIMO_NOME 20
#define TOTAL_TUNEIS 5
#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>



typedef struct {
    int x;
    int y;
} COORDENADA;

typedef struct {
    COORDENADA pos_tunel;
    int id_entrada;
    char dir;
    int id_saida;
} TUNEL;

void salva_tunel (TUNEL tunel_teste[TOTAL_TUNEIS], int tam_array, char nome_arq[TAM_MAXIMO_NOME])
{
    TUNEL buffer[TOTAL_TUNEIS];
    FILE *arq;
    int i;

        if(!(arq = fopen(nome_arq,"wb")))
               printf("Erro");

        else
        {

        fwrite(tunel_teste,sizeof(TUNEL),tam_array,arq);
                fclose(arq);
        }
}

int carrega_tunel (TUNEL *tunel_teste, char nome_arq[TAM_MAXIMO_NOME])
{
    FILE *arq;
    int quant_tuneis = 0;

        if(!(arq = fopen(nome_arq,"rb")))
            printf("Arquivo nao-lido");

        while(!feof(arq))
        {
            if (fread (&tunel_teste[quant_tuneis], sizeof (TUNEL),1,arq)== 1)
                quant_tuneis++;


        }
        fclose(arq);
        return quant_tuneis;

}
// MAIN TESTE
int main ()
{
    TUNEL tunel_esq = {{4,5}, 0, '<', 3}, tunel_dir = {{5,6}, 1, '>', 0}, tunel_cim = {{6,7}, 2, '^', 1}, tunel_bai = {{7,8}, 3, 'v', 2};
   // TUNEL tuneis[TOTAL_TUNEIS] = {tunel_esq, tunel_dir, tunel_cim, tunel_bai};
    TUNEL tuneis_teste [20];
    char nome_arquivo[TAM_MAXIMO_NOME] = {"tuneis_map3"};
    int i, quantidade_tunel = 0;

      // TUNEL tuneis [2] = {{{37,11}, 'd', 'A', 'B'}, {{42,11}, 'e', 'B', 'A'}};
       TUNEL tuneis[TOTAL_TUNEIS] = {{{38,6}, 'd', 'A', 'B'}, {{40,1}, 'e', 'B', 'E'},{{77,11}, 'b', 'C', 'A'}, {{38,16}, 'd', 'D', 'C'},{{40,23}, 'd', 'E', 'D'}} ;

         salva_tunel(tuneis, TOTAL_TUNEIS,nome_arquivo);

       /* printf("Quantidade de tuneis?");
        scanf("%d",&quantidade_tunel);

        fflush(stdin);
        printf("\n Nome do arquivo:");
        gets(nome_arquivo);

        for (i=0; i < quantidade_tunel; i++)
            putchxy(tuneis[i].pos_tunel.x, tuneis[i].pos_tunel.y, tuneis[i].dir);



        salva_tunel(tuneis, quantidade_tunel, nome_arquivo);

        quantidade_tunel = carrega_tunel(tuneis_teste, nome_arquivo);

        printf("\n\n\n Quantidade achada = %d", quantidade_tunel);

        getch();
        clrscr();

        for (i=0; i < quantidade_tunel; i++)
            putchxy(tuneis_teste[i].pos_tunel.x, tuneis_teste[i].pos_tunel.y, tuneis_teste[i].dir);*/


}
