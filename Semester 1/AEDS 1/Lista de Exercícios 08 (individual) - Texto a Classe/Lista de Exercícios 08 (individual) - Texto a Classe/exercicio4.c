#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
     Lista Extra - Exercicio 4  (Texto)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

int main(void) {
  //variaveis
  char texto[100], formatado[100];
  int pos = 0;
  bool espaco = false;

  printf("Digite um texto: ");
  scanf("%[^\n]", texto);

  //analisar composição do texto e quantidade de espaços
  //transferir caracteres validos para outro vetor
  for(int i = 0; i < strlen(texto); i++)
    {
      if(texto[i] == ' ')
      {
        if(espaco == false)
        {
          formatado[pos] = texto[i];
          pos++;
          espaco = true;
        }
      }
      else
      {
        espaco = false;
        formatado[pos] = texto[i];
        pos++;
      }
    }

  printf("Frase corrigida:\n  %s \n", formatado);
  
  return 0;
}