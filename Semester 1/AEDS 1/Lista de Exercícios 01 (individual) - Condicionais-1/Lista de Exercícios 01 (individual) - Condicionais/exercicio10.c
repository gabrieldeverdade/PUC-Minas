#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Leia a velocidade máxima permitida em uma avenida e a 
                   velocidade com que o motorista estava dirigindo nela. Se o 
                   motorista estiver dentro do limite de velocidade, imprima a 
                   mensagem "Motorista respeitou a lei". Se o motorista tiver 
                   ultrapassado a velocidade máxima permitida, calcule e imprima 
                   o valor da multa a ser cobrada.
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  float veloci_max, veloci_motor, multa, diferenca_v;

  //Leitura dos dados
  printf("Informe a velocidade máxima permitida: ");
  scanf("%f", &veloci_max);
  printf("Informe a velocidade do motorista: ");
  scanf("%f", &veloci_motor);

  //Condições, calculo + exibe resultado
  if (veloci_motor > veloci_max)
  {
    diferenca_v = veloci_motor - veloci_max;
    if (diferenca_v <= 10)
    {
      multa = 50;
    }
    else if (diferenca_v <= 30 && diferenca_v >= 11)
    {
      multa = 100;
    }
    else
    {
      multa = 200;
    }
    printf("\n\nA multa é de R$%.2lf\n", multa);
  }
  else
  {
    printf("\nO Motorista Respeitou a Lei!\n");
  }
  
  return 0;
}