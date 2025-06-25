using System;

class Program
{
  public static void Main (string[]args)
  {
    int numero;
    int divisores = 0;

      //Solicita que o usuário informe o numero
    Console.WriteLine("Informe o número: ");
      //Realiza a Leitura do número
    numero = Convert.ToInt32(Console.ReadLine());

      //Verificar a quantidade de divisores do número
    for (int i=1; i<=numero; i++)
    {
        //Verifica se é divisor
      if(numero % i == 0)
        divisores++;
    }

      //Depois de contar a quantidade de divisores, verifica se possui apenas 2
      //Um número é primo se possui apenas dois divisores ==> 1 e o próprio número
    if(divisores == 2)
      Console.WriteLine("É um número primo!");
    else
      Console.WriteLine("Não é um número primo!");

      //Aguarda que uma tecla seja pressionada
    Console.ReadKey();
  }
}