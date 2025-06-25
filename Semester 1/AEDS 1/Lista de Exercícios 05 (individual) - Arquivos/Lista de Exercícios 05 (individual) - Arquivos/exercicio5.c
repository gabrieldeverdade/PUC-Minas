#include <stdio.h>
/*
    Lista 5 - Arquivo
    Exercício 5 - Escreva um programa que concatene o conteúdo  de                   dois arquivos. O conteúdo dos dois arquivos 
                  deverá ser adicionado em um terceiro arquivo
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */
int main(void) 
{
  FILE *mistura;
  FILE *arq1;
  FILE *arq2;
  char texto1[100],texto2[100];
  arq1=fopen("arquivo1.txt","a");
  arq2=fopen("arquivo2.txt","a");
  mistura = fopen("mistura.txt","a");

  fgets(texto1,100,arq1);
  fprintf(mistura,"%s\n",texto1);

  fgets(texto2,100,arq2);
  fprintf(mistura,"%s",texto2);

  fclose(mistura);
}