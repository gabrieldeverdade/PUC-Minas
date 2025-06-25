package unidade00g;
import java.util.Scanner;
public class unidade00g21702 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        double total=0;
        double[] array = new double[5];
        for(int i=0;i<5;i++){
            System.out.print("Digite a nota do aluno "+(i+1)+": ");
            array[i]=scanner.nextDouble();
        }
       double menor = array[0];
        for(int i=0;i<5;i++){
            if(array[i]<menor){
                menor=array[i];
            }
            total+=array[i];
        }
        System.out.println("Total: "+total+"\nMédia: "+(total/5)+"\nMenor nota: "+menor);
        scanner.close();
    }
}
