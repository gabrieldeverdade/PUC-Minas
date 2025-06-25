package unidade00f;

public class unidade00f3102 {
    public static void main(String[] args){
        String conteudo="";
        Arq.openRead("criptografado.txt");
        while(Arq.hasNext()==true){
            conteudo+=Arq.readLine() + "\n"; 
        }
        Arq.close();
        String conteudoCriptografado="";
        for(int i=0;i<conteudo.length();i++){
            int c = (int)(conteudo.charAt(i)-3);
            char cc = (char)(c);
            conteudoCriptografado+=cc;
        }
        System.out.println(conteudoCriptografado);
    }
}
