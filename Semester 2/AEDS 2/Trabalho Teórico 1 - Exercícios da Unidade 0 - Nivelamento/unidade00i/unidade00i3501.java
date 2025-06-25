package unidade00i;
import java.util.Scanner;
public class unidade00i3501 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] x = new int[5];
        for(int i=0;i<5;i++){
            x[i]=scanner.nextInt();
        }
        int n=5;
        x[0]=n;
        System.out.println(x[0]+" "+x[1]);
        scanner.close();
    }
}
