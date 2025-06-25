package unidade00f;
import java.util.Scanner;
public class unidade00f2903 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String conteudo="";
        Arq.openRead("ExemploArq02Escrita.txt");
        while(Arq.hasNext()==true){
            conteudo += Arq.readLine();
            conteudo.toUpperCase();
            conteudo+="\n";
        }
        Arq.close();
        String conteudoMaiusculo = conteudo.toUpperCase();
        System.out.println(conteudoMaiusculo); 
        scanner.close();
    }
}