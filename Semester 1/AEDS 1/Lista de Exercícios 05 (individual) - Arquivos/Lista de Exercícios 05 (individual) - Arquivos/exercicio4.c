#include <stdio.h>
/*
    Lista 5 - Arquivo
    Exercício 4 - implemente um programa que leia um arquivo texto 
                  e imprima, linha a linha, o seu conteúdo na 
                  tela. Imprima também a quantidade de linhas que 
                  este arquivo possui.  
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */
int main(void) 
{
  FILE *arquivo;
  int i=0;
  char conteudo[100];
  arquivo=fopen("texto.txt","r");
 
  while (!feof(arquivo))
    {
      fgets(conteudo,100,arquivo);
      printf("%s",conteudo);
      i++;
    }
  if (i==1)
  printf("\nO arquivo possui %d linha\n",i);
  else
  {
    printf("\nO arquivo possui %d linhas\n",i);
  }
  fclose(arquivo);
}