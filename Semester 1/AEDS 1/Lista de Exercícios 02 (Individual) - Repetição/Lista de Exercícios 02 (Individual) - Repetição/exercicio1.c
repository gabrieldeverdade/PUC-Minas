#include <stdio.h>

 /*
     Exercicio - Identificar sequência de valores positivos,
                 negativos e zeros
     Autor: Gabriel Azevedo Fernandes
     Data: 17/09/2022
  */
int main()
{
  //Declaração de variáveis
  int neg = 0, posi = 0, zero = 0, rep;

  //Informa valor
  printf("Informe o número de repetições: ");
  scanf("%d", &rep);

  //Condições repetição
  for (int i=0, n; i < rep; i++)
    {
      printf("Digite um número: ");
      scanf("%d", &n);

      //Identificação dos valores
      if (n < 0)
      {
        neg++;
      }
      if (n > 0)
      {
        posi++;
      }
      if ( n == 0)
      {
        zero++;
      }
    }

  //Exibe resultado
  printf("\n\nQuantidade de negativos: %d\n", neg);
  printf("Quantidade de positivos: %d\n", posi);
  printf("Quantidade de zeros: %d\n", zero);
  return 0;
}