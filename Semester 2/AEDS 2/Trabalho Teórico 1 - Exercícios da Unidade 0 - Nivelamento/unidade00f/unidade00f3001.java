package unidade00f;

public class unidade00f3001 {
    public static void main(String[] args){
        String conteudo="";
        Arq.openRead("meuArquivo.txt");
        while(Arq.hasNext()==true){
            conteudo += Arq.readLine() + "\n";
        }
        Arq.close();
        String conteudoMaiusculo = conteudo.toUpperCase();
        Arq.openWrite("copiaMeuArquivo.txt");
        Arq.print(conteudoMaiusculo);
        Arq.close();
    }
}
