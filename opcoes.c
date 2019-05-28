/* Alterar as frutas para terem formatos diferentes
    Criar o menu ajuda
    Arrumar a velocidade inicial da cobra
    Algoritmo de pontuação alterado */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

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
#define TAM_LOGO 6

///Definições opções
#define MIN_ITENS 1
#define MAX_ITENS 10
#define VEL_INICIAL_MIN 1
#define VEL_INICIAL_MAX 10
#define TAM_MAX_INICIAL 100
#define TAM_MIN_INICIAL 10
#define VEL_MAX 100
#define VEL_MIN 550
#define VEL_INICIAL_PADRAO 5
#define TAM_MAXIMO_PADRAO 15
#define MAX_ITENS_PADRAO 2
#define VELOCIDADE1 550
#define VELOCIDADE2 500
#define VELOCIDADE3 450
#define VELOCIDADE4 400
#define VELOCIDADE5 350
#define VELOCIDADE6 300
#define VELOCIDADE7 250
#define VELOCIDADE8 200
#define VELOCIDADE9 150
#define VELOCIDADE10 100

///Definições de items
#define CONSTANTE_VELOCIDADE 50
#define BASE_SKIP 1000
#define COMIDA 'C'
#define FASTER 'F'
#define SLOWER 'S'
#define SKIP   'K'
#define PROBABILIDADE_COMIDA 67
#define PROBABILIDADE_FASTER 87
#define PROBABILIDADE_SLOWER 97
#define PROBABILIDADE_SKIP 100
#define PONTUACAO_BASE_COMIDA 2
#define PONTUACAO_BASE_SLOWER 1
#define PONTUACAO_BASE_FASTER 3
#define PONTUACAO_BASE_SKIP 40
#define CONSTANTE_PONTUACAO 1

/// Definiçoes de movimentação da cobra
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
#define TAM_INICIAL_COBRA 5

/// Definições de Tuneis
#define TUNEL_A 'A'
#define TUNEL_B 'B'
#define TUNEL_C 'X'
#define TUNEL_D 'D'
#define TUNEL_E 'E'
#define TOTAL_TUNEIS 5

#define POS_TUNEL_A 0
#define POS_TUNEL_B 1
#define POS_TUNEL_C 2
#define POS_TUNEL_D 3
#define POS_TUNEL_E 4

///Definicao niveis
#define NIVEL1 1
#define NIVEL2 2
#define NIVEL3 3


typedef struct {
    int x;
    int y;
} COORDENADA;

typedef struct {
    COORDENADA posicoes[LIMITE_COBRA];
    char dir;
    int tam_cobra;
} COBRA;

typedef struct {
int vel_inicial;
int tam_maximo;
int max_item;
} CONFIG;

typedef struct{
int pontuacao;
char nome_jogador [TAM_JOGADOR];
} SCORE;

typedef struct {
    COORDENADA posicao_tunel;
    char id_entrada;
    char dir;
    char id_saida;
} TUNEL;

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void carrega_config (CONFIG *config_carregada, char nome_arquivo[])
{
    CONFIG buffer;
    FILE *arq;

    if(!(arq = fopen(nome_arquivo,"rb")))
    {
      //preenche com as configurações mínimas
      config_carregada -> vel_inicial = VEL_INICIAL_PADRAO;
      config_carregada -> tam_maximo  = TAM_MAXIMO_PADRAO;
      config_carregada -> max_item = MAX_ITENS_PADRAO;
    }

    else
    {
        fread(&buffer, sizeof(CONFIG),1,arq);

      config_carregada -> vel_inicial = buffer.vel_inicial;
      config_carregada -> tam_maximo  = buffer.tam_maximo;
      config_carregada -> max_item = buffer.max_item;


    }
    fclose(arq);
}

void salva_config (CONFIG config_usuario, char nome_arquivo [])
{
    CONFIG buffer;
    FILE *arq;
        if(!(arq = fopen(nome_arquivo,"wb")))
            printf("Erro criacao ");

        else
        {
            buffer.vel_inicial = config_usuario.vel_inicial;
            buffer.tam_maximo = config_usuario.tam_maximo;
            buffer.max_item = config_usuario.max_item ;

            fwrite(&buffer, sizeof(CONFIG),1,arq);
            fclose(arq);
        }

}

void escolhe_velocidade_inicial (CONFIG *config_usuario)
{
    int volta_menu = 1, escolheu = 1;
    int velocidade_escolhida;

        while (escolheu && volta_menu)
        {
            clrscr();
            gotoxy(20,5);

            textcolor(YELLOW);
            printf("Escolha a velocidade entre 1 e 10 \n\n\t\t\t\t");
            textcolor(LIGHTGRAY);
            scanf("%d", &velocidade_escolhida);



            if (velocidade_escolhida < VEL_INICIAL_MIN || velocidade_escolhida > VEL_INICIAL_MAX)
                clrscr();

            else
            {
                config_usuario->vel_inicial = ajusta_velocidade(velocidade_escolhida);
                escolheu = 0; /// para sair do laço

            }
        }
}

