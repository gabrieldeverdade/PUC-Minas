#include <stdio.h>

/*
     Exercicio - Elabore um algoritmo que leia o código do candidado em um 
                 voto.
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main(void) 
{

//Declaração de variáveis
int voto1=0,voto2=0,voto3=0,voto4=0,voto5=0,voto6=0,voto,totalvotos=1;

//Estrutura de repetição
while (voto!=0)
  {
  
//Coleta de valores
printf("Digite o %d° voto: ",totalvotos);
scanf("%d",&voto);
    if (voto==0)
    {
      totalvotos--;
    }
    else
    {
      
//Condição dos votos
switch (voto)
  {
  case 1: 
    voto1 ++;
    break;
  case 2:
    voto2++;
    break;
  case 3:
    voto3 ++;
    break;
  case 4:
    voto4 ++;
    break;
  case 5:
    voto5 ++;
    break;
  case 6:
    voto6 ++;
    break; 
    }
    totalvotos ++;
      }}

//Exibe resultado
printf("\nO total de votos no candidato 1 foi %d", voto1);
printf("\nO total de votos no candidato 2 foi %d", voto2);
printf("\nO total de votos no candidato 3 foi %d", voto3);
printf("\nO total de votos no candidato 4 foi %d", voto4);
printf("\n\nO total de votos nulos foi %d", voto5);
printf("\nO total de votos brancos foi %d", voto6);
  }