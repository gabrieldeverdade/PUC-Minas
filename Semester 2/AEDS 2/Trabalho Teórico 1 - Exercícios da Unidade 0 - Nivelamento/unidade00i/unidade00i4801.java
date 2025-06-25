package unidade00i;
import java.util.Scanner;
public class unidade00i4801 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        for(int i=0;i<N;i++){
            System.out.println(i+1);
        }
        scanner.close();
    }
}
