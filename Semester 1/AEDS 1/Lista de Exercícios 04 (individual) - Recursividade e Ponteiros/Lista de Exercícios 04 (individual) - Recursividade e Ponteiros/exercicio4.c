#include <stdio.h>
/*
     Exercicio - Faça uma função recursiva que calcula o resto da divisão 
                 usando subtrações sucessivas: int resto (int numerador, int 
                 denominador). Faça  um  programa  principal  que  leia  
                 dois  números,  acione  a  função  e  exiba  o  resultado 
                 gerado. 
     Autor: Gabriel Azevedo Fernandes
     Data: 15/10/2022
  */

//Declaração de variáveis
int resto(int nume, int denomi)
{
  //condições e recursão
  if (nume/denomi == 0)
  {
    return (nume);
  } 
  else 
  {
    return (resto(nume - denomi,denomi));
  }
}

//leitura de valores e exibe resultado
int main(void) 
{
  int nume, denomi;
  printf("Informe o numerador e o denominador respectivamente: ");
  scanf("%d %d", &nume, &denomi);
  printf("O resto da divisão é %d\n", resto(nume, denomi));
}