void escolhe_tamanho_maximo (CONFIG *config_usuario)
{
    int volta_menu = 1, escolheu = 1;
    int tamanho_escolhido;

        while (escolheu && volta_menu)
        {
            clrscr();
            gotoxy(20,5);

            textcolor(YELLOW);
            printf("Escolha o tamanho maximo entre 10 e 100 \n\n\t\t\t\t");
            textcolor(LIGHTGRAY);
            scanf("%d", &tamanho_escolhido);


            if (tamanho_escolhido < 10 || tamanho_escolhido > 100)
                clrscr();

            else
            {
                config_usuario->tam_maximo = tamanho_escolhido;
                escolheu = 0; /// para sair do laço
            }
        }
}

void escolhe_itens_maximo (CONFIG *config_usuario)
{
    int volta_menu = 1, escolheu = 1;
    int max_itens;

        while (escolheu && volta_menu)
        {
            clrscr();
            gotoxy(20,5);

            textcolor(YELLOW);
            printf("Escolha o maximo de itens entre 1 e 10 \n\n\t\t\t\t");
            textcolor(LIGHTGRAY);
            scanf("%d", &max_itens);


            if (max_itens < MIN_ITENS || max_itens > MAX_ITENS)
                clrscr();

            else
            {
                config_usuario->max_item = max_itens;
                escolheu = 0; /// para sair do laço
            }
        }
}

void desenha_logo ()
{
    int lin, col;
    char logo_jogo[TAM_LOGO][COLUNAS] = {"0000000000000000000000000000000000000000000000000000000000000000000000000000000",
                                         "0000000000000000000000111001100010011110010010011110000000000000000000000000000",
                                         "0000000000000000000000100001010010010010010100010000000000000000000000000000000",
                                         "0000000000000000000000111001001010011110011000011110000000000000000000000000000",
                                         "0000000000000000000000001001000110010010010100010000000000000000000000000000000",
                                         "0000000000000000000000111001000010010010010010011110000000000000000000000000000"};


         for (lin = 0; lin < TAM_LOGO; lin++)
            {
                for (col = 0; col < COLUNAS; col++)
                {
                    if (logo_jogo[lin][col] == '1')
                    {
                        textcolor (LIGHTRED);
                        textbackground(LIGHTRED);
                        putchxy(col + CORRECAOX, lin + CORRECAOY ,'.');
                    }
                }
            }
            textcolor(LIGHTGRAY);
            textbackground(BLACK);

}

void opcoes (CONFIG *config_usuario)
{
    char tecla;
    int volta_menu = 1; ///Condição para sair do laço

         while (volta_menu)
         {
            clrscr();
            gotoxy(30,5);
            textcolor(YELLOW);
            printf("OPCOES\n\n\n");

            textcolor(LIGHTGRAY);
            printf("\t\t\t(V)elocidade Inicial\n\n \t\t\t(T)amanho Maximo\n\n \t\t\t(M)aximo de Itens");

            tecla = getch();
            //tolower(tecla);

                if (tecla != 'v' && tecla != 't' && tecla != 'm' && tecla != ESC)
                        clrscr();


                else
                {
                    switch (tecla)
                    {
                        case 'v':   escolhe_velocidade_inicial(config_usuario);
                                  //printf("teste %d", config_usuario->vel_inicial);
                                    break;

                        case 't':   escolhe_tamanho_maximo(config_usuario);
                                    //printf("teste %d", config_usuario->tam_maximo);
                                    //getch();
                                    break;

                        case 'm':   escolhe_itens_maximo(config_usuario);
                                    //printf("teste %d", config_usuario->max_item);
                                   // getch();
                                    break;

                        case ESC: volta_menu = 0;
                                  break;

                    }
                }

         }
}

void salva_score (SCORE score_atual[])
{
    FILE *arq1; // ponteiro para o arquivo
    char nome[TAM1] = {"arquivoscore.txt"};
    int ind_score;

       if ((arq1 = fopen(nome, "w+")) == NULL)
       {
           printf("Erro no arquivo");
           fclose(arq1);
       }

        else
            for (ind_score = 0; ind_score < TAM_SCORE; ind_score++)
            {
               fprintf(arq1,"%d" "%s\n", score_atual[ind_score].pontuacao,score_atual[ind_score].nome_jogador);
            }
        fclose(arq1);
}

