package unidade00h;
import java.util.Scanner;
public class unidade00h15901 {
    public static int calculaResto(int D, int d) {
        if(D/d==0){
            return D;
        }
        else{
            return calculaResto(D-d,d);
        }
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor do dividendo: ");
        int D = scanner.nextInt();
        System.out.print("Digite o valor do divisor: ");
        int d = scanner.nextInt();
        System.out.println("Resto: "+calculaResto(D,d));
        scanner.close();
    }
}
