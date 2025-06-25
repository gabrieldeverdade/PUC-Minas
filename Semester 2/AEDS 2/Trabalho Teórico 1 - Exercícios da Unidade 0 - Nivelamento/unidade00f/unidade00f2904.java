package unidade00f;

public class unidade00f2904 {
    public static void main(String[] args){
        String conteudo="";
        Arq.openRead("meuArquivo.txt");
        while(Arq.hasNext()==true){
            conteudo += Arq.readLine() + "\n";
        }
        Arq.close();
        Arq.openWrite("copiaMeuArquivo.txt");
        Arq.print(conteudo);
        Arq.close();
    }
}
