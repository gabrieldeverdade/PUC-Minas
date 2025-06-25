public class unidade00b2a {
    public static void compara(int[] array) {
        int maior=array[0];
        int menor=array[0];
        for(int i=0;i<array.length;i++){
            if(maior<array[i]){
                maior=array[i];
            }
            if(menor>array[i]){
                menor=array[i];
            }
        }
        System.out.println("Maior: "+maior+"\nMenor: "+menor);
    }
    public static void main(String[] args){
        int[] array = {1,2,3,4,5,6,7,8,9};
        compara(array);
    }
}
