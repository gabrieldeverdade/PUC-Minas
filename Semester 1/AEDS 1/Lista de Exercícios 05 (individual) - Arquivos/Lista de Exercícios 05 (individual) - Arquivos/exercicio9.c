#include <stdio.h>
#include <stdlib.h>

/*
    Lista 5 - Arquivo
    Exercício 9 - Crie um programa que receba dados de vários 
                  alunos (Matricula e Telefone) e armazene em 
                  um  arquivo  texto.  Crie  no  mesmo  programa  
                  uma  opção  de  ler  dados  de  um  arquivo  já 
                  armazenado dados de alunos
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */

int main(void) 
{
  FILE *grade;
  int total;
  int matricula[9],telefone[8];
  
  grade = fopen("grade.txt","w");

  printf("Digite quantos alunos serão registrados: ");
  scanf("%d",&total);

  total--;

  int alunom[total];
  int alunot[total];

  for(int i=0;i<=total;i++)
    {
      printf("Digite o telefone do aluno %d: ",i+1);
      scanf("%d",&alunom[i]);
      printf("Digite a matrícula do aluno %d: ",i+1);
      scanf("%d",&alunot[i]);
      fprintf(grade,"Aluno %d - Matrícula: %d, Telefone: %d\n",i+1,alunom[i],alunot[i]);
    }
  }
  