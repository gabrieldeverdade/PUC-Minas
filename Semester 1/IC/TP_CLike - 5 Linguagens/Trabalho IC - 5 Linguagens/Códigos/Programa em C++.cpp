#include <iostream>
using namespace std;

/*
    Trabalho IC em 5 Linguagens - Linguagem C++ 
    Autor - Gabriel Azevedo Fernandes
    Data - 12/06/2022
 */


//Depois de contar a quantidade de divisores, verifica se possui apenas 2

//Um número é primo se possui apenas dois divisores ==> 1 e o próprio número

//Verificar a quantidade de divisores do número
void calcula (int number){
  int divisiveis = 0;
  for(int i=1; i <= number; i++){
    if(number %i == 0){
      divisiveis++;
    }
  }
  if (number == 1){
    cout<< "O número 1 não é primo, pois tem apenas um divisor"<<endl;
  }
  else if (divisiveis == 2){
    cout <<"É PRIMO"<<endl;
  }
  else{
    cout<<"NÃO É PRIMO"<<endl;
  }
}

//Solicita que o usuário informe o numero
void imprime (){
  int numero;
  cout<<"Vamos verificar se o numero informado é primo!"<<endl;
  cout<<"Digite um número:"<<endl;
  cin>>numero;
  calcula(numero);
}

//Pergunta se quer dar continuidade ao usar o programa
  void verifica(){
    char opt ='s';
  while(opt =='s'){
    imprime();
    cout<<"Deseja Continuar"<<endl;
    cout<<"Digite 's' para continuar ou qualquer tecla para encerrar"<<endl;
    cin>>opt;
    }
}

int main(){
  verifica();
  return 0;
}