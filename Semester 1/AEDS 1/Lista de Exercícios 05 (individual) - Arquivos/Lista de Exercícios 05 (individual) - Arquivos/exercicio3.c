#include <stdio.h>
#include <stdlib.h>
/*
    Lista 5 - Arquivo
    Exercício 3 - implemente um programa que abra o arquivo texto 
                  (criado no exercício anterior) e conte a 
                  quantidade de caracteres ‘a’ que estão presentes 
                  nele. Imprima a quantidade na tela. 
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */


int main(void) 
{
  int a=0;
  FILE *texto;
  int quantidade=0;
  char arquivo[100];

  texto = fopen("arquivotex.txt","r");
  
  fgets(arquivo,100,texto);

  while(arquivo[a]!='\0')
    {
      if (arquivo[a]=='a')
      {
        quantidade ++;
      }
      a++;
    }
  printf("Existem %d caracteres 'a' no arquivo\n",quantidade);
}