#include <stdio.h>
/*
    Trabalho IC em 5 Linguagens - Linguagem C 
    Autor - Gabriel Azevedo Fernandes
    Data - 12/06/2022
 */
int main(){
  int n, d, EhPrimo;
  d=2;
  EhPrimo = 1;

  //Solicita e mostra na tela do usuário o número dado pelo usuário 
  printf("Digite um número inteiro positivo: ");
  scanf("%d", &n);
  printf("\nInteiro dado = %d \n", n);

  //Verificar a quantidade de divisores do número
    if(n<=1)
    EhPrimo = 0;
  while(EhPrimo == 1 && d <= n/2){
    if(n % d == 0)
      EhPrimo = 0;
    d = d + 1;
  }
  //Informa o resultado
  if (EhPrimo == 1)
    printf("\n%d é primo \n", n);
  else
    printf("\n%d não é primo\n", n);
  return 0;
  }

