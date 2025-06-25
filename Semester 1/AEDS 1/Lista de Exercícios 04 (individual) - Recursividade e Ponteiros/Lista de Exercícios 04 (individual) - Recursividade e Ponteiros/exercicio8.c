#include <stdio.h> 
 /*
     Exercicio 8 (Ponteiro) - Identificar o erro no código
     Autor: Gabriel Azevedo Fernandes
     Data: 16/10/2022
  */
int main() 
{ 
    int x, *p, **q; 
    p = &x; 
    q = &p; 
    x = 10; 
    printf("\n%d\n", **q); 
    return(0);  
} 
// o código tem um erro no printf, ele manda imprimir o endereço do q (&q). Para ele imprimir o valor 10 (valor de x) deve ser impresso o valor apontado pelo valor apontado pelo q. Logo, o printf deve ser printf("\n%d\n", **q);