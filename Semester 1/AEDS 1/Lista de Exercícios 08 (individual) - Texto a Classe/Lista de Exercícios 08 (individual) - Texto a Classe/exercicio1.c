#include <stdio.h>

/*
     Lista Extra - Exercicio 1 (Struct)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

typedef struct Cadastro
{
int cod;
char email[30];
double hrs;
char pag;
}Cadastro;

int main(void) 
{
  int N=500;
  Cadastro V[N];
  for(int i=0;i<N;i++)
    {
      printf("Digite o código do cliente %d: ",i+1);
      scanf("%d",&V[i].cod);
      printf("Digite seu email: ");
      scanf("%s",V[i].email);
      printf("Digite as horas de acesso: ");
      scanf("%lf",&V[i].hrs);
      printf("O cliente possui página? (S/N) ");
      scanf(" %c",&V[i].pag);
    }
  for(int i=0;i<N;i++)
    {
      if(V[i].hrs<=20)
      {
        if(V[i].pag=='S'||V[i].pag=='s')
          printf("%d: R$ 75\n",V[i].cod);
        else
          printf("%d: R$ 35\n",V[i].cod);
      }
      else
      {
        if(V[i].pag=='S'||V[i].pag=='s')
          printf("%d: R$ %.2lf\n",V[i].cod,(75+((V[i].hrs-20)*2.5)));
        else
          printf("%d: R$ %.2lf\n",V[i].cod,35+(V[i].hrs-20)*2.5);
      }
    }
}