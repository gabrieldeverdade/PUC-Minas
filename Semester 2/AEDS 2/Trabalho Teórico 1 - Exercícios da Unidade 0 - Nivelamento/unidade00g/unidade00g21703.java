package unidade00g;
import java.util.Scanner;
public class unidade00g21703 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o valor de N: ");
        int N = scanner.nextInt();
        int media=0;
        double[] array = new double[N];
        for(int i=0;i<N;i++){
            System.out.print("Digite o valor da posição "+(i+1)+": ");
            array[i]=scanner.nextDouble();
        }
        for(int i=0;i<N;i++){
            media+=array[i];
        }
        media/=N;
        System.out.println("Média: "+media);
        for(int i=0;i<N;i++){
            if(array[i]>media){
                System.out.print(array[i]+" ");
            }
        }
        System.out.println();
        scanner.close();
    }
}
