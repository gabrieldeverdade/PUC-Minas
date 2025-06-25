#include <stdio.h>

/*
     Lista Extra - Exercicio 5  (Texto)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

int main(void) {
  //variaveis
  int dia, mes, ano;
  char meses[12][20] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

  //ler data
  printf("Digite a data de nascimento (dd/mm/aaaa): ");
  scanf("%d/%d/%d", &dia, &mes, &ano);

  if(dia < 10) printf("0%d de %s de %d\n", dia, meses[mes-1], ano);
  else printf("%d de %s de %d\n", dia, meses[mes-1], ano);
  
  return 0;
}