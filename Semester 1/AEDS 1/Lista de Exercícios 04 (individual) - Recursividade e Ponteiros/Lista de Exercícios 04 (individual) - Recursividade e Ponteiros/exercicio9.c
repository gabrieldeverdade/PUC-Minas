#include <stdio.h>
 /*
     Exercicio 9 (Ponteiro) - Escreva um programa em C que declare 
                              variáveis para armazenar um valor 
                              inteiro, um valor real  e  um  
                              caracter.  Deve  existir  no  
                              programa  ponteiros  associados  a  
                              cada  um  deles.  O programa deve 
                              solicitar novos dados para as 
                              variáveis e elas devem ser modificadas 
                              usando os respectivos ponteiros. Exiba 
                              os endereços e os conteúdos de todas 
                              as variáveis e ponteiros antes e após 
                              a alteração. 
     Autor: Gabriel Azevedo Fernandes
     Data: 16/10/2022
  */
int main(void) 
{
  int x,*px=&x;
  double y,*py=&y;
  char c,*pc=&c;
  x=1;
  y=5;
  c='f';
  printf("Antigos valores: \n\n");
  printf("O valor inteiro é %d e seu endereço é %p\n\nO valor do ponteiro do inteiro é %d e seu endereço é %p\n\nO valor real é %.2lf e seu endereço é %p\n\nO valor do ponteiro do real é %.2lf e seu endereço é %p\n\nO valor do caracter é %c e seu endereço é %p\n\nO valor do ponteiro do caracter é %c e seu endereço é %p\n\n",x,&x,*px,&px,y,&y,*py,&py,c,&c,*pc,&pc);

  printf("\nDigite o novo valor inteiro: ");
  scanf("%d",px);
  printf("Digite o novo valor real: ");
  scanf("%lf",py);
  printf("Digite o novo valor do caracter: ");
  scanf(" %c",pc);

  printf("\nNovos valores: \n\nO valor inteiro é %d e seu endereço é %p\nO valor do ponteiro do inteiro é %d e seu endereço é %p\nO valor real é %.2lf e seu endereço é %p\nO valor do ponteiro do real é %.2lf e seu endereço é %p\nO valor do caracter é %c e seu endereço é %p\nO valor do ponteiro do caracter é %c e seu endereço é %p\n",x,&x,*px,&px,y,&y,*py,&py,c,&c,*pc,&pc);
}