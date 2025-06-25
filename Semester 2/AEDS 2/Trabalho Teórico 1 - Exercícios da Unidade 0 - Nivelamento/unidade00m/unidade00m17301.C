#include <stdio.h>
#include <stdlib.h>

int main(void){
    int N;
    FILE *arquivoTexto;
    arquivoTexto = fopen("arquivoC.txt","a");
    printf("Digite o valor de N: ");
    scanf("%d",&N);
    int V[N];
    for(int i=0;i<N;i++){
        fprintf(arquivoTexto,"%d, ",V[i]);
    }
    fclose(arquivoTexto);
    for(int i=0;i<N;i++){
        printf("%d ",V[i]);
    }
}