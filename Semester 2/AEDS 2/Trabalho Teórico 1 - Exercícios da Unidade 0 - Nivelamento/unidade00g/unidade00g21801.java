package unidade00g;
import java.util.Scanner;
public class unidade00g21801 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        int[] array = new int[N];
        for(int i=0;i<N;i++){
            System.out.print("Digite o elemento "+(i+1)+": ");
            array[i]=scanner.nextInt();
        }
        if(N%2==0){
            for(int i=0;i<N/2;i++){
                System.out.println(array[i]+array[N-i-1]);
            }
        }
        scanner.close();
    }
}
