#include <iostream>
#include <stdio.h>
using namespace std;
/*
     Lista Extra - Exercicio 3  (Classe)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */
class Eletrodomestico {
private:
  string nome, telefone;
  double preco;
  void Inicializar(string nNome, string nTelefone, double nPreco) {
    SetNome(nNome);
    SetTelefone(nTelefone);
    SetPreco(nPreco);
  }
public:
  Eletrodomestico() { Inicializar("Loja", "0800-0800", 0.00); }
  void SetNome(string nNome) {
    if(nNome.length() > 0) nome = nNome;
    else cout << "Nome de loja inválido";
  }
  void SetTelefone(string nTele) {
    if(nTele.length() == 9 && nTele[4] == '-') telefone = nTele;
    else cout << "Telefone inválido";
  }
  void SetPreco(double nPreco) {
    if (nPreco >= 0) preco = nPreco;
    else cout << "Preço inválido";
  }
  string GetNome() { return nome; }
  string GetTelefone () { return telefone; }
  double GetPreco() { return preco; }
};

int main() 
{
  char arqEntrada[30], arqSaida[30], caracter, nome[20], tel[10];
  double preco, soma = 0;
  int quant= 0; // total de cadastros
  FILE * entrada, * saida;
  Eletrodomestico cadastros[30];
  
  cout << "Nome do arquivo dos cadastros: ";
  cin >> arqEntrada;

  entrada = fopen(arqEntrada, "r");
  while (fscanf(entrada, " %[^\n] %[^\n] %lf", nome, tel, &preco) != EOF)
  {
    printf("\nNome: %s\n Tel: %s\n Preco: R$%.2lf\n", nome, tel, preco);
    cadastros[quant].SetNome(nome);
    cadastros[quant].SetTelefone(tel);
    cadastros[quant].SetPreco(preco);
    soma += preco;
    quant ++;
  }
  fclose(entrada);

  cout << "\nNome do arquivo de relatório: ";
  cin >> arqSaida;
  
  saida = fopen(arqSaida, "w");

  fprintf(saida, "    Cadastros abaixo da média (Média: %.2lf)\n", (soma/quant));
  for (int i = 0; i < quant; i++)
    {
      if (cadastros[i].GetPreco() < (soma/quant))
      {
        fprintf(saida, "%s : %s\n", cadastros[i].GetNome().c_str(), cadastros[i].GetTelefone().c_str());
      }
    }
  printf("Concluido\n");
  fclose(saida);
}