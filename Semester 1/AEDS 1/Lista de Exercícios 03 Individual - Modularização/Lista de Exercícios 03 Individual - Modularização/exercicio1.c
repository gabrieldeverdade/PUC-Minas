#include <stdio.h>

/*
     Exercicio - Fazer um procedimento que recebe as 3 notas de um aluno por 
                 parâmetro e uma letra. Se a letra for 'A', o procedimento calcula 
                 e escreve sua média aritmética, se for 'P', calcula e escreve a 
                 média ponderada (pesos 5, 3 e 2). Faça um programa que leia 3 
                 notas de N alunos e acione o procedimento para cada aluno        
                 (N deve ser lido no teclado)    
Autor: Gabriel Azevedo Fernandes
     Data: 24/09/2022
  */

//Declaração de variáveis
float media(float nota1, float nota2, float nota3, char op) 
{
  //Condições e cálculo das médias
    if (op == 'A') 
    {
        return (nota1 + nota2 + nota3) / 3;
    } 
    else if (op == 'P') 
    {
        return (nota1*5 + nota2*3 + nota3*2) / 10;
    }
}

//Acionamento
int main()
{
    float nota1, nota2, nota3, calc;
    char op;

    printf("Digite A ou P: ");
    scanf("%c", &op);
    printf("Digite 3 notas:\n");
    scanf("%f %f %f", &nota1, &nota2, &nota3);

    calc = media(nota1, nota2, nota3, op);

    //Exibe Resultado
    printf("A média é igual a: %f", calc);

    return 0;
}