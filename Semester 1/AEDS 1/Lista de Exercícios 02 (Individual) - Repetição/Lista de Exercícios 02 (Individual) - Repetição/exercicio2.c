#include <stdio.h>

/*
     Exercicio - Calcular o percentual dos valores 
                 positivos, negativos e zeros
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main() 
{
  //Declaração de variáveis
  int neg = 0, posi = 0, zero = 0, rep, P, total;

  printf("Informe o número de repetições: ");
  scanf("%d", &rep);

  //Condições da repetição
  for (int i = 0, n; i < rep; i++)
    {
      printf("Digite um número: ");
      scanf("%d", &n);

      if (n < 0)
      {
        neg++;
      }
      if (n > 0)
      {
        posi++;
      }
      if (n == 0)
      {
        zero++;
      }
    }

  //Exibe resultado
  total = neg + posi + zero;
  
   P = (neg*100) / total;
  printf("\n\nPorcentagem de números negativos: %d%%\n",P);
  
  P = (posi*100) / total;
  printf("Porcentagem de números positivos: %d%%\n", P);
  
  P = (zero*100) / total;
  printf("Porcentagem de zeros: %d%%\n", zero);
  return 0;
}