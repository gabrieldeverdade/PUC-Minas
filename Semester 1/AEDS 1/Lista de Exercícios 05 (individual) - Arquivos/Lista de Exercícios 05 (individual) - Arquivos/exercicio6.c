#include <stdio.h>
/*
    Lista 5 - Arquivo
    Exercício 6 - Faça um programa que solicite ao usuário um 
                  número, em seguida, imprima na tela todos os 
                  seus divisores. Salve em um arquivo texto a soma 
                  total desses divisores
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */
int main(void) 
{
  FILE *somaarq;
  int soma=0;
  int n, i=0, divisores[9999],b;
  printf("Digite o número a ser dividido: ");
  scanf("%d",&n);

  for(b=n;b>0;b--)
    {
      if(n%b==0)
      {
        if(b!=1)
        {
          divisores[i]=b;
          printf("%d ",divisores[i]);
          i++;
        } 
        else
        {
          divisores[i]=b;
          printf("e %d ",divisores[i]);
        }
      }
    }
  
  printf("são os divisores de %d\n",n);
  
  for(b=0;b<=i;b++)
    {
      soma+=divisores[b];  
    }

  somaarq = fopen("somaarq.txt","w");
  fprintf(somaarq,"%d",soma);
  fclose(somaarq);
}