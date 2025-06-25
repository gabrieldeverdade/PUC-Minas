package unidade00g;
import java.util.Scanner;
public class unidade00g21802 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        int[] array = new int[N];
        for(int i=0;i<N;i++){
            System.out.print("Digite o valor da posição "+(i)+": ");
            array[i]=scanner.nextInt();
        }
        int menor = 0;
        for(int i=1;i<N;i++){
            if(array[i]<array[menor]){
                menor=i;
            }
        }
        System.out.print("Posição do menor elemento: "+menor);
        scanner.close();
    }
}
