#include <stdio.h>
#include <stdlib.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Ler o valor de hora e minuto, 
                   depois calcular e exibir quantos 
                   minutos se passaram desde o 
                   início do dia
    Data: 02/08/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  int horas,minutos;
  printf("Informe a hora e minuto separado por espaço: ");
  scanf("%d %d",&horas, &minutos);
  
  minutos=(horas*60 + minutos);//Calcúlo para conversão em minutos
  
  printf("Se passaram %d minutos desde o início do dia do dia até a hora atual\n",minutos);//Exibe resultado
  return 0;
}
