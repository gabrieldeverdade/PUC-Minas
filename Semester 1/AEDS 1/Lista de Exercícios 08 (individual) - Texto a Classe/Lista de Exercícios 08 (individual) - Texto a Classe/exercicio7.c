#include <stdio.h>
#include <string.h>

/*
     Lista Extra - Exercicio 7  (Texto)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

int main(void) 
{
  char V[100];
  printf("Digite seu texto que será criptografado: ");
  scanf(" %[^\n]",V);
  for(int i=0;i<strlen(V);i++)
    {
      if(V[i]!=32)
      V[i]+=3;
    }
  printf("%s",V);
  }