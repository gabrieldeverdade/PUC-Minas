#include <stdio.h>

/* 
     Exercicio -  escrever um procedimento que receba 3 valores reais e 
                  verifique se os comprimentos dos lados de um triangulo + 
                  exibir o tipo de triângulo formado.
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */

//Módulo para verificar triângulo

void triangulo(double X,double Y,double Z)
{
 {
    //Condição + exibe na tela
    if(X<Y+Z && Y<X+Z && Z<X+Y)
   {
     if (X == Y && Y == Z)
      {
        printf("Triângulo Equilátero\n");
      }
       
       else if (X==Y||Y==Z)
      {
        printf("Triângulo Isósceles\n");
      }
      
     else
      {
        printf("Triângulo Escaleno\n");
      }
   }
     
    else
    {
      printf("Não é triângulo\n");
    }
 }
}

int main(void) 
{
  //declaração de variável
  double num1,num2,num3;
  int N=1;

  //Condição da repetição
  while (N >= 1)
   {
  //Leitura de lados
  printf("Digite os 3 lados do triângulo %d (0 em um dos lados para sair): ",N);
  scanf("%lf %lf %lf",&num1,&num2,&num3);

  //Fim do programa (saída)
  if(num1==0||num2==0||num3==0)
   {
    printf("Fim do programa\n");
    N=0;
   }
    
    else
  {
    //aciona módulo
    triangulo(num1,num2,num3);
    N++;
   }
  }
}