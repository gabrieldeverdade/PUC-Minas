#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#define N 10
using namespace std;

/*
     Lista Extra - Exercicio 9  (Classe)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

class Pessoa
{
private:
  string nome;
  int dia;
  string mes;
public:
  Pessoa()
  {
    SetNome("aa");
    SetDia(1);
    SetMes("Janeiro");
  }
  Pessoa(char nom[20],int d,char m[20])
  {
    SetNome(nom);
    SetDia(d);
    SetMes(m);
  }
  string GetNome()
  {
    return nome;
  }
  void SetNome(string nom)
  {
    if(nom.length()>=2) nome=nom;
    else cout<<"Erro - Nome inválido!\n";
  }
  int GetDia()
  {
    return dia;
  }
  void SetDia(int d)
  {
    if(d>0&&d<=31) dia=d;
    else cout<<"Erro - Dia inválido!\n";
  }
  string GetMes()
  {
    return mes;
  }
  void SetMes(string m)
  {
    if(m.length()>=4) mes=m;
    else cout<<"Erro - Mês inválido!\n";
  }
  void Exibir()
    {
      cout<<"Nome: "<<GetNome()<<"\nDia: "<<GetDia()<<"\nMês: "<<GetMes()<<endl;
  }
};

int main() 
{
  FILE *vasco;
  char ala[20];
  int dia;
  char nome[20],mes[20];
  Pessoa V[N];
  string enter;
  cout<<"Digite o nome do arquivo onde serão armazenadas as informações: ";
  cin>>ala;
  vasco=fopen(ala,"w");
  for(int i=0;i<N;i++)
    {
      cout<<"Digite o nome da pessoa "<<i+1<<": ";
      cin>>nome;
      V[0].SetNome(nome);
      cout<<"Dia do aniversário: ";
      cin>>dia;
      V[0].SetDia(dia);
      cout<<"Mês do aniversário: ";
      cin>>mes;
      V[0].SetMes(mes);
      fprintf(vasco,"%s:\n%s, dia %d\n\n",mes,nome,dia);
    } 
  for(int i=0;i<N;i++)
    {
      V[i].Exibir();
    }
}