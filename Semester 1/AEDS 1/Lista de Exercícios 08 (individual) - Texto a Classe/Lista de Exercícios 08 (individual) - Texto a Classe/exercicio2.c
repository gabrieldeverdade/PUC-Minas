#include <stdio.h>

/*
     Lista Extra - Exercicio 2  (Struct)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

typedef struct Registro
{
int cod;
char doa;
char nome[30];
char autor[30];
char edit[30];
char area;
}Registro;

int main(void) 
{
  // Passar N para 500 depois
  int consulta,escolha;
  int N=1;
  Registro e[N],h[N],b[N];
  printf("Cadastro de Exatas\n\n");
  for(int i=0;i<N;i++)
    {
      printf("Digite o código do livro %d: ",i+1);
      scanf("%d",&e[i].cod);
      printf("O livro foi doado? (s/n) ");
      scanf(" %c",&e[i].doa);
      printf("Digite o nome: ");
      scanf("%s",e[i].nome);
      printf("Qual o autor do livro? ");
      scanf("%s",e[i].autor);
      printf("Qual a editora? ");
      scanf("%s",e[i].edit);
      printf("\nCadastro do %dº livro de exatas efetuado!\n\n",i+1);    
    }
  printf("Cadastro de Humanas\n\n");
  for(int i=0;i<N;i++)
    {
      printf("Digite o código do livro %d: ",i+1);
      scanf("%d",&h[i].cod);
      printf("O livro foi doado? (s/n) ");
      scanf(" %c",&h[i].doa);
      printf("Digite o nome: ");
      scanf("%s",h[i].nome);
      printf("Qual o autor do livro? ");
      scanf("%s",h[i].autor);
      printf("Qual a editora? ");
      scanf("%s",h[i].edit);
      printf("\nCadastro do %dº livro de humanas efetuado!\n\n",i+1);    
    }
  printf("Cadastro de Biológicas\n\n");
  for(int i=0;i<N;i++)
    {
      printf("Digite o código do livro %d: ",i+1);
      scanf("%d",&b[i].cod);
      printf("O livro foi doado? (s/n) ");
      scanf(" %c",&b[i].doa);
      printf("Digite o nome: ");
      scanf("%s",b[i].nome);
      printf("Qual o autor do livro? ");
      scanf("%s",b[i].autor);
      printf("Qual a editora? ");
      scanf("%s",b[i].edit);
      printf("\nCadastro do %dº livro de biológicas efetuado!\n\n",i+1);    
    }
  do{
    printf("Digite o código para consulta (-1 para sair): ");
    scanf("%d",&consulta);
    if (consulta!=-1)
    {
      printf("\n\nSelecione uma área:\n1 - Exatas\n2 - Humanas\n3 - Biológicas\nEscolha: ");
      scanf("%d",&escolha);
      switch(escolha)
        {
          case 1:
          for(int i=0;i<N;i++)
            {
              if(e[i].cod==consulta)
              {
                printf("\nNome: %s\nAutor: %s\nEditora: %s\nDoado: %c\n\n",e[i].nome,e[i].autor,e[i].edit,e[i].doa);
              }
            }
          break;
          case 2:
          for(int i=0;i<N;i++)
            {
              if(h[i].cod==consulta)
              {
                printf("\nNome: %s\nAutor: %s\nEditora: %s\nDoado: %c\n\n",h[i].nome,h[i].autor,h[i].edit,h[i].doa);
              }
            }
          break;
          case 3:
          for(int i=0;i<N;i++)
            {
              if(b[i].cod==consulta)
              {
                printf("\nNome: %s\nAutor: %s\nEditora: %s\nDoado: %c\n\n",b[i].nome,b[i].autor,b[i].edit,b[i].doa);
              }
            }
          break;
          default: printf("Opção inválida!\n\n");
        }
    }
    }while (consulta!=-1);
}