import java.util.*;

public class metodoiii {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite o número de vértices: ");
        int vertices = scanner.nextInt();

        System.out.print("Digite o número de arestas: ");
        int arestas = scanner.nextInt();

        long startTime = System.nanoTime(); // Início da contagem do tempo

        Grafo grafo = criarGrafoAleatorio(vertices, arestas);

        // Encontrar a árvore geradora mínima usando o método de Tarjan
        List<Aresta> mst = Tarjan.tarjanMST(grafo);

        long endTime = System.nanoTime(); // Fim da contagem do tempo
        long duration = (endTime - startTime); // Tempo de execução em nanossegundos

        // Imprimir o resultado
        System.out.println("Arestas na árvore geradora mínima:");
        for (Aresta aresta : mst) {
            System.out.println("Aresta entre " + aresta.origem + " e " + aresta.destino + " com peso " + aresta.peso);
        }

        // Imprimir o tempo de execução
        System.out.println("Tempo de execução: " + duration + " nanossegundos");
    }

    private static Grafo criarGrafoAleatorio(int vertices, int arestas) {
        Random rand = new Random();
        List<Aresta> listaArestas = new ArrayList<>();

        // Geração aleatória de arestas
        for (int i = 0; i < arestas; i++) {
            int origem = rand.nextInt(vertices);
            int destino = rand.nextInt(vertices);
            int peso = rand.nextInt(100) + 1; // Peso entre 1 e 100
            listaArestas.add(new Aresta(origem, destino, peso));
        }

        return new Grafo(vertices, listaArestas);
    }
}

class Aresta {
    int origem;
    int destino;
    int peso;

    Aresta(int origem, int destino, int peso) {
        this.origem = origem;
        this.destino = destino;
        this.peso = peso;
    }
}

class Grafo {
    int vertices;
    List<Aresta> arestas;
    List<List<Integer>> listaAdjacencia;

    Grafo(int vertices, List<Aresta> arestas) {
        this.vertices = vertices;
        this.arestas = arestas;
        this.listaAdjacencia = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            listaAdjacencia.add(new ArrayList<>());
        }
        for (Aresta aresta : arestas) {
            listaAdjacencia.get(aresta.origem).add(aresta.destino);
            // Considerando grafo não direcionado
            listaAdjacencia.get(aresta.destino).add(aresta.origem);
        }
    }

    int getVertice() {
        return vertices;
    }

    List<Aresta> getArestas() {
        return arestas;
    }

    List<List<Integer>> getAdjList() {
        return listaAdjacencia;
    }
}
