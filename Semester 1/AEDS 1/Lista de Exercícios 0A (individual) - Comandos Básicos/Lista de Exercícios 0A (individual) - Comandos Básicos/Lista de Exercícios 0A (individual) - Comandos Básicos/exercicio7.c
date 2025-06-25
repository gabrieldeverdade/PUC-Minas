#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler a razão e o primeiro termo de uma 
                   PG e exibir o seu quinto termo.
    Data: 01/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  int i, ini, termos, prog;
  printf("Leitura de razão e exibição do seu 5 termo!");
  printf("\n\nInforme o primeiro termo e a razão da PG: ");
  scanf("%i %i %i", &ini, &termos, &prog);

  printf("\nResultado: ");//Exibe resultado
  for (i=0; i < termos; i++)//Exibição da progressão
    {
    printf("%i ", ini);
    ini = ini * prog; //Calcula PG
    //ini = ini + prog; //Calcula PA
  }
  return 0;
}