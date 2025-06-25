#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
    Lista 5 - Arquivo
    Exercício 7 - Faça um programa para inserir N letras 
                  informadas pelo usuário em um arquivo texto. 
                  Onde N  é  uma  quantidade  de  letras  definida                   pelo  usuário.  Depois  de  inseridas  as  N  
                  letras,  o programa deverá ler todas as N letras 
                  do arquivo, calcular e mostrar a quantidade de 
                  vogais, ou seja,  quantas letras a, e, i, o, u.
    Autor - Gabriel Azevedo Fernandes
    Data - 07/11/2022
 */
int main(void){
    char texto[100];
    int i, j, contador=0;
	char vetVogais[] = "aAeEiIoOuU";
	
FILE *entrada;  
 entrada = fopen("entrada.txt", "w");
  
printf("Usuário, digite um texto: ");
  
scanf(" %[^\n]",texto);
  fputs(texto,entrada);

  fclose(entrada);

    for (i=0;i<strlen(texto);i++){
    	for (j=0;j<strlen(vetVogais);j++){
    		if (texto[i] == vetVogais[j]){
    			contador++;
    		}
    	}
    }
    
    if (contador == 1){
    	printf ("\n\nO texto informado possui 1 vogais\n\n");
	}else{
		printf ("\n\nO texto informado possui %d vogais\n\n", contador);
	}
    return 0;
}