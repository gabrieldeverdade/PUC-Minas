#include <stdio.h>

  /*
     Exercicio - verificar números divisíveis po 3, 9, 5 e 2
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main()
{
  //Declaração de variáveis
  int num, forTwo = 0, forNine = 0, forFive = 0, i = 0;

  //Identificador de valores + condições
  do {
    printf("Informe o %dº número: ", i+1);
    scanf("%d", &num);

    forFive += num % 5 == 0 && num;
    forTwo += num % 2 == 0 && num;
    forNine += num % 9 == 0 && num;

    if (num % 5 && num % 9 && num % 2 || num == 0)
    {
      printf("\nNúmero indivisível pelos valores\n");
    }
    i++;
  }
    while (i < 5);
  
  //Exibe resultado
  printf("Quantidade de números divisíveis por 2: %d", forTwo );
  printf("Quantidade de números divisíveis por 3 e 9: %d", forNine);
  printf("Quantidade de números divisíveis por 5: %d", forFive);
  return 0;
}