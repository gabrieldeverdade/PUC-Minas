public class unidade00b1a{
    public static boolean verifica(int x, int[] array) {
        for(int i=0;i<array.length;i++){
            if(array[i]==x){
                return true;
            }
        }
        return false;
    }
    public static void main(String[] args) {
        int[] array = {1,2,3,4,5,6,7,8,9};
        int x = 9;
        if(verifica(x,array)){
            System.out.println("Pertence");
        }
        else{
            System.out.println("Não pertence");
        }
    }
}