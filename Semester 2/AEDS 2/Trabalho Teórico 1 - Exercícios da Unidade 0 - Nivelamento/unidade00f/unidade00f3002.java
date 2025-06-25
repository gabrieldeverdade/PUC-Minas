package unidade00f;

public class unidade00f3002 {
    public static void main(String[] args){
        String conteudo="";
        Arq.openRead("meuArquivo.txt");
        while(Arq.hasNext()==true){
            conteudo += Arq.readLine() + "\n";
        }
        Arq.close();
        String conteudoInvertido="";
        for(int i=0;i<conteudo.length();i++){
            conteudoInvertido+=conteudo.charAt(conteudo.length()-i-1);
        }
        Arq.openWrite("copiaMeuArquivo.txt");
        Arq.print(conteudoInvertido);
        Arq.close();
    }
}
