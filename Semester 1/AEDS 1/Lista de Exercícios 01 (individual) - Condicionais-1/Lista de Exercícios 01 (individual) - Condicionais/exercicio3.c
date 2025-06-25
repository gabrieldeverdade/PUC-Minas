#include <stdio.h>

/*
    Autor: Gabriel Azevedo Fernandes
       Exercício - Fazer um algoritmo que leia o ano de 
                   nascimento de uma pessoa e calcule a sua 
                   idade considerando o ano atual. Para 
                   verificar se já fez aniversário no ano atual 
                   pergunte se a pessoa já fez aniversário, 
                   sendo que ela pode entrar com a informação 
                   (S-SIM ou N-NÃO). Com isso é possível ter 
                   maior precisão para conseguir a carteira de 
                   habilitação (18 anos ou mais) e imprima a 
                   mensagem referente a essa checagem. Imprima 
                   a idade da pessoa.
    Data: 09/09/2022 
  */
int main(void) 
{
  //Declaração de variáveis
  char aniversario;
  int ano_nasc, ano_atu, idade=0;

  printf("Informe o ano do seu nascimento e o ano atual: ");
  scanf("%d %d", &ano_nasc, &ano_atu);

  printf("Você já fez aniversário esse ano (S ou N)? ");
  scanf(" %c", &aniversario);

  //Cálculo da sua idade e verificação da CNH
  switch (aniversario) //compara os valores da variável
    {
      case 'S': //Condição caso Sim seja a resposta
      idade = ano_atu - ano_nasc;
      printf("\nVocê tem %d anos\n", idade);
      if (idade <18)
      {
        printf("Não pode tirar a CNH!\n");
      }
      else
      {
       printf("Pode tirar a CNH!\n"); 
      }
        
      break;case 'N': //Condição caso o Não seja a resposta
      idade = ano_atu - ano_nasc - 1;
      printf("\nVocê tem %d anos\n", idade);
      if(idade < 18)
      {
        printf("Não pode tirar a CNH!\n");
      }
      else
      {
        printf("Pode tirar a CNH!\n");
      }
    }
  return 0;
}

