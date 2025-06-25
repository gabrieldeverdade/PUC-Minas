#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Fazer programa para:                           
                   Ler um símbolo do teclado  
                   Identificar com a estrutura SWITCH e mostrar as 
                   seguintes mensagens, segundo o caso:         
                   SINAL DE MENOR                               
                   SINAL DE MAIOR                               
                   SINAL DE IGUAL                               
                   OUTRO SINAL
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  char simbolo;

  //Leitura dos símbolos
  printf("Informe o símbolo: ");
  scanf("%c", &simbolo);

  //Condição + exibe resultado
  switch (simbolo)
    {
      case '<': printf("SINAL DE MENOR\n");
        break;
      case '>': printf("SINAL DE MAIOR\n");
        break;
      case '=': printf("SINAL DE IGUAL\n");
      break;
      default: printf("OUTRO SINAL\n");
      break;
    }
  
  return 0;
}