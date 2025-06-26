import java.io.*;
import java.util.*;

public class Main extends Thread {
   public static void main(String[] args) throws IOException {
      try {
         generateRandomGraph(50000, 50000, "graph.txt");
         Graph g = Graph.fromFile("graph.txt");
         g.checkAllPairs();
      } catch (FileNotFoundException e) {
         System.out.println("Arquivo não encontrado: " + e.getMessage());
      }
   }

   public static void generateRandomGraph(int vertices, int edges, String filename) throws IOException {
      double probability = (double) edges / (vertices * (vertices - 1));
      Random rand = new Random();
      PrintWriter writer = new PrintWriter(new File(filename));

      for (int i = 0; i < vertices; i++) {
         for (int j = i + 1; j < vertices; j++) {
            if (rand.nextDouble() < probability) {
               writer.println(i + " " + j);
            }
         }
      }

      writer.close();
   }
}