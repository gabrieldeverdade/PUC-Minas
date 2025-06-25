#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Sabendo que 100 kilowatts custa um sétimo do 
                  salário mínimo, faça um algoritmo que receba o valo 
                  do salário mínimo e a quantidade de kilowatt fasta 
                  por uma residência, calcule e exiba: o valo em 
                  reais de cada kilowatt; o valor em reais a ser 
                  pago; e o novo valor a ser pago por essa residência 
                  com um desconto de 10%.
    Data: 31/08/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  int val_sal, qtd_kw, val_kw, val_reais, desc, val_desc;

  //Busca das informações
  printf("Informe o valor do salário mínimo: ");
  scanf("%d", &val_sal);
  printf("\nInforme a quantidade de kilowatts gasta: ");
  scanf("%d", &qtd_kw);

  val_kw = val_sal/7;//cálculo do valor de cada kilowatt por um sétimo do salário mínimo
  val_reais = val_kw * qtd_kw;//cálculo valor a ser pago em reais
  desc = val_reais * 10/100;//cálculo do valor a ser pago após 10% de desconto
  val_desc = val_reais - desc;//valor final após o desconto

  //Exibe resultado
  printf("\n\nO valor em reais de cada Kilowatt é: R$%d", val_kw);
  printf("\nValor em reais a ser pago é: R$%d", val_reais);
  printf("\nValor a ser pago após o de desconto: R$%d", val_desc);
  return 0;
}