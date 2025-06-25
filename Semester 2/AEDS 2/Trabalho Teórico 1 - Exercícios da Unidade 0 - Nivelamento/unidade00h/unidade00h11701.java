package unidade00h;
import java.util.Scanner;

public class unidade00h11701 {
    public static int resto(int N) {
        if(N/10==0){
            return N%10;
        }
        else{
            return (resto(N/10)+N%10);
        }
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o número que será obtido a soma dos dígitos: ");
        int N = scanner.nextInt();
        System.out.println(resto(N));
        scanner.close();
    }
    
}
