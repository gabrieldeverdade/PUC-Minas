#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler um número 
       inteiro de 3 dígitos no formato 
       CDU e invertê-lo para UDC.
    Data: 31/08/2022 
  */

int main(void) 
{
  //Declaração de variáveis
   int u, c, d, auxd, num, invertido;//valores CDU e UDC
    printf("Insira o numero que deseja inverter: ");
    scanf("%d",&num);

    //Cálculo dos valores a serem invertidos
    c = num/100; //calculo do primeiro valor
    auxd = num-(c*100);//calculo para copiar o primeiro valor e exibir
    d = auxd/10;//calculo para exibir o segundo valor
    u = num-((c*100)+(d*10));//cálculo para exibir o terceiro valor
    invertido = (u*100)+(d*10)+(c); //cálculo para inverter os valores

    //Exibe resultado
    printf("\nO número invertido é: %d",invertido);
  
  return 0;
}