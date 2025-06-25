package unidade00f;
import java.util.Scanner;
public class unidade00f2901 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String nome, frase;
        System.out.print("Digite o nome do arquivo: ");
        nome=scanner.nextLine();
        nome+=".txt";
        System.out.print("Digite a frase que será alocada nele: ");
        frase=scanner.nextLine();
        Arq.openWrite(nome);
        Arq.print(frase);
        Arq.close();
        scanner.close();
    }
}
