package unidade00i;
import java.util.Scanner;
public class unidade00i6201 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        for(int i=N;i>0;i--){
            System.out.println(i);
        }
        scanner.close();
    }
}
