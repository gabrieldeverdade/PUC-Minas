#include <stdio.h>
/* 
     Exercicio -  fazer uma função que recebe um valor inteiro e 
                  verifica se o valor é positivo ou negativo. Deve ser 
                  feito com true ou false. Lê N numeros e para cada um 
                  deles exibe uma msg informando se é positivo ou não
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */

//módulo
int leitorsinal (valor)
{

//declaração de variável
int numa;

//condição para verificar o núm
if (valor < 0)
{
 numa=0;
}
else if (valor == 0)
{
  numa=2;
}
  else
{
  numa=1;
}
  return (numa);
  }


int main(void) 
{
//declaração de variáveis
 int num,a=1,resultado; 

//estrutura repetição, verifica números e verificar se o 0 foi digitado
while (a>=1)
  {
    printf("Digite o número %d: ",a);
    scanf("%d",&num);

//Enviar pro módulo
resultado = leitorsinal(num);

if (resultado==0)
{
  printf("O número é negativo\n");
  a++;
    }
 else if (resultado==2)
 {
   printf("Fim do programa\n");
    a=0;
 }
  else if (resultado ==1)
 {
  printf("O número é positivo\n");
  a++;
  }
 }
}
  