#include <stdio.h>
#include <math.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler base e altura de um 
                   retângulo e exibir --> 
                   perímetro, área e diagonal.
    Data: 31/08/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  int base, alt, peri, area, diag; //valores a serem lidos e resultados

  printf("Informe o valor da base do retângulo: ");
  scanf("%d", &base);
  printf("\nInforme o valor da altura do retângulo: ");
  scanf("%d", &alt);
  
  //Fórmula para o cálculo do retângulo
  peri = 2*(base+alt);//Cálculo do perímetro
  area = base*alt;//Cálculo da área
  diag = sqrt(pow(base,2)+pow(alt,2));
  //Cálculo da diagonal (SQRT<--Raiz quadrada)(POW<--Exponenciação)

  //Exibe resultado
  printf("\nO perímetro é igual a: %d", peri);
  printf("\nA área é igual a: %d", area);
  printf("\nA diagonal é igual a: %d", diag);
  
  return 0;
}