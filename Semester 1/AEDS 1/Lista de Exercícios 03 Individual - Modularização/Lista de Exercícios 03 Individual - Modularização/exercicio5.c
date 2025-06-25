#include <stdio.h>

/* 
     Exercicio -  fazer procedimento que recebe a media final de um 
                  aluno, identifica e exibe o seu conceito, conforme o 
                  exercicio proposto
     Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */
//Módulo exibir conceito
void conceito (int mediafinal, int aluno)
{

//Cálculo + exibe conceito
  if (mediafinal<=39)
  {
    printf("O aluno %d apresenta o conceito F\n",aluno);
  }
  else if (mediafinal<=59)
  {
    printf("O aluno %d apresenta o conceito E\n",aluno);
  }
  else if (mediafinal<=69)
  {
    printf("O aluno %d apresenta o conceito D\n",aluno);
  }
  else if (mediafinal<=79)
  {
    printf("O aluno %d apresenta o conceito C\n",aluno);
  }
  else if (mediafinal<90)
  {
    printf("O aluno %d apresenta o conceito B\n",aluno);
  }
  else
  {
    printf("O aluno %d apresenta o conceito A\n",aluno);
  }
}

int main(void) 
{

//Declaração de variáveis
int N,media,a=1;

//Leitura de dados
printf("Digite a quantidade de alunos que serão analisados: ");
scanf("%d",&N);

//Repetição até o número informado
while (N>=1)
  {
    printf("Digite a média final do aluno %d: ",a);
    scanf("%d",&media);

//Aciona módulo
    conceito (media,a);
    a++;
    N--;
  }
  }