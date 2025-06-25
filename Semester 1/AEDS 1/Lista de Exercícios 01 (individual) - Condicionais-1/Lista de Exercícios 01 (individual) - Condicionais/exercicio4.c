#include <stdio.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Faça um algoritmo que segundo uma nota 
                   informada pelo usuário, verifique em qual 
                   faixa a mesma se encaixa e imprima para o 
                   usuário a mensagem correspondente       
                   (Nota >= 8 e nota <=10 --> Ótimo)                               (Nota >= 7 e nota <8 --> Bom)              
                   (Nota >= 5 e Nota <7 --> Regular)          
                   (Nota < 5 --> Insatisfatório)

    Data: 09/09/2022 
  */

int main(void) 
{
  //Declaração de variáveis
  double nota;

  printf("Digite a sua nota na prova: ");
  scanf("%lf", &nota);

  //Condição, verificação e exibição das notas
  if(nota < 5)
  {
    printf("\nInsatisfatório!\n");
  }
  else if (nota < 7)
  {
    printf("\nRegular!\n");
  }
  else if (nota < 8)
  {
    printf("\nBom!\n");
  }
  else if (nota <= 10)
  {
    printf("\nÓtimo!\n");
  }
    
  else
  {
    printf("\nNota Inválida!\n");//Caso de valor incorreto
  }
  return 0;
}