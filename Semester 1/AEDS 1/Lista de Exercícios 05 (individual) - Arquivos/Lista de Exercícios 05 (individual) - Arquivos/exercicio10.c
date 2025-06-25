#include <stdio.h>
#include <stdlib.h>
/*
    Lista 5 - Arquivo
    Exercício 10 - Considere um arquivo texto que armazene números 
                   em ponto flutuante em cada uma de suas 
                   linhas. Escreva um programa em C que determine 
                   o valor máximo, o valor mínimo e a média 
                   desses valores armazenados no arquivo. Imprima 
                   esses valores na tela
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */


int main(void)
{
  int N, min,max;
  double total=0;
  FILE *numeros;

  numeros = fopen("numeros.txt","w");
  
  printf("Informe o total de números que serão digitados: ");
  scanf("%d",&N);

  
  
  int num[N];

  
  
  for(int i=0;i<N;i++)
    {
      if(i==0)
      {
        printf("Informe o valor do primeiro número: ");
        scanf("%d",&num[i]);
        fprintf(numeros,"%d\n",num[i]);
        min=num[i];
        max=num[i];
        total+=num[i];
      }
      else
      {
        printf("Informe o valor do próximo número: ");
        scanf("%d",&num[i]);
        fprintf(numeros,"%d\n",num[i]);
        total+=num[i];
        if (num[i]<min)
        {
          min=num[i];
        }
        if (num[i]>max)
        {
          max=num[i];
        }
      }
    }
  fprintf(numeros,"Menor número: %d\n",min);
  fprintf(numeros,"Maior número: %d\n",max);
  fprintf(numeros,"Média geral: %.2lf\n",total/(N));
}