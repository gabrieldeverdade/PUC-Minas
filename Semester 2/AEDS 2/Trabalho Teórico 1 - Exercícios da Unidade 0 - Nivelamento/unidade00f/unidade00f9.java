package unidade00f;
import java.util.Scanner;
public class unidade00f9 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        Arq.openWrite("ExemploArq01Escrita.txt");
        for(int i=1;i<=10;i++){
            Arq.println(i);
        }
        Arq.close();
        Arq.openWrite("ExemploArq02Escrita.txt");
        String nome;
        int id;
        System.out.print("Digite seu nome completo: ");
        nome = scanner.nextLine();
        System.out.print("Quantos anos? ");
        id = scanner.nextInt();
        Arq.println(nome);
        Arq.println(id);
        Arq.close();
        scanner.close();
    }
}
