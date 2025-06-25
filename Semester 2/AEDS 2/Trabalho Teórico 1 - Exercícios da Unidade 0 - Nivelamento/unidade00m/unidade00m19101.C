#include <stdio.h>
void troca(int *a,int *b){
    int troca=*a;
    *a=*b;
    *b=troca;
}
int main(){
    int a,b;
    printf("Digite os números a serem trocados: ");
    scanf("%d %d",&a,&b);
    troca(&a,&b);
    printf("Valores trocados: %d e %d\n",a,b);
}