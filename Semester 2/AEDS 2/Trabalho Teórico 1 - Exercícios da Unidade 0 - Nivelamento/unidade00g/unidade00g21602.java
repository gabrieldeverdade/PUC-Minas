package unidade00g;
import java.util.Scanner;
public class unidade00g21602 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int[] array = {5,4,6,7,3,8,2,9,1};
        for(int a=0;a<9;a++){
            int menor=a;
            for(int i=a+1;i<9;i++){
                if(array[i]<array[menor]){
                    menor=i;
                }
            }
            int troca=array[a];
            array[a]=array[menor];
            array[menor]=troca;
        }
        for(int i=0;i<9;i++){
            System.out.print(array[i]+", ");
        }
        System.out.println();
        scanner.close();  
    }
}
