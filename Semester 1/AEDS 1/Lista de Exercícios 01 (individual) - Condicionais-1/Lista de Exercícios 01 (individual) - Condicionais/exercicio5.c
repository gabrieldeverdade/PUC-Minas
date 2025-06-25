#include <stdio.h>
/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Um hotel com 75 aptos deseja fazer uma 
                   promoção especial de final de seman, 
                   concedendo um desconto de 25% na diária. 
                   Com isto, espera aumentar sua taxa de 
                   ocupação de 50 para 80%. Sendo dado o valo 
                   normal da diária, calcular e imprimir:    
                   A) O valor da diária promocional;         
                   B) O valor total arrecadado com 80% de 
                   ocupação e diária promocional;             
                   C) O valor arrecadado com 50% de ocupação e 
                   diária normal;                              
                   D) A diferença entre estes dois valores;
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  double diaria, promodia;

  //Informação sobre valores
  printf("Informe o valor da diária: R$");
  scanf("%lf", &diaria);

  //Exibição dos valores + pedidos de A a D (Exercício)
  promodia = diaria * 0.75;

  printf("\nO valor da diária com a promoção é: R$%.2lf\n", promodia);//questão A
  
  printf("\nO valor total arrecadado com os 60 apartamentos \nna diária promocional: R$%.2lf\n", promodia*60);//Questão B (75-80% = 60 apartamentos)
  
  printf ("\nO valor total arrecado com metade da ocupação \nna diária normal: R$%.2lf\n",diaria * 37.5);//Questão C
  
printf ("\n\nDiferença entre as arrecadações: R$ %.2lf",(promodia * 60) - (diaria * 37.5));//Questão D
  return 0;
}