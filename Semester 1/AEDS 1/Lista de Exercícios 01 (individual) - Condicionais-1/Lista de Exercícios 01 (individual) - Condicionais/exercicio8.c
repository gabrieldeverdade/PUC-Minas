#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Construa um programa que lê uma opção conforme 
                   abaixo (Usar estrutura SWITCH) e o salário atual 
                   do funcionario, calcula e exibe o novo salário:  
                   A = aumento de 8% no salário;                   
                   B = aumento de 11% no salário;                 
                   C = aumento fixo no salário (de R$350,00 se o  
                   salário for até R$1000 e de R$200,00 se o salário 
                   atual for maior que R$1000);
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  char opcao;
  float sal_atu, sal_novo;

  //Leitura de Valores
  printf("Escolha a opção A, B ou C: ");
  scanf("%c", &opcao);

  //Leitura do salário atual
  printf("Informe o seu salário atual: R$");
  scanf("%f", &sal_atu);

  //Condições do exercício proposto
  switch (opcao)
    {
      case 'A': sal_novo = 1.08 * sal_atu; //Aumento de 8%
        break;
      case 'B': sal_novo = 1.11 * sal_atu; //Aumento de 11%
        break;
      case 'C': if (sal_atu > 1000)
      {
        sal_novo = sal_atu + 200;
      }
      else
      {
        sal_novo = sal_atu + 350;
      }
      break;
    }

  //Exibe resultado
  printf("O seu salário novo é: R$%.2lf\n", sal_novo);
  
  return 0;
}