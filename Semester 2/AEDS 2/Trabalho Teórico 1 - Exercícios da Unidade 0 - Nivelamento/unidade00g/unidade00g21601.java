package unidade00g;
import java.util.Scanner;
public class unidade00g21601 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        int[] array = new int[N];
        for(int i=0;i<N;i++){
            System.out.print("Digite o elemento "+(i+1)+": ");
            array[i]=scanner.nextInt();
        }
        int menor = array[0];
        for(int i=1;i<N;i++){
            if(array[i]<menor){
                menor=array[i];
            }
        }
        System.out.println("O menor elemento é "+menor);
        scanner.close();
    }
}
