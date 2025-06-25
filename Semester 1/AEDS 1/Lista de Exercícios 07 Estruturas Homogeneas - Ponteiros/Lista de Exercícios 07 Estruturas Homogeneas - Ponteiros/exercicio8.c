#include <stdio.h>

/*
    Exercício 8 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */
void imprimeAlfabeto(char *c){
  char aux='A';
  for(int i=0;i<26;i++){
    c[i]=aux;
    printf("%c ",c[i]);
    aux++;
  }
}

int main(void) {
  char c[26];
  imprimeAlfabeto(c);
}