void carrega_score (SCORE score_atual[])
{
    FILE *arq1;
    char nome[TAM1] = {"arquivoscore.txt"};
    char string_erro[TAM_JOGADOR] = {"AAA"};
    int ind_score;

        if ((arq1 = fopen(nome, "r")) == NULL)
        {
           for (ind_score = 0; ind_score < TAM_SCORE; ind_score++)
           {
               score_atual[ind_score].pontuacao = 0;
               strcpy(score_atual[ind_score].nome_jogador,string_erro);
           }
        fclose(arq1);
        }

        else
        {
           ind_score = 0;
            while (!feof(arq1) && ind_score < TAM_SCORE)
            {
                fscanf(arq1, "%4d %s", &score_atual[ind_score].pontuacao, score_atual[ind_score].nome_jogador);
                ind_score ++;
            }
       // CONSIDERAR BYTES SEM VALOR VÃLIDO NO TRABALHO FINAL
            fclose(arq1);
        }
}

void exibe_score (SCORE score_atual[])
{
    int ind_score;

        carrega_score(score_atual);
        clrscr();
        //gotoxy(20,5);
        textcolor(LIGHTGRAY);
        for (ind_score = 0; ind_score < TAM_SCORE; ind_score++)
            printf("\n\n\t\t\t\t  %d \t %s", score_atual[ind_score].pontuacao, score_atual[ind_score].nome_jogador);

        getch();
}

void ajuda ()
{
    clrscr();

    textcolor(YELLOW);
    printf("\t\n\t\t - UTILIZE AS SETAS DO TECLADO PARA MOVER A COBRA");
    printf("\n\n\t - VA PEGANDO AS COMIDAS QUE APARECEM PARA MUDAR O STATUS DA COBRA:\n\n");
    textcolor(LIGHTRED);
    printf("\t %c", COMIDA);
    textcolor(YELLOW);
    printf("  AUMENTA O TAMANHO DA COBRA\n");
    textcolor(LIGHTGRAY);
    printf("\t %c", FASTER);
    textcolor(YELLOW);
    printf("  AUMENTA A VELOCIDADE DA COBRA\n");
    textcolor(LIGHTMAGENTA);
    printf("\t %c", SLOWER);
    textcolor(YELLOW);
    printf("  DIMINUI A VELOCIDADE DA COBRA\n");
    textcolor(LIGHTCYAN);
    printf("\t %c", SKIP);
    textcolor(YELLOW);
    printf("  FAZ AVANCAR DE NIVEL\n\n");
    printf("\t - PASSE DE NIVEL COMENDO %c OU CHEGANDO AO TAMANHO MAXIMO DA COBRA\n\n", SKIP);
    printf("\t - VENCA O JOGO COMPLETANDO TODOS OS NIVEIS");
    textcolor(LIGHTRED);
    printf("\n\n \t\t\t\t\tBOA SORTE");

    getch();

}

void creditos()
{

            clrscr();
            gotoxy(20,5);

            textcolor(LIGHTGRAY);
            printf(" Algoritmos e Programacao 2017/1 \n\n\n\n\n \t\t   Jogo desenvolvido por  ");
            textcolor(YELLOW);
            printf("Igor Lemes");
            textcolor(LIGHTGRAY);

            getch();

}

void carrega_mapa (char *nome_arq_mapa, char mapa_jogo[LINHAS][COLUNAS])
{
    FILE *arq1;
    int ind_mapa;
       if ((arq1 = fopen(nome_arq_mapa, "r")) == NULL)
       {
           printf("Erro ao abrir o arquivo");
           fclose(arq1);
           getch();
       }

       else
          for(ind_mapa = 0; ind_mapa < LINHAS; ind_mapa++)
          {
             fgets(mapa_jogo[ind_mapa],COLUNAS, arq1);
          }
        fclose(arq1);
}

void carrega_logo_nivel (char *nome_arq_logo, char logo[LINHAS][COLUNAS],int nivel)
{
    FILE *arq1;
    int ind_logo;
       if ((arq1 = fopen(nome_arq_logo, "r")) == NULL)
       {
           printf("\n\n\n\n\n\n\n NIVEL %d",nivel);
           fclose(arq1);
           getch();
       }

       else
          for(ind_logo = 0; ind_logo < LINHAS; ind_logo++)
          {
             fgets(logo[ind_logo],COLUNAS, arq1);
             //puts(mapa_jogo[i]);
            //printf("Lendo \n");
          }
        fclose(arq1);
}

void desenha_logo_nivel (char logo[LINHAS][COLUNAS])
{
    int lin, col;

         for (lin = 0; lin < LINHAS; lin++)
            {
                for (col = 0; col < COLUNAS; col++)
                    if (logo [lin][col] == '1')
                    {
                        textcolor (YELLOW);
                        textbackground(YELLOW);
                        putchxy(col + CORRECAOX, lin + CORRECAOY ,'x');
                    }

            }
        textcolor(LIGHTGRAY);
        textbackground(BLACK);
}

