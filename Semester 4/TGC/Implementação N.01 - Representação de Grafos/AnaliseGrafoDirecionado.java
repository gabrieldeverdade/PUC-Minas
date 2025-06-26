import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class AnaliseGrafoDirecionado {

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);

        // Leitura do nome do arquivo e do vértice
        System.out.println("Digite o nome do arquivo com os dados do grafo: ");
        String nomeArquivo = scanner.nextLine();
        System.out.println("Digite o número do vértice: ");
        int vertice = scanner.nextInt();

        // Leitura do grafo
        Map<Integer, HashSet<Integer>> grafo = lerGrafo(nomeArquivo);

        // Cálculo do grau de saída
        int grauSaida = grauSaida(grafo, vertice);

        // Cálculo do grau de entrada
        int grauEntrada = grauEntrada(grafo, vertice);

        // Obtenção dos sucessores
        HashSet<Integer> sucessores = sucessores(grafo, vertice);

        // Obtenção dos predecessores
        HashSet<Integer> predecessores = predecessores(grafo, vertice);

        // Impressão das informações básicas
        System.out.println("Grau de saída: " + grauSaida);
        System.out.println("Grau de entrada: " + grauEntrada);
        System.out.println("Sucessores: " + sucessores);
        System.out.println("Predecessores: " + predecessores);
    }

    private static Map<Integer, HashSet<Integer>> lerGrafo(String nomeArquivo) throws IOException {
        Map<Integer, HashSet<Integer>> grafo = new HashMap<>();
        try (BufferedReader br = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha = br.readLine();
            String[] partes = linha.split(" ");
            int nVertices = Integer.parseInt(partes[0]);
            int mArestas = Integer.parseInt(partes[1]);

            for (int i = 0; i < mArestas; i++) {
                linha = br.readLine();
                partes = linha.split(" ");
                int origem = Integer.parseInt(partes[0]);
                int destino = Integer.parseInt(partes[1]);

                grafo.putIfAbsent(origem, new HashSet<>());
                grafo.get(origem).add(destino);
            }
        }
        return grafo;
    }

    private static int grauSaida(Map<Integer, HashSet<Integer>> grafo, int vertice) {
        return grafo.getOrDefault(vertice, new HashSet<>()).size();
    }

    private static int grauEntrada(Map<Integer, HashSet<Integer>> grafo, int vertice) {
        int grauEntrada = 0;
        for (HashSet<Integer> adjacencias : grafo.values()) {
            if (adjacencias.contains(vertice)) {
                grauEntrada++;
            }
        }
        return grauEntrada;
    }

    private static HashSet<Integer> sucessores(Map<Integer, HashSet<Integer>> grafo, int vertice) {
        return grafo.getOrDefault(vertice, new HashSet<>());
    }

    private static HashSet<Integer> predecessores(Map<Integer, HashSet<Integer>> grafo, int vertice) {
        HashSet<Integer> predecessores = new HashSet<>();
        for (Map.Entry<Integer, HashSet<Integer>> entrada : grafo.entrySet()) {
            if (entrada.getValue().contains(vertice)) {
                predecessores.add(entrada.getKey());
            }
        }
        return predecessores;
    }
}
