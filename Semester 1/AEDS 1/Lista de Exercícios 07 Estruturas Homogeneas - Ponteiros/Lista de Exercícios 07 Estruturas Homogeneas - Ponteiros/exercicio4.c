#include <stdio.h>
#include <stdbool.h>

/*
    Exercício 4 
    Autor - Gabriel Azevedo Fernandes
    Data - 27/11/2022
 */
bool checkVogal(char c){
  return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

int main(void) {
  char str[1000];
  int vogal=0,cons=0;
  printf("String de entrada: ");
  scanf("%s",str);
  for(int i=0;str[i]!='\0';i++){
    if(checkVogal(str[i])){
      vogal++;
    }
    else{
      cons++;
    }
  }
  printf("Número de vogais: %d\n",vogal);
  printf("Número de consoantes: %d\n",cons);
}