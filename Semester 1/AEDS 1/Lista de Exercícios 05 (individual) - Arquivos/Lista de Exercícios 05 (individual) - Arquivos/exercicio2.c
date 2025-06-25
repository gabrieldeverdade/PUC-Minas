#include <stdio.h>
#include <stdlib.h>
/*
    Lista 5 - Arquivo
    Exercício 2 - Crie um programa que receba um texto do usuário 
                  e grave o texto em um arquivo
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */

int main(void) 
{
  FILE *entrada;
  char texto[100];

  entrada = fopen("entrada.txt","w");
  fgets(texto,100,stdin);
  fprintf(entrada,"%s",texto);
  fclose(entrada);
}