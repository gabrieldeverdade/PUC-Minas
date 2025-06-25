#include <stdio.h>
#include <string.h>

/*
     Lista Extra - Exercicio 6  (Texto)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

int verifica(char palavra[30], char palavraInvertida[30])
{
for(int i=0; i<strlen(palavra); i++)
{
    if(palavra[i]==palavraInvertida[i])
    {
      if (i==strlen(palavraInvertida-1))
      return 1;
    }
  else
  return 0;

}
 }
int main (void)
{
  char texto[30], texto2[30];
  int x=1;
  printf("Digite uma frase em letras minusculas: ");
  scanf(" %[^\n]", texto);
  for(int a=0; a<strlen(texto); a++)
  {
    texto2[a]= texto[strlen(texto)-x];
    x++;
  }
  texto2[strlen(texto)]='\0';
  if (verifica(texto, texto2)==1)
  {
    printf("É paralindromo\n");
    }
  else
    printf("Não é paralindromo\n");
}