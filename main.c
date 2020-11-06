/* 
Caio Mergulhao Montenegro - 120015018
Wemerson Silva Caxias da Costa - 120063485
Vitor Ferreira Nunes - 120034070
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Prototipos das funçoes */
int receberDificuldade(int tam, int qtdPares[]);
void criarMatriz(int dificuldade, char caracteres[9]);
void mostrarMatriz();
void lerCasas();
void atualizarMatriz(int lin1, int col1, int lin2, int col2);
void limpaTela();
void checaFim();
void mostraPontuacao();
void delay(int segundos);
int validaJogadas(int lin, int col);
int replayPartida();

/* Variaveis globais */
int matriz[4][4];
int linha, jogadas, acertos, running, qtdChar, dificuldade;

/* Main */
int main(void)
{
    do
    {
        char caracteres[9] = "!@#$%&*(";
        int qtdPares[3] = {4, 6, 8};
        jogadas = 0; acertos = 0, running = 1;
        dificuldade = receberDificuldade(3, qtdPares);
        criarMatriz(dificuldade, caracteres);
        while(running)
        {
            mostrarMatriz();
            lerCasas();
            delay(3);
            limpaTela();
            checaFim();
        }
    }while(replayPartida());
    
    
    return 0;
}

/* Funçoes */

/* a funçao recebe um vetor contendo a quantidade de pares em cada dificuldade
e o tamanho do vetor. Ela escreve no console as dificuldades e recebe
a escolhida pelo usuario, dps retorna a quantidade de pares da dificuldade
escolhida. */
int receberDificuldade(int tam, int qtdPares[])
{
    int i, dificuldade;
    for(i=0; i<tam; i++)
    {
        printf("Dificuldade %d: %d pares.\n", i+1, qtdPares[i]);
    }
    while (1)
    {
        printf("Selecione a dificuldade:");
        scanf("%d", &dificuldade);
        if(dificuldade>0 && dificuldade<=tam) break;
        else printf("Dificuldade selecionada invalida.\n");
    }
    limpaTela();
    return dificuldade;
}

/* A função define os caracteres aleatoriamente da matriz de acordo
com a dificuldade. */
void criarMatriz(int dificuldade, char caracteres[9])
{
    int i, j, linAleatoria, colAleatoria, count;
    qtdChar = 4 + (dificuldade-1)*2;
    linha = dificuldade+1;
    srand(time(0));
    for(i=0; i<linha; i++)
        for(j=0; j<4; j++) matriz[i][j] = 0;
    for(i=0; i<qtdChar; i++)
    {
        count = 0;
        while(1)
        {
            linAleatoria = rand()%linha;
            colAleatoria = rand()%4;
            if(matriz[linAleatoria][colAleatoria] == 0)
            {
                matriz[linAleatoria][colAleatoria] = caracteres[i];
                count++;
            }
            if(count == 2) break;
        }
    }
}

/* A funçao mostra a matriz com ? substituindo os caracteres que fazem
parte do jogo da memoria (como se ela estivesse no escuro) */
void mostrarMatriz()
{
    int i,j;
    mostraPontuacao();
    for (i=0;i<linha;i++)
    {
        if (i==0)
            printf ("   1  2  3  4\n");
        printf ("%d ", i+1);
        for (j=0;j<4;j++)
        {
            if(matriz[i][j])
                printf ("[?]");
            else printf("   ");
        }
        printf("\n");
    }
}

/* A funçao le as o par de casas que o usuario escolher e mostra o caracter
escondido nas casas escolhidas, alem de checar se eh um par de caracteres iguais */
void lerCasas()
{
    int i, j , lin1, col1, lin2, col2;
    do
    {
    printf ("Insira a casa que quer revelar no formato: LINHA,COLUNA: ");
    scanf("%d,%d", &lin1, &col1);
    } while(validaJogadas(lin1, col1));
    limpaTela();
    mostraPontuacao();
    lin1--; col1--;
    for (i=0;i<linha;i++)
    {
        if (i==0)
            printf ("   1  2  3  4\n");
        printf ("%d ", i+1);
        for (j=0;j<4;j++)
        {
            if(i == lin1 && j == col1)
                printf("[%c]", matriz[i][j]);
            else if(matriz[i][j])
                printf ("[?]");
            else printf("   ");
        }
        printf("\n");
    }
    do
    {
        do 
        {
            printf ("Insira a segunda casa que quer revelar no formato: LINHA,COLUNA: ");
            scanf("%d,%d", &lin2, &col2);
        }while(lin2 == lin1+1 && col2 == col1+1);
    } while(validaJogadas(lin2, col2));
    jogadas++;
    limpaTela();
    mostraPontuacao();
    lin2--; col2--;
    for (i=0;i<linha;i++)
    {
        if (i==0)
            printf ("   1  2  3  4\n");
        printf ("%d ", i+1);
        for (j=0;j<4;j++)
        {
            if((i == lin1 && j == col1) || (i == lin2 && j == col2))
                printf("[%c]", matriz[i][j]);
            else if(matriz[i][j])
                printf ("[?]");
            else printf("   ");
        }
        printf("\n");
    }
    if (matriz[lin1][col1] == matriz[lin2][col2])
    {
        atualizarMatriz(lin1,col1,lin2,col2);
        acertos++;
	}
}

/* A funçao atribui o valor 0 aos pares que o jogador acertou */
void atualizarMatriz(int lin1, int col1, int lin2, int col2)
{
	matriz[lin1][col1] = 0;
	matriz[lin2][col2] = 0;
}

/* A funçao da um clear no console indepente do SO */
void limpaTela()
{
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #endif    
}

/* A funcao checa se o jogador chegou ao fim da partida e exibe
seu resultado */ 
void checaFim()
{
    if(acertos == qtdChar)
    {
    running = 0;
    limpaTela();
    printf("Parabens!!!!\nVoce concluiu a dificuldade %d com %d jogadas.\n", dificuldade, jogadas);
    } 
}

/* Mosta os dados da partida, como se fosse uma HUD */
void mostraPontuacao()
{
    printf("Jogadas: %d  Acertos: %d  Dificuldade: %d\n", jogadas, acertos, dificuldade);
}

/* A funcao cria um delay */
void delay(int segundos)
{
    int tempFinal = time(0) + segundos;
    while(time(0)<tempFinal);
}

/* A funca checa se a casa escolhida é valida */
int validaJogadas(int lin, int col)
{
    if(lin > linha || col > 4)
    {
        printf("Jogada invalida\n\n");
        return 1;
    }
    else if(matriz[lin-1][col-1] == 0)
    {
        printf("Jogada invalida\n\n");
        return 1;
    }
    else return 0;
}

/* A funcao checa se o jogador gostaria de jogar outra partida */
int replayPartida()
{
    char c;
    fflush(stdin);
    delay(3);
    limpaTela();
    printf("Deseja jogar outra partida? s/n: ");
    scanf(" %c", &c);
    if(c == 's' || c == 'S') return 1;
    else return 0;
}