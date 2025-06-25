#include <stdio.h>

/* 
     Exercicio -  fazer dunção que lê indeterminadas notas de alunos, 
                  calcula e retorna a média das notas dos alunos aprovados 
                  (nota maior ou igual a 6)
     Autor: Gabriel Azevedo Fernandes
     Data: 25/09/2022
  */

//Mód
double media(double numAluno,double notas)
{

//Declaração de variáveis
double media;

//Cálculo média
media = notas/numAluno;

//Retorna valor 
return (media);
  }

int main(void) 
{
//declaração de variáveis
double aluno=1,alunomedia=0,nota,notafinal=0,resultado;

//Leitura dos dados 
 while(aluno>=1)
   {
printf("Digite a nota do aluno %.0lf (-1 para parar): ",aluno);
scanf("%lf",&nota);

//Verifica se nota é > ou = a 6
if (nota==-1)
{
  aluno=0;
}
     else
{
if (nota<6)
{}
     else if (nota>=6)
     {
       notafinal=notafinal+nota;
       alunomedia++;
     }
aluno++;
     }
     
//Enviar para módulo
     }
 resultado = media (alunomedia,notafinal);
     
 //exibe resultado na tela
 printf("O valor da média é %.2lf\n",resultado);
}