void exibe_logo_nivel (int nivel)
{
    char logo1 [TAM1] = {"nivel1_logo.txt"};
    char logo2 [TAM1] = {"nivel2_logo.txt"};
    char logo3 [TAM1] = {"nivel3_logo.txt"};
    char logo_carregado [LINHAS][COLUNAS];

        switch (nivel)
        {
            case NIVEL1:    carrega_logo_nivel(logo1,logo_carregado,nivel);
                            desenha_logo_nivel(logo_carregado);
                            getch();
                            break;

            case NIVEL2:    carrega_logo_nivel(logo2,logo_carregado,nivel);
                            desenha_logo_nivel(logo_carregado);
                            getch();
                            break;

            case NIVEL3:    carrega_logo_nivel(logo3,logo_carregado,nivel);
                            desenha_logo_nivel(logo_carregado);
                            getch();
                            break;
        }
}

char desenha_tunel (char tunel)
{

    if (tunel == TUNEL_A || tunel == TUNEL_D || tunel == TUNEL_C)
        return '>';

    else if (tunel == TUNEL_B ||tunel == TUNEL_E)
        return '<';



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
                    else
                        if (cenario[lin][col] == TUNEL_A || cenario[lin][col] == TUNEL_B || cenario[lin][col] == TUNEL_C || cenario[lin][col] == TUNEL_D  || cenario[lin][col] == TUNEL_E)
                    {
                        textcolor (BLACK);
                        textbackground(WHITE);
                        putchxy(col + CORRECAOX, lin + CORRECAOY ,desenha_tunel(cenario[lin][col])); /// FUNÇAO TESTA QUAL É A REPRESENTAÇAO DO TUNEL QUE SERÁ DESENHADO
                    }
            }
        textcolor(LIGHTGRAY);
        textbackground(BLACK);
}

void desenha_interface (int velocidade, int cenario, int pontuacao, int tam_cobra)
{
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Pontuacao:%d \t Nivel:%d \t Tamanho:%d \t Velocidade:%d", pontuacao, cenario, tam_cobra, converte_velocidade(velocidade));
    textcolor(LIGHTGRAY);
}

void apaga_snake (COBRA *snake)
{
    int ind_apaga;

    for( ind_apaga = snake->tam_cobra; ind_apaga > 0; ind_apaga--) /// LAÇO PARA VER AS ÚLTIMAS POSIÇÕES QUE SERÃO APAGADAS
             {
                    snake->posicoes[ind_apaga].x = snake->posicoes[ind_apaga - 1].x;
                    snake->posicoes[ind_apaga].y = snake->posicoes[ind_apaga - 1].y;
             }
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

void nova_direcao (COBRA *snake, char seta, int *perdeu)
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

                    case ESC: *perdeu = 0;
                               break;

            }
}

void desenha_snake (COORDENADA cabeca_cobra)
{
            textcolor (BLACK);
            textbackground(LIGHTGREEN);
            putchxy(cabeca_cobra.x,cabeca_cobra.y, 'o'); // IMPRIME A COBRA
            textcolor(LIGHTGRAY);
            textbackground(BLACK);
}

void se_bateu (COBRA snake, int *perdeu)
{
   int ind_colidiu;

        for(ind_colidiu = 1; ind_colidiu < snake.tam_cobra; ind_colidiu++)
             {
                if (snake.posicoes[CABECA].x == snake.posicoes[ind_colidiu].x && snake.posicoes[CABECA].y == snake.posicoes[ind_colidiu].y)
                    *perdeu = 0;
             }
}

int converte_velocidade (int velocidade_atual)
{
    switch (velocidade_atual)
    {
        case VELOCIDADE1: return 1;
                          break;

        case VELOCIDADE2: return 2;
                          break;

        case VELOCIDADE3: return 3;
                          break;

        case VELOCIDADE4: return 4;
                          break;

        case VELOCIDADE5: return 5;
                          break;

        case VELOCIDADE6: return 6;
                          break;

        case VELOCIDADE7: return 7;
                          break;

        case VELOCIDADE8: return 8;
                          break;

        case VELOCIDADE9: return 9;
                          break;

        case VELOCIDADE10: return 10;
                          break;
    }
}

int ajusta_velocidade (int velocidade_escolhida)
{

    switch (velocidade_escolhida)
    {
        case 1: return VELOCIDADE1;
                break;

        case 2: return VELOCIDADE2;
                break ;

        case 3: return VELOCIDADE3;
                break ;

        case 4: return VELOCIDADE4;
                break ;

        case 5: return VELOCIDADE5;
                break ;

        case 6: return VELOCIDADE6;
                break ;

        case 7: return VELOCIDADE7;
                break ;

        case 8: return VELOCIDADE8;
                break ;

        case 9: return VELOCIDADE9;
                break ;

        case 10: return VELOCIDADE10;
                break ;
    }

}

