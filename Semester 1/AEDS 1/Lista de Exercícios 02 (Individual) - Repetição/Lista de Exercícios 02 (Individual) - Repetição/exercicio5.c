#include <stdio.h>

/*
     Exercicio - Calcular o salário de cada habitante e mostrar 
                 a média de acordo com o exercício proposto
     Autor: Gabriel Azevedo Fernandes
     Data: 19/09/2022
  */
int main(void) 
{
  //Declaração de variáveis
int pessoaX=1, salario=0, filho=0;
int maiorsal,filhototal=0;
double salario100=0, saltotal=0;
  
//Condição da repetição dos salários e filhos
while (salario >= 0)
  {
    
//Declaração dos valores
    
printf("Digite a quantidade de filhos e o salário da pessoa %d: ",pessoaX);
scanf("%d %d",&filho,&salario);
if (salario < 0)
{
  pessoaX--;
}
  else
{
if (pessoaX==1)
{
  maiorsal=salario;
}
else if (salario > maiorsal)
{
  maiorsal=salario;
}
if (salario<=100)
{
  salario100++;
}
  saltotal = saltotal + salario;
filhototal = filhototal + filho;
  pessoaX++;
  }}

//Exibição dos resultados

printf("Média do salário da população: %.2lf\n",(double)saltotal/pessoaX);
printf("Média do número de filhos: %.2lf\n",(double)filhototal/pessoaX);
printf("Maior salário: R$ %d\n", maiorsal);
printf("Percentual de pessoas com salário de até R$ 100: %.2lf por cento\n",(salario100/pessoaX)*100);
  return 0;
}