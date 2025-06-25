
public class unidade00b1b{
    public static boolean verifica(int x, int[] array) {
        for(int i=0;i<array.length;i++){
            if(array[i]==x){
                return true;
            }
        }
        return false;
    }
    public static void main(String[] args) {
        int[] array = {8,2,3,6,5,4,7,1,9,10};
        int x = 50;
        if(verifica(x,array)){
            System.out.println("Pertence");
        }
        else{
            System.out.println("Não pertence");
        }
    }
}