#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/*
     Lista Extra - Exercicio 3  (Texto)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */


//procedimento comparação
int comparar(char texto[])
{
    //determinar conectores invalidos
  char conectores[8][4] = {"E", "DA", "DE", "DI", "DO", "DU", "DOS", "DAS"};
  int pos;
  bool igual = true;
  
  for(int i = 0; i < 8; i++)
    {
      pos = 0;
      igual = true;

      while(igual && pos < strlen(conectores[i]))
      {
        for(pos = 0; pos < strlen(conectores[i]); pos++)
        {
          if(texto[pos] != conectores[i][pos]) igual = false;
        }
      }
      if (igual == true && strlen(conectores[i]) == (strlen(texto) - 1)) return 1;
   }
  return 0;
}

int main(void) {
  char nome[100], abreviacao[20], parteNome[20];
  int a = 0, aux = 1;
  
  printf("Digite um nome: ");
  scanf("%[^\n]", nome);

  //abreviacao[0] = toupper(nome[0]);
  parteNome[0] = toupper(nome[0]);
  for (int i = 0; i < strlen(nome); i++)
    {
      //separar nomes por espaço
      if(nome[i] != ' ')
        {
          parteNome[aux] = toupper(nome[(i+1)]);
          aux++;
        }
      else if(nome[i] == ' ')
      {
        parteNome[aux] = '\0';
        aux = 0;
        //conferir se a parte do nome eh valida
        if(comparar(parteNome) == 0)
        {
          
          abreviacao[a] = parteNome[0];
          a++;
        }
        parteNome[aux] = toupper(nome[(i+1)]);
        aux++;
      }
    }
  abreviacao[a] = parteNome[0];
  
  //exibir abreviação
  printf("%s\n", abreviacao);

  return 0;
}