char escolhe_item ()
{
    int item_sorteado;




       item_sorteado = (rand() % ((100 - 1) + 1) + 1);

       if (item_sorteado <= PROBABILIDADE_COMIDA )
        {
            textcolor(LIGHTRED);
            return COMIDA; ///comida
        }

       if (item_sorteado > PROBABILIDADE_COMIDA  && item_sorteado <= PROBABILIDADE_FASTER)
        {
            textcolor(LIGHTGRAY);
            return FASTER; ///faster
        }

       if (item_sorteado > PROBABILIDADE_FASTER && item_sorteado <= PROBABILIDADE_SLOWER)
        {
            textcolor(LIGHTMAGENTA);
            return SLOWER; ///slower
        }

       if(item_sorteado > PROBABILIDADE_SLOWER && item_sorteado <= PROBABILIDADE_SKIP)
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

        //srand(time(0));


        while (testa_obstaculo)
        {
            eixoy = rand() % LINHAS;
            eixox = rand() % COLUNAS;
            if (cenario[eixoy][eixox] == '0')
                testa_obstaculo = 0;
        }
        item = escolhe_item(); /// Gera um item

        putchxy (eixox + CORRECAOX, eixoy + CORRECAOY,item); /// desenha o item na tela
        textcolor (LIGHTGRAY);

        cenario[eixoy][eixox] = item;  /// Coloca o item no arranjo para testar se cabeça da cobra come ou não o item

}

int colidiu (int *pontuacao, COBRA *snake, int *velocidade, int *perdeu, int *passou, char colisao)
{

    int velocidade_aux;

    switch(colisao)
    {
        case '1':       *perdeu = 0;
                        //printf(" perdeu");
                        return 0;
                        break;

        case COMIDA:    snake->tam_cobra++;
                        velocidade_aux = converte_velocidade(*velocidade); /// Auxiliar recebe o valor decimal da velocidade para fazer o cálculo da pontuacao
                        *pontuacao = floor(*pontuacao + ((PONTUACAO_BASE_COMIDA * snake->tam_cobra) / (CONSTANTE_PONTUACAO * velocidade_aux)));
                        return 1;
                        break;

        case SLOWER:    if (*velocidade < VEL_MIN )
                            *velocidade = *velocidade + CONSTANTE_VELOCIDADE; /// slower, diminui velocidade
                        velocidade_aux = converte_velocidade(*velocidade);
                        *pontuacao = floor(*pontuacao + ((PONTUACAO_BASE_SLOWER * snake->tam_cobra) / (CONSTANTE_PONTUACAO * velocidade_aux)));
                        return 1;
                        break;

        case FASTER:  if (*velocidade > VEL_MAX)
                            *velocidade = *velocidade - CONSTANTE_VELOCIDADE; /// faster, aumenta velocidade
                        velocidade_aux = converte_velocidade(*velocidade);
                        *pontuacao = floor(*pontuacao + ((PONTUACAO_BASE_FASTER * snake->tam_cobra) / (CONSTANTE_PONTUACAO * velocidade_aux)));
                        return 1;
                        break;

        case SKIP:      *pontuacao = *pontuacao + BASE_SKIP;
                        velocidade_aux = converte_velocidade(*velocidade);
                        *pontuacao = floor(*pontuacao + ((PONTUACAO_BASE_SKIP* snake->tam_cobra) / (CONSTANTE_PONTUACAO * velocidade_aux)));
                        *passou = 1;
                        return 1;
                        break;

        default:        return 0; ///Se não comeu nenhum item, retorna falso
                        break;

    }
}

void entra_tunel (TUNEL tuneis[],char colisao, COBRA *snake, int nivel)
{

    if (nivel == NIVEL2)
    {
        switch (colisao)
        {
            case TUNEL_A:  //snake -> dir =
                           snake->posicoes[CABECA].x = tuneis[POS_TUNEL_B].posicao_tunel.x + CORRECAOX + CORRECAOX;
                           snake->posicoes[CABECA].y = tuneis[POS_TUNEL_B].posicao_tunel.y + CORRECAOY;
                      break;

            case TUNEL_B: //snake -> dir ='e';
                          snake->posicoes[CABECA].x = tuneis[POS_TUNEL_A].posicao_tunel.x;
                          snake->posicoes[CABECA].y = tuneis[POS_TUNEL_A].posicao_tunel.y + CORRECAOY;
                        break;
        }
    }

    else
        if (nivel == NIVEL3)
        {
            switch (colisao)
            {
                case TUNEL_A:   snake->posicoes[CABECA].x = tuneis[POS_TUNEL_B].posicao_tunel.x + CORRECAOX + CORRECAOX;
                                snake->posicoes[CABECA].y = tuneis[POS_TUNEL_B].posicao_tunel.y + CORRECAOY;
                                break;

                case TUNEL_B:   snake->dir = 'd';
                                snake->posicoes[CABECA].x = tuneis[POS_TUNEL_E].posicao_tunel.x + CORRECAOX + CORRECAOX;
                                snake->posicoes[CABECA].y = tuneis[POS_TUNEL_E].posicao_tunel.y + CORRECAOX;
                                break;

                 case TUNEL_C:  snake->dir = 'e';
                                snake->posicoes[CABECA].x = tuneis[POS_TUNEL_A].posicao_tunel.x;
                                snake->posicoes[CABECA].y = tuneis[POS_TUNEL_A].posicao_tunel.y + CORRECAOY + CORRECAOX;
                                break;

                 case TUNEL_D:  snake ->dir = 'e';
                                snake->posicoes[CABECA].x = tuneis[POS_TUNEL_C].posicao_tunel.x;
                                snake->posicoes[CABECA].y = tuneis[POS_TUNEL_C].posicao_tunel.y + CORRECAOY;
                                break;

                 case TUNEL_E:   snake->posicoes[CABECA].x = tuneis[POS_TUNEL_D].posicao_tunel.x;
                                snake->posicoes[CABECA].y = tuneis[POS_TUNEL_D].posicao_tunel.y + CORRECAOY;
                                break;

            }
        }
}

