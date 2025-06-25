package unidade00f;
import java.util.Scanner;
public class unidade00f3201 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int a=0;       
        do{
            System.out.print("1: Inserir\n2: Remover\n3: Listar\n4: Sair\nEscolha: ");
            String escolha = scanner.nextLine();
            switch(escolha){
            case "1":
            System.out.print("Digite o que deseja inserir: ");
            String inserir = scanner.nextLine();
            Arq.openWrite("pilha.dat.txt");
            Arq.println(inserir);
            Arq.close();
            break;
            case "2":
            System.out.println("Ainda em desenvolvimento :/");
            break;
            case "3":
            String lista="";
            Arq.openRead("pilha.dat.txt");
            while(Arq.hasNext()==true){
                lista+=Arq.readLine()+"\n";
            }
            System.out.println(lista);
            Arq.close();
            break;
            case "4":
            a=1;
            break;
            default:
            System.out.println("Erro - inexistente!");
        }
        }while(a==0);
        scanner.close();
    }
}
