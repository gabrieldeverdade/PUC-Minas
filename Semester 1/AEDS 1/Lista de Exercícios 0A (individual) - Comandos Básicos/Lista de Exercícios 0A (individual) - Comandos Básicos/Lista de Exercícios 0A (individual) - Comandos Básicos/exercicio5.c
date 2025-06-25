#include <stdio.h>
#include <math.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler valores do cateto 
                   de um triângulo e 
                   exibir a hipotenusa
    Data: 31/08/2022 
  */

int main(void) 
{
  //Declaração de Variáveis
  int cat_op, cat_ad, hip;

  printf("\tCálculo da Hipotenusa");
  printf("\n\nInforme o valor do cateto oposto: ");
  scanf("%d", &cat_op);
  printf("Informe o valor do cateto adjascente: ");
  scanf("%d", &cat_ad);

  hip = sqrt(pow(cat_op,2)+pow(cat_ad,2)); //TEOREMA DE PITÁGORAS

  //Exibição de resultados
  printf("\n\tResultado");
  printf("\n\nA hipotenusa é igual a: %d", hip);
  return 0;
}