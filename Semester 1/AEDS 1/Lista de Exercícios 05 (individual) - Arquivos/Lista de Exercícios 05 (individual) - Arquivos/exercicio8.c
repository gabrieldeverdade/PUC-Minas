#include <stdio.h>
/*
    Lista 5 - Arquivo
    Exercício 8 - Crie um programa que leia a quantidade de 
                  veículos que uma locadora de veículos possui e 
                  o valor que ela cobra por cada aluguel, 
                  mostrando as informações pedidas a seguir
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */
int main(void) 
{
  FILE *relatorio;
  double carros,aluguel;

  relatorio = fopen("resultado.txt","w");

  printf("Digite o total de carros da locadora: ");
  scanf("%lf",&carros);
  printf("Digite o valor do aluguel de cada carro: ");
  scanf("%lf",&aluguel);

  printf("\nO faturamento anual da locadora é R$ %.2lf\n",(((carros/3)*aluguel)*12));
  fprintf(relatorio,"O faturamento anual da locadora é R$ %.2lf\n",(((carros/3)*aluguel)*12));

  printf("O valor ganho com multas no mês é R$ %.2lf\n",(carros/30)*(0.2*aluguel));
  fprintf(relatorio,"O valor ganho com multas no mês é R$ %.2lf\n",(carros/30)*(0.2*aluguel));
  
  printf("O valor gasto com manutenção de veículos é R$ %.2lf\n",(0.02*carros)*(600));
  fprintf(relatorio,"O valor gasto com manutenção de veículos é R$ %.2lf",(0.02*carros)*(600));

  fclose(relatorio);
}