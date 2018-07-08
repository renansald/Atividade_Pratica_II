/*
* CSI030-2018-01 - Programacao de Computadores I
* Nome........: Renan Saldanha Linhares
* Matricula...: 18.1.5908
* Curso.......: Engenharia de Computação
* Exercicio...: exercicio 01 / Atividade Pratica 2
*/

// Bibliotecas
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Geração das embarcações e locais no  campo de batalha*/
void campo(char mat[15][16]){
  int l, c;
  for(int a = 0; a <= 80; a++){
    l = rand ()% 15 + 0;
    c = rand ()% 15 + 0;
    if ((a <= 40) && (mat[l][c] != '@')){ //Gera os submarinos, que tem a unica condição que é a posição ja não ter um submarino
      mat[l][c] = '@';}
    else if ((a > 40) && (mat[l][c] != '@') && (mat[l][c+1] != '@') && (mat[l][c] != '$') && (mat[l][c+1] != '$' ) && (mat[l][c+2] != '$') && (mat[l][c-1] != '$') && (c <= 13)){ //Gera os porta avioes, que tem como condição na posiçao sorteada não ter nem o simbolo de submarino e nem o de porta avioes, assim como a proxima posição e 2 posições a frente do lugar sorteado não pode existir um submarino
      mat[l][c] = mat [l][c+1] = '$';}
    else{
      a--;}
  }
}

/*Atribuir espaços no campo a ser apresentado durante o jogo*/
void espaco(char mat[15][16]){
for (int a = 0; a < 15; a++){
    for (int b = 0; b < 16; b++){
        mat[a][b] = ' ';}
}
}

/*Imprimir o campo na tela*/
void imprimi(char mat[15][16],  char j[]){
printf("\n\n\t    Campo de %s\n", j); //Para informar de quem é o cmapo impresso
printf ("   A B C D E F G H I J K L M N O\n"); //Informa as colunas
  for(int a = 0; a < 15; a++){
    if (a < 9){ //Adiciona o digito zero antes do numero qundo o numero é composto de um digito apenas, para formatar a tabela
        printf("0%d ", a+1);}
    else{
    printf("%d ", a+1);}
    for(int b = 0; b < 16; b++){
        printf ("%c ", mat[a][b]);}
    printf("\n");}
}

/*Geração dos tiros, e informacaão se acertou embarcação ou não*/
void tiro(char mat[15][16], int l, char c, char mat2[15][16]){
int j;
if ((c == 'A') || (c == 'a')){ //Estrutura para transformar os caracters da coluna em numeros inteiros
    j = 0;}
else if ((c == 'B') || (c == 'b')){
    j = 1;}
else if ((c == 'C') || (c == 'c')){
    j = 2;}
else if ((c == 'D') || (c == 'd')){
    j = 3;}
else if ((c == 'E') || (c == 'e')){
    j = 4;}
else if ((c == 'F') || (c == 'f')){
    j = 5;}
else if ((c == 'G') || (c == 'g')){
    j = 6;}
else if ((c == 'H') || (c == 'h')){
    j = 7;}
else if ((c == 'I') || (c == 'i')){
    j = 8;}
else if ((c == 'J') || (c == 'j')){
    j = 9;}
else if ((c == 'K') || (c == 'k')){
    j = 10;}
else if ((c == 'L') || (c == 'l')){
    j = 11;}
else if ((c == 'M') || (c == 'm')){
    j = 12;}
else if ((c == 'N') || (c == 'n')){
    j = 13;}
else if ((c == 'O') || (c == 'o')){
    j = 14;}

if (mat2[l-1][j] == '@'){ //Estrutura de teste, se o local que o jogar atirou tiver um submarino, no local do submarino receberá um *
        mat[l-1][j] = '*';}
else if ((mat2[l-1][j] == '$') && (mat2[l-1][j+1] == '$')){ //Caso tenha acertado a primeira coluna do porta avioes vai adiciona o * nela e na proxima
        mat[l-1][j] = mat[l-1][j+ 1] = '*';}
else if ((mat2[l-1][j]== '$') && (mat2[l-1][j-1] == '$')){ //Caso tenha acertado a segunda coluna do porta avioes vai adiciona o * nela e na anterior
            mat[l-1][j] = mat[l-1][j-1] = '*';}
else {
        mat[l-1][j] = '~';} //Caso não tenha acertado nem o submarino e nem o porta avioes
}

