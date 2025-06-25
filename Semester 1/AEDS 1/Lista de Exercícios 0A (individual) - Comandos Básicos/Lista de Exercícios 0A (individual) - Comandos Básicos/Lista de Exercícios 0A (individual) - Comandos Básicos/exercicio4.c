#include <stdio.h>
#include<math.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler o raio de um círculo e 
                   exibir o seu perímetro e 
                   área.
    Data: 31/08/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  int raio, perimetro, area;

  printf("--Leitura do Raio de um circulo--\n\n");
  printf("Informe o valor do raio: ");
  scanf("%d", &raio);

  //Fórmulas para o cálculo da circunferência
  perimetro = 2*3.1415*raio;//Cálculo do perímetro
  area = 3.1415*pow(raio,2);//Cálculo da área (POW - Exponenciação)

  //Exibição de resultados
  printf("\n\n--Exibição de resultado--");
  printf("\n\nO PERÍMETRO é igual a: %d", perimetro);
  printf("\nA ÁREA é igual a: %d", area);
  
  return 0;
}