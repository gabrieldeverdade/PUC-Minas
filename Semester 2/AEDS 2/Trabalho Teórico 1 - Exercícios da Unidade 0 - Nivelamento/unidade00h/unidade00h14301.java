package unidade00h;
import java.util.Scanner;
public class unidade00h14301 {
    public static int troca(int N) {
        if(N/10==0){
            return 1;
        }
        else{
            return (troca(N/10)+1);
        }
    }
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o número que serão contados os dígitos: ");
        int N = scanner.nextInt();
        System.out.println(troca(N));
        scanner.close();     
    }
}
