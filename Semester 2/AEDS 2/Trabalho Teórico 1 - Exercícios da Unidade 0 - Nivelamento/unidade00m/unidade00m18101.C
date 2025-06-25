#include <stdio.h>
int main (){
    int N;
    printf("Digite o valor de N: ");
    scanf("%d",&N);
    int V[N],Vsoma[N/2];
    for(int i=0;i<N/2;i++){
        Vsoma[i]=V[i]+V[N-i-1];
    }
    for(int i=0;i<N/2;i++){
        printf("%d ",Vsoma[i]);
    }
}