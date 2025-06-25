#include <stdio.h>
/*
     Exercicio -  Fazer um procedimento que recebe 3 valores inteiros por 
                  parâmetro e os exiba em ordem crescente. Faça um programa 
                  que leia N conjuntos de 3 valores e acione o procedimento 
                  para cada conjunto. (N deve ser lido no teclado)
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */

//Módulo
void crescente(n1, n2,n3)
{
//Ordem crescente + Exibe na tela
if (n1 < n2 && n1 < n3)
{
  printf("%d ",n1);
  if (n2 < n3)
  {
    printf("%d %d\n",n2,n3);
  }
    
  else if (n3 < n2)
  {
    printf("%d %d\n",n3,n2);
  }
  
}
  
  else if (n2 < n1 && n2 < n3)
  {
    printf("%d ",n2);
    if(n1 < n3)
    {
      printf("%d %d\n",n1,n3);
    }
      
    else if (n3 < n1)
    {
      printf("%d %d\n",n3,n1);
    }
  }
    
  else if (n3 < n1 && n3 < n2)
  {
    printf("%d ",n3);
    if (n1 < n2)
    {
      printf("%d %d\n",n1,n2);
    }
      
    else if (n2 < n1)
    {
      printf("%d %d\n",n2,n1);
    }
  }
}

int main(void) 
{
  //Declaração de variável
  int N, num1, num2, num3, conj=1;

  printf("Digite o total de conjuntos desejado: ");
  scanf ("%d",&N);

  //Condição repetição confoem os conjuntos
  while(N >= 1)
  {
    printf("\nDigite os 3 números do conjunto %d: ",conj);
    scanf("%d %d %d",&num1,&num2,&num3);
 
   //Aciona módulo
   crescente(num1,num2,num3);
   N--;
   conj++;
  }
}