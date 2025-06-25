#include <stdio.h>

/* 
     Exercicio -  fazer uma função que recebe a idade de um nadador por 
                  parâmetro e retorna a categoria desse nadador de acordo 
                  com o exercicio proposto
     Autor: Gabriel Azevedo Fernandes
     Data: 25/09/2022
  */

//Módulo
int leitor (num)
{
//declaração de variável
char cat;
  
//condição + calculo
if (num>=5 && num<=7)
{
  cat = 'F';
}
  else if (num>7&&num<=10)
  {
    cat = 'E';
  }
  else if (num>10&&num<=13)
  {
    cat = 'D';
  }
  else if (num>13&&num<=15)
  {
    cat = 'C';
  }
  else if (num>15&&num<=17)
  {
    cat = 'B';
  }
  else if (num>=18)
  {
    cat = 'A';
  }
  else 
  {
    cat = 'I';
  }

//Retorna categoria pro main
return (cat);
  }
  
int main(void) 
{

//declaração de variável
int idade;
char categoria;

//Leitura de dados
printf("Digite a idade do nadador: ");
scanf("%d",&idade);

//Enviar pro módulo
categoria = leitor(idade);

//Exibir categoria na tela
  if (categoria != 'I')
  {
printf("A categoria do nadador é %c\n",categoria);
  }
  else
  {
    printf("Não possui categoria\n");
  }
}