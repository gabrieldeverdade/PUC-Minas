#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Receber 2 números reais e salvá-los 
                   nas variáveis A e B. Fazer com que os 
                   valores troquem, A=B e B=A. Exibir os 
                   valores finais.
    Data: 01/08/2022 
  */
int main(void) 
{
  //Declaração das variáveis
  float a, b, c;//valores a serem lidos
  printf("Informe o valor de A: ");
  scanf("%f", &a);
  printf("Informe o valor de B: ");
  scanf("%f", &b);

  printf("\nValor de A e B na ordem original!\nA:%f\nB:%f",a,b);

  //Troca do valor das variáveis
  c = a; //faz uma copia do A no C
  a=b;//copia o B no A
  b = c;//copia o C no B
  
  //Exibição das variáveis inversas
  printf("\n\nValor de A e B trocados!\nA:%f\nB:%f",a,b);
 
  return 0;
}