void colidiu_tunel (int *perdeu, TUNEL tuneis[], char colisao, COBRA *snake, int nivel)
{
    switch (colisao)
    {
        case TUNEL_A: if (snake->dir == 'd')
                           entra_tunel (tuneis, colisao, snake, nivel);
                      else
                        *perdeu = 0;
                      break;

        case TUNEL_B: if (snake ->dir == 'e')
                           entra_tunel (tuneis, colisao, snake, nivel);
                        else
                         *perdeu = 0;
                        break;

        case TUNEL_C: if (snake->dir == 'd')
                           entra_tunel (tuneis, colisao, snake, nivel);
                        else
                         *perdeu = 0;
                        break;

        case TUNEL_D: if (snake ->dir == 'd')
                           entra_tunel (tuneis, colisao, snake, nivel);
                        else
                         *perdeu = 0;
                        break;

        case TUNEL_E: if (snake ->dir == 'e')
                           entra_tunel (tuneis, colisao, snake, nivel);
                        else
                         *perdeu = 0;
                        break;
    }
}

void carrega_tunel (TUNEL tunel[],int nivel)
{
    int i_tuneis;
    TUNEL buffer;
    TUNEL tuneis_nivel2[TOTAL_TUNEIS] = {{{37,11}, 'd', 'A', 'B'}, {{42,11}, 'e', 'B', 'A'}};
    TUNEL tuneis_nivel3[TOTAL_TUNEIS] = {{{38,6}, 'd', 'A', 'B'}, {{40,1}, 'e', 'B', 'E'},{{77,11}, 'b', 'C', 'A'}, {{38,16}, 'd', 'D', 'C'},{{40,23}, 'd', 'E', 'D'}} ;

        switch (nivel)
        {
          case NIVEL2: for (i_tuneis = 0; i_tuneis < TOTAL_TUNEIS; i_tuneis++)
                            tunel[i_tuneis] = tuneis_nivel2[i_tuneis];
                        break;

          case NIVEL3: for (i_tuneis = 0; i_tuneis < TOTAL_TUNEIS; i_tuneis++)
                            tunel[i_tuneis] = tuneis_nivel3[i_tuneis];
                      break;
        }
}