/*Contagem de Pontos*/
int pontos (char mat[15][16]){
int cont = 0;
for(int a = 0; a < 15; a++){  //Como cada asterisco valem 100 pontos, é contado os asteriscos no campo do adversario e somado aos pontos
    for(int b = 0; b < 16; b++){
        if(mat[a][b] == '*'){
            cont = cont+100;}
}
}
return cont;
}

/*Imprimi Campo final*/
void Imprimir_resposta(char mat[15][16], char mat1[15][16], char j[]){  //Estrutura que imprime o campo de cada jogador, mostrando as embarções atingidas, as embarcações não atingidas e suas posições e os tiros na agua
printf("\n\n\t    Campo de %s\n", j);
printf ("   A B C D E F G H I J K L M N O\n");
  for(int a = 0; a < 15; a++){
    if (a < 9){
        printf("0%d ", a+1);}
    else{
    printf("%d ", a+1);}
    for(int b = 0; b < 16; b++){
    if (mat1[a][b] == '*'){
        mat[a][b] = '*';}
    else if (mat1[a][b] == '~'){
        mat[a][b] = '~';}
  printf ("%c ", mat[a][b]);}
printf ("\n");}
}


/*Função princiapal*/
int main(int argc, char const *argv[]) {
  int ptsJ1, ptsJ2, rodada, linha;
  char j1[51], j2[51], matriz1[15][16], matriz2[15][16], CampoJ1[15][16], CampoJ2[15][16], coluna, reseta, reseta2;
  srand (time(NULL));
  do{ //Função para reiniciar o jogo a partir desse ponto, caso sejam jogadores diferente
  printf ("\t\t\t Regras:\n* Existem dois campos de batalha, um do jogador 1 e um do jogador 2;\n* Cada campo possui 80 embarcacoes, sendo 40 submarinos e 40 porta avioes;\n* As embarcacoes sao definas da seguinte maneira:\n\t- @ equivale a um submarino, que vale 100 pontos;\n\t- $$ equivale a um porta avioes, que vale 200 pontos;\n\t- * equivale a embarcacao destruida;\n\t- ~ equivale a tiro na agua.\n* Cada jogador tera um total de 3 jogadas alternadas entre eles;\n* Para escolher o local a ser atacado o jogador deve infomar um numero, quando solicitado a linha ser atacada, e uma letra, quando solicitado a coluna a ser atacada, exemplo linha 2 coluna f, isso significa que o ataque acontecera na posica 2f;\n* O jogador que fizer mais pontos ao final do jogo vence.");
  printf("\n\nInforme o nome do Jogador 1: ");
  scanf (" %[^\n]s", j1);
  printf("Informe o nome do Jogador 2: ");
  scanf (" %[^\n]s", j2);
  do{ //Função para reiniciar o jogo, caso sejam os mesmos jogadores
  espaco(matriz1);
  espaco(matriz2);
  espaco(CampoJ1);
  espaco (CampoJ2);
  campo(matriz1);
  campo(matriz2);
  imprimi(matriz1, j1);//tirar
  imprimi(matriz2, j2);//tirar
  imprimi(CampoJ1, j1);
  imprimi(CampoJ2, j2);

  for(int a = 1; a < 4; a++){ //Estrutura para contar as rodadas
        printf("\t\t\tRodada %d\n", a);
   for(rodada = 1; rodada < 3; rodada++){ //Estrutura para fazer a jogada de cada jogador
    if (rodada%2 != 0){
    printf ("\n\n%s Informe a linha a ser atacada: ", j1);
    scanf ("%d", &linha);
    printf ("\n\n%s Informe a coluna a ser atacada: ", j1);
    scanf(" %c", &coluna);
    if ((linha <= 15) && (linha >= 1) && ((coluna == 'a') || (coluna == 'A') || (coluna == 'b') || (coluna == 'B') || (coluna == 'c') || (coluna == 'C') || (coluna == 'd') || (coluna == 'D') || (coluna == 'e') || (coluna == 'E') || (coluna == 'f') || (coluna == 'F') || (coluna == 'g') || (coluna == 'G') || (coluna == 'h') || (coluna == 'H') || (coluna == 'i') || (coluna == 'I') || (coluna == 'j') || (coluna == 'J') || (coluna == 'k') || (coluna == 'K') || (coluna == 'l') || (coluna == 'L') || (coluna == 'm') || (coluna == 'M') || (coluna == 'n') || (coluna == 'N') || (coluna == 'o') || (coluna == 'O'))){ //Estrutura para teste das condições de entrada
    tiro(CampoJ2, linha, coluna, matriz2);}
    else{
    printf ("\7Os numeros vao de \"1\" a \"15\" e as letras vao de \"a\" a \"o\". E a ordem deve ser sempre numero seguido de letra.\nPor favor %s repita sua jogada", j1);
    linha = -1;
    coluna = '\0';
    rodada--;
    continue;}}
    else{
    printf ("\n\n%s Informe a linha a ser atacada: ", j2);
    scanf ("%d", &linha);
    printf ("\n\n%s Informe a coluna a ser atacada: ", j2);
    scanf(" %c", &coluna);
    if ((linha <= 15) && (linha >= 1) && ((coluna == 'a') || (coluna == 'A') || (coluna == 'b') || (coluna == 'B') || (coluna == 'c') || (coluna == 'C') || (coluna == 'd') || (coluna == 'D') || (coluna == 'e') || (coluna == 'E') || (coluna == 'f') || (coluna == 'F') || (coluna == 'g') || (coluna == 'G') || (coluna == 'h') || (coluna == 'H') || (coluna == 'i') || (coluna == 'I') || (coluna == 'j') || (coluna == 'J') || (coluna == 'k') || (coluna == 'K') || (coluna == 'l') || (coluna == 'L') || (coluna == 'm') || (coluna == 'M') || (coluna == 'n') || (coluna == 'N') || (coluna == 'o') || (coluna == 'O'))){
    tiro(CampoJ1, linha, coluna, matriz1);}
    else{
    printf ("\7Os numeros vao de \"1\" a \"15\" e as letras vao de \"a\" a \"o\". E a ordem deve ser sempre numero seguido de letra.\nPor favor %s repita sua jogada", j2);
    linha = -1;
    coluna = '\0';
    rodada--;
    continue;}
    imprimi(CampoJ1, j1);
    imprimi (CampoJ2, j2);}
  }
  }
  printf ("\n\nA baixo segue a posicao das embarcacoes dos campos de cada jogador e as que foram abatidas e os tiros na agua.\n\n");
  Imprimir_resposta(matriz1, CampoJ1, j1);
  Imprimir_resposta(matriz2, CampoJ2, j2);
  printf("\nPontos:\n");
  ptsJ1 = pontos(CampoJ2);
  printf ("Pontos jogador %s: %d\n", j1, ptsJ1);
  ptsJ2 = pontos(CampoJ1);
  printf ("Pontos jogador %s: %d\n", j2, ptsJ2);
  if (ptsJ1 > ptsJ2){ //Estrutura para informar o vencedor ou empate
    printf ("Parabens %s voce venceu.\n", j1);}
  else if (ptsJ1< ptsJ2){
    printf ("Parabens %s voce venceu.\n", j2);}
  else{
    printf ("EMPATE\n");}
    printf ("Digite \"s\" para jogar novamente, ou \"n\" para sair do jogo: "); //estrutura para escolher novo jogo ou sair do game
    scanf(" %c", &reseta);
    if ((reseta == 's') || (reseta == 'S')){ //Estrutura para escolher se o novo jogo vai ser com os mesmo jogadores ou não
        printf ("Digite \"s\" caso sejam os mesmo jogadores, ou \"n\" caso sejam novos jogadores: ");
        scanf(" %c", &reseta2);
    }
    }while (((reseta == 's') || (reseta == 'S')) && ((reseta2 == 's') || (reseta2 == 'S')));
  }while((reseta == 's') || (reseta == 'S'));
  return 0;
}
