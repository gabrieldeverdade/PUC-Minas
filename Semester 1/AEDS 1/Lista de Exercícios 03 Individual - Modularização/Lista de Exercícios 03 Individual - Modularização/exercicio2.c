#include <stdio.h>

/*
     Exercicio - Fazer um procedimento que leia um número não determinado de 
                 pessoas, calcule e exiba a media de salário da população (a 
                 condição de parada pode ser um flag ou a quantidade de N) 
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */
//Módulo para calcular média de salário e filho

void calculo(int num)
{
//Declaração de Variáveis
int pessoa=1, filho, filhototal=0, total;
double salario, saltotal=0;

//Condição da repetição número de pessoas
while (num >= 1)
  {
    //Leitura valores    
    printf("Infome o salário e número de filhos da pessoa %d: ",pessoa);
    scanf("%lf %d",&salario,&filho);

    //Condição + calculo
    if (pessoa == 1)
    {
      total = num;
      saltotal = saltotal + salario;
      filhototal = filhototal + filho;
    }
      else
    {
      saltotal = saltotal + salario;
      filhototal = filhototal + filho; 
    }
    num--;
    pessoa ++;
  }
  printf("\nA média de salário da população é: R$%.2lf\nA média de %d filhos\n", saltotal/total, filhototal/total);
}

int main(void) 
{
  
//Dec de variável
int N;

printf("Informe o número de habitantes analisados: ");
scanf("%d",&N);

//Aciona módulo
calculo(N);
  }