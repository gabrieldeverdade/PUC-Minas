#include <stdio.h>
/*
    Lista 5 - Arquivo
    Exercício 1 - Crie  um  programa  que  escreva  de  1  até  10                   em um arquivo, armazenando um número por linha.
    Autor - Gabriel Azevedo Fernandes
    Data - 05/11/2022
 */

int main(void) {

  FILE *entradaNum;

  entradaNum = fopen("numeros.txt", "w");
  
  for(int i=1; i<=10; i++)
    {
      fprintf(entradaNum, "%d\n", i);
    }
    fclose(entradaNum);
}