#include <stdio.h>

/*
     Exercicio - Um comerciante deseja fazer o levantamento do lucro das 
                 mercadorias que ele comercializa. Para isto, mandou digitar uma 
                 linha para cada mercadoria com o preço de compra e de venda de 
                 cada um 
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main(void) 
{
//Declaração de variáveis
int mercadoria = 1, totalcompra, totalvenda, totallucro, lucro, lucro1 =0 ;
double lucro2 = 0, lucro3 = 0, compra, venda;


//Condição e estrutura da repetição
while (compra != 0)
  {

 //Coleta dos valores
printf("Informe o valor de compra e venda da mercadoria %d: ",mercadoria);
scanf("%lf %lf",&compra, &venda);
    if (compra == 0)
    {
      mercadoria--;
    }
    else
    {
  lucro = venda - compra;
    if (lucro<0.1*compra)
    {
      lucro1++;
    }
    else if (lucro >= 0.1*compra && lucro <=0.2*compra)
    {
      lucro2++;
    }
    else if (lucro >0.2*compra)
    {
      lucro3++;
    }
    totalcompra = totalcompra + compra;
    totalvenda = totalvenda + venda;
    totallucro = totallucro + lucro;
    mercadoria++;
    }}

//Exibição dos valores

printf("\nO número de mercadorias que propiciaram um lucro inferior a 10 por cento foi %d", lucro1);
  
printf("\nO número de mercadorias que propiciaram um lucro entre 10 por cento e 20 por cento foi %.0lf", lucro2);
  
printf("\nO número de mercadorias que propiciaram um lucro superior a 20 por cento foi %.0lf", lucro3);
  
printf("\n\nValor total de compras: R$%d", totalcompra);
  
printf("\nValor total de vendas: R$%d", totalvenda);
  
printf("\nO lucro total foi R$ %d", totallucro);


  
    }