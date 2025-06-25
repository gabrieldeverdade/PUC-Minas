#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

/*
     Lista Extra - Exercicio 8  (Classe)
     Autor: Gabriel Azevedo Fernandes
     Data: 13/12/2022
  */

class Pessoa {
private:
  int codigo;
  string nome;
  int idade;
  string endereco;
  int numero;
  string complemento;
  void Inicializar(int novoCodigo, string novoNome, int novaIdade,
                   string novoEndereco, int novoNumero,
                   string novoComplemento) {
    SetCodigo(novoCodigo);
    SetNome(novoNome);
    SetIdade(novaIdade);
    SetEndereco(novoEndereco);
    SetNumero(novoNumero);
    SetComplemento(novoComplemento);
  }

public:
  // construtores
  Pessoa() {
    Inicializar(0, "José", 21, "Rua Claudio Manoel", 1162, "sala 1302");
  }
  // Set e Get 's
  void SetCodigo(int novoCod) {
    if (novoCod >= 0)
      codigo = novoCod;
    else
      cout << "Erro - codigo invalido \n";
  }
  void SetNome(string novoNome) {
    if (novoNome.length() >= 3)
      nome = novoNome;
    else
      cout << "Erro - nome invalido \n";
  }
  void SetIdade(int novaIdade) {
    if (novaIdade >= 0)
      idade = novaIdade;
    else
      cout << "Erro - idade invalida \n";
  }
  void SetEndereco(string novoEndereco) {
    if (novoEndereco.length() >= 3)
      endereco = novoEndereco;
    else
      cout << "Erro - endereco invalido \n";
  }
  void SetNumero(int novoNumero) {
    if (novoNumero >= 0)
      numero = novoNumero;
    else
      cout << "Erro - numero invalido \n";
  }
  void SetComplemento(string novoComplemento) {
    if (novoComplemento.length() >= 3)
      complemento = novoComplemento;
    else
      cout << "Erro - complemento invalido \n";
  }

  int GetCodigo() { return codigo; }
  string GetNome() { return nome; }
  int GetIdade() { return idade; }
  string GetEndereco() { return endereco; }
  int GetNumero() { return numero; }
  string GetComplemento() { return complemento; }
  // Outros métodos
  void Exibir(){
    cout << "Código: " << GetCodigo() << endl << "Nome: " << GetNome() << endl << "Idade: " << GetIdade() << endl << "Endereço: "<< GetEndereco() << endl << "Numero: " << GetNumero() << endl << "Complemento: " << GetComplemento() << endl;
  }
};

void cadastrarPessoa(Pessoa vetor[60], int N)
{
  int novoCod, novaIdade, novoNumero;
  string novoNome, novoEndereco, novoComplemento;
  cout << "   Pessoa " << N << endl;

  cout << "Código: ";
  cin >> novoCod;
  vetor[N].SetCodigo(novoCod);

  cout << "Nome: ";
  cin >> novoNome;
  vetor[N].SetNome(novoNome);
  
  cout << "Idade: ";
  cin >> novaIdade;
  vetor[N].SetIdade(novaIdade);

  cout << "Endereco: ";
  cin >> novoEndereco;
  vetor[N].SetEndereco(novoEndereco);

  cout << "Numero: ";
  cin >> novoNumero;
  vetor[N].SetNumero(novoNumero);

  cout << "Complemento: ";
  cin >> novoComplemento;
  vetor[N].SetComplemento(novoComplemento);  

  cout << endl;
}

int main() 
{
  Pessoa grupo[60];
  FILE* arquivo = fopen("arquivo.txt", "w");
  char arqNome[30];
  int quant;

  cout << "Nome do arquivo (escrever '.txt'): ";
  cin >> arqNome;
  arquivo = fopen(arqNome, "w");
  
  cout << "Quantidade de pessoas: ";
  cin >> quant;

  for (int i = 0; i < quant; i++)
  {
    cadastrarPessoa(grupo, i);
  }

  for (int i = 0; i < quant; i++)
  {
    grupo[i].Exibir();
    cout << endl;

    //exibir no arq
    fprintf(arquivo, "\nCódigo: %d \nNome: %s \nIdade: %d \nEndereço: %s \nNumero:  %d \nComplemento: %s \n", grupo[i].GetCodigo(), grupo[i].GetNome().c_str(), grupo[i].GetIdade(), grupo[i].GetEndereco().c_str(), grupo[i].GetNumero(), grupo[i].GetComplemento().c_str());
  }

  fclose(arquivo);
}