void iteracao_snake (COBRA snake, char cenario [LINHAS][COLUNAS], SCORE *score_jogador, CONFIG config_jogador, int nivel, int *perdeu,int *passou)
{
    char seta;
    char bateu;
    int ind_itens, ind_apaga, ind_colidiu;
    int velocidade;
    TUNEL tuneis [TOTAL_TUNEIS];

        carrega_tunel(tuneis, nivel); /// carrega os tuneis que serão colocados no cenário

        /// tamanho inicial que sempre é cinco
         snake.tam_cobra = TAM_INICIAL_COBRA;

         ///Desenha a interface pela primeira vez
         desenha_interface (config_jogador.vel_inicial,nivel,score_jogador->pontuacao,snake.tam_cobra);

        /// posição inicial onde a cobra vai nascer
        snake.posicoes[CABECA].x = POS_INICIAL_CABECA;
        snake.posicoes[CABECA].y = POS_INICIAL_CY;

        snake.posicoes[CAUDA].x = POS_INICIAL_CAUDA;
        snake.posicoes[CAUDA].y = POS_INICIAL_CY;

        ///Direção inicial da cobra
        snake.dir = 'd';

        /// Ajuste para velocidade inicial ficar nos padrões da função Sleep
        velocidade = ajusta_velocidade(config_jogador.vel_inicial);

        for (ind_itens = 1; ind_itens <= config_jogador.max_item; ind_itens++)
            gera_item(cenario); /// GERA N ITENS INICIAIS DE ACORDO COM A S DEFINIÇÕES DO JOGADOR

	    while (seta != ESC && *perdeu && *passou == 0)
        {
			while(seta != ESC && !(seta = kbhit())&& *perdeu && *passou == 0) /// LAÇO QUE FAZ A COBRA SE MOVER PARA UMA DIREÇÃO ATÉ QUE UMA TECLA SEJA PRESSIONADA
			{
				apaga_snake(&snake);

				muda_direcao(&snake); ///Laço que vai movendo a cobra

				putchxy(snake.posicoes[snake.tam_cobra].x,snake.posicoes[snake.tam_cobra].y, ' '); /// APAGA A ÚLTIMA POSIÇÃO DA COBRA

				///Testa se a cobra colidiu em algum item ou na parede
				bateu = cenario[snake.posicoes[CABECA].y - CORRECAOY][snake.posicoes[CABECA].x - CORRECAOX]; /// Variável que guarda o caracter do mapa em que está a cabeça da cobra

				if (colidiu(&score_jogador->pontuacao, &snake, &velocidade, perdeu, passou, bateu))
				{
					cenario[snake.posicoes[CABECA].y - CORRECAOY][snake.posicoes[CABECA].x - CORRECAOX] = 0; /// Coloca um 0 novamente no mapa onde antes tinha um item que foi comido
					gera_item(cenario);
					desenha_interface(velocidade,*perdeu,score_jogador->pontuacao,snake.tam_cobra);

					if (snake.tam_cobra == config_jogador.tam_maximo) /// Se a cobra chega no tamanho máximo definido pelo usuário, muda a variável que faz passar de nível
						*passou = 1;
				}

				colidiu_tunel(perdeu, tuneis, bateu, &snake, nivel);

				desenha_snake(snake.posicoes[CABECA]); /// IMPRIME A COBRA

				Sleep(velocidade); /// VELOCIDADE DA COBRA

				///Testa se a cobra colidiu com ela mesma
				se_bateu(snake,perdeu);

			}

            seta = getch();

			if (seta == -32)
				seta = getch();

			nova_direcao(&snake, seta, perdeu); ///Funçao que testa qual seta foi apertada
        }

}

void mensagem_final (int venceu)
{
    char tecla;
    clrscr();
    if (venceu == 0)
    {
            textcolor(YELLOW);
            printf("\n\n\n\n\n\n \t\t\t\t  VOCE \n \t\t\t\t VENCEU! =)");
            getch();
    }

    else
        if (venceu == 1)
        {
            textcolor(YELLOW);
            printf("\n\n\n\n\n\n \t\t\t\t  VOCE \n \t\t\t\t PERDEU :(");
            getch();
       }
}

void total_pontos (SCORE score_jogador)
{
    clrscr();
    textcolor(YELLOW);
    printf("\n\n\n\n\n\n \t\t\t\t  VOCE FEZ \n\n \t\t\t\t %d PONTOS", score_jogador.pontuacao);
    textcolor(LIGHTGRAY);
    getch();
}

void novo_jogo (CONFIG config_usuario, SCORE *score_jogador)
{
    int velocidade_atual, pontuacao_jogador;
    int nivel;
    int perdeu = 1, venceu = 1, passou = 0;
    COBRA snake_jogador;
    char cenario[LINHAS][COLUNAS];

        clrscr();

        ///Definições iniciais padrão
        nivel = NIVEL1;
        score_jogador->pontuacao = 0;
        snake_jogador.tam_cobra = TAM_INICIAL_COBRA;
        velocidade_atual = config_usuario.vel_inicial;

        while (perdeu && venceu) /// Laço para passar pelos níveis
        {
            clrscr();
            exibe_logo_nivel(nivel);
            clrscr();
            desenha_cenario(cenario,nivel);
            iteracao_snake(snake_jogador,cenario, score_jogador, config_usuario, nivel, &perdeu, &passou);

            if (passou && nivel <= NIVEL2) /// Passa para o próximo nível e zera o booleano que controla se o jogador venceu o jogo
            {
                nivel++;
                passou = 0;
                score_jogador->pontuacao = score_jogador->pontuacao + BASE_SKIP; /// Soma os pontos por ter passado de nível
            }
            else
                if (nivel == NIVEL3 && passou == 1)
                {
                    venceu = 0;
                    score_jogador->pontuacao = score_jogador->pontuacao + BASE_SKIP;
                }
        }

        mensagem_final(venceu);
        total_pontos(*score_jogador);



}

void pega_nome_jogador (SCORE *score_jogador)
{
    char nome_auxiliar[TAM1];
    int tamanho;

        do
            {
                clrscr();
                textcolor(YELLOW);
                printf("\n\n\n\n\n\n \t\t DIGITE TRES LETRAS DO SEU NOME \n\n \t\t\t\t");
                textcolor(LIGHTGRAY);
                strupr(gets (nome_auxiliar));
                tamanho = strlen(nome_auxiliar);

                if (tamanho > TAM_JOGADOR - 1)
                {
                    textcolor(YELLOW);
                    printf("\t\t\n\n Nome excede o limite de tres letras");
                    getch();
                }
                else
                    if (tamanho < TAM_JOGADOR - 1)
                {
                    {
                    textcolor(YELLOW);
                    printf("\t\t\n\n Nome tem menos letras do que a pedida");
                    getch();
                    }
                }
            } while (tamanho > TAM_JOGADOR - 1 || tamanho < TAM_JOGADOR - 1);

            ///Se saiu do laço, o nome está no tamanho certo
            strcpy(score_jogador->nome_jogador, nome_auxiliar);
}


void ordena_score (int posicao_jogador, SCORE score_jogador, SCORE score_atual[])
{
    SCORE score_auxiliar1, score_auxiliar2;
    int ind_score;

        ///Passa o score do jogador para a posição ocupada
        strcpy(score_auxiliar1.nome_jogador,score_atual[posicao_jogador].nome_jogador);
        score_auxiliar1.pontuacao = score_atual[posicao_jogador].pontuacao;

        strcpy(score_atual[posicao_jogador].nome_jogador,score_jogador.nome_jogador);
        score_atual[posicao_jogador].pontuacao = score_jogador.pontuacao;


        ///Ordena o restante o arranjo
          posicao_jogador = posicao_jogador + 1; //Avança uma posição no arranjo

          if (posicao_jogador < TAM_SCORE ) // Teste para verificar se o jogador já não está na última posição do array
          {
                for (ind_score = posicao_jogador; ind_score < TAM_SCORE; ind_score ++)
                {
                    strcpy(score_auxiliar2.nome_jogador, score_atual[ind_score].nome_jogador);
                    score_auxiliar2.pontuacao = score_atual[ind_score].pontuacao;

                    strcpy(score_atual[ind_score].nome_jogador,score_auxiliar1.nome_jogador);
                    score_atual[ind_score].pontuacao = score_auxiliar1.pontuacao;

                    strcpy(score_auxiliar1.nome_jogador,score_auxiliar2.nome_jogador);
                    score_auxiliar1.pontuacao = score_auxiliar2.pontuacao;
                }
          }
}

void ajusta_score (SCORE score_jogador, SCORE score_atual[])
{
    SCORE score_auxiliar;
    int ind_score = 0;
    int achou = 1;

        while (achou && ind_score < TAM_SCORE)
        {
            if (score_jogador.pontuacao >= score_atual[ind_score].pontuacao)
            {
                pega_nome_jogador(&score_jogador);
                ordena_score (ind_score, score_jogador,score_atual); /// Passa o índice atual como parâmetro inicial do índice que vai ordenar o arranjo
                achou = 0;
            }

            ind_score ++;
        }


}

void menu_principal(CONFIG *config_usuario, SCORE score_atual[])
{
   char tecla;
   int sair = 1, vai_ranking = 0; /// Sair do jogo e começar novo jogo
   char config_do_usuario[TAM1] = {"config_usuario"};  /// Nome onde guardarão as configurações do usuario
   SCORE score_jogador;

        while (sair)
        {
            clrscr();
            desenha_logo();
            gotoxy(30,10);
            textcolor(YELLOW);
            printf("(N)OVO JOGO \n\n \t\t\t     (R)ANKING \n\n \t\t\t     (O)PCOES \n\n \t\t\t     (A)JUDA \n\n \t\t\t     (C)REDITOS \n\n \t\t\t     (S)AIR");
            textcolor(LIGHTGRAY);

            tecla = getch();

            if (tecla != 'n' && tecla != 'r' && tecla != 'c' && tecla != 'o' && tecla != 's' && tecla != 'a')
                        clrscr();

            else
            {
                switch (tecla)
                {
                    case 'n':   novo_jogo(*config_usuario,&score_jogador);
                                ajusta_score(score_jogador,score_atual);
                                salva_score(score_atual);
                                exibe_score(score_atual);
                                break;

                    case 'r':   exibe_score(score_atual);
                                break;

                    case 'o':   opcoes(config_usuario);
                                salva_config(*config_usuario,config_do_usuario);
                                break;

                    case 'a':    ajuda();
                                break;

                    case 'c':    creditos();
                                break;

                    case 's':   sair = 0;
                                break;
                }
            }
        }
}

main()
{
    hidecursor();
    CONFIG config_inicial;
    SCORE score_inicial[TAM_SCORE];
    char config_padrao[TAM1]= {"config_usuario"};

        srand(time(0));
        carrega_score(score_inicial);

        carrega_config(&config_inicial,config_padrao);

        menu_principal(&config_inicial,score_inicial);


return 0;
}
