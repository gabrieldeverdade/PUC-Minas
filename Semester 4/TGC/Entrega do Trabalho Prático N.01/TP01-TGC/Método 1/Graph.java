import java.util.*;
import java.io.*;

public class Graph {
    private int V; // Número de vértices
    private LinkedList<Integer> adj[]; // Lista de adjacências
    private int time = 0; // Adicionado

    public static void main(String[] args) {
        int[] vertices = {100, 1000, 10000, 100000};
    
        for (int v : vertices) {
            Graph g = new Graph(v);
    
            // Gera um grafo aleatório
            Random rand = new Random();
            for (int i = 0; i < v; i++) {
                for (int j = i + 1; j < v; j++) {
                    if (rand.nextBoolean()) {
                        g.addEdge(i, j);
                    }
                }
            }
    
            System.out.println("Grafo com " + v + " vértices:");
            g.checkAllPairs();
        }
    }
    
    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }

    void addEdge(int v, int w) { // Adiciona uma aresta ao grafo
        adj[v].add(w);
        adj[w].add(v);
    }

    boolean isBCUtil(int u, int parent[], boolean visited[], int disc[], int low[], boolean ap[]) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        Iterator<Integer> i = adj[u].iterator();
        while (i.hasNext()) {
            int v = i.next();
            if (!visited[v]) {
                children++;
                parent[v] = u;
                isBCUtil(v, parent, visited, disc, low, ap); // Modificado

                low[u] = Math.min(low[u], low[v]);

                if (parent[u] == -1 && children > 1) // Modificado
                    ap[u] = true;

                if (parent[u] != -1 && low[v] >= disc[u]) // Modificado
                    ap[u] = true;
            }
            else if (v != parent[u])
                low[u] = Math.min(low[u], disc[v]);
        }
        return false; // Adicionado para evitar erro de compilação, você pode precisar ajustar isso dependendo da lógica desejada
    }

    void isBC() {
        boolean visited[] = new boolean[V];
        int disc[] = new int[V];
        int low[] = new int[V];
        int parent[] = new int[V];
        boolean ap[] = new boolean[V];
    
        for (int i = 0; i < V; i++) {
            parent[i] = -1; // Modificado
            visited[i] = false;
            ap[i] = false;
        }
    
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                isBCUtil(i, parent, visited, disc, low, ap); // Modificado
    
        for (int i = 0; i < V; i++)
            if (ap[i] == true)
                System.out.println(i);
    }

    // Código adicional para verificar a existência de dois caminhos internamente disjuntos
    boolean isTwoPaths(int u, int v) {
        LinkedList<Integer> path1 = new LinkedList<>();
        LinkedList<Integer> path2 = new LinkedList<>();

        boolean visited[] = new boolean[V];

        if (findPathUtil(u, v, visited, path1)) {
            // Limpa o array de visitados
            Arrays.fill(visited, false);

            // Marca os vértices no primeiro caminho como visitados
            for (int vertex : path1) {
                visited[vertex] = true;
            }

            // Remove o início e o fim do caminho
            visited[u] = false;
            visited[v] = false;

            if (findPathUtil(u, v, visited, path2)) {
                return true;
            }
        }

        return false;
    }

    private boolean findPathUtil(int u, int v, boolean visited[], LinkedList<Integer> path) {
        visited[u] = true;
        path.add(u);

        if (u == v)
            return true;

        Iterator<Integer> i = adj[u].iterator();
        while (i.hasNext()) {
            int w = i.next();
            if (!visited[w]) {
                if (findPathUtil(w, v, visited, path))
                    return true;
            }
        }

        path.removeLast();
        visited[u] = false;
        return false;
    }

    void checkAllPairs() {
        long total_time = 0;
        int count = 0;

        for (int u = 0; u < V; u++) {
            for (int v = u + 1; v < V; v++) {
                long start_time = System.nanoTime();
                boolean result = isTwoPaths(u, v);
                long end_time = System.nanoTime();

                total_time += (end_time - start_time);
                count++;

                if (result) {
                    System.out.println("Existem dois caminhos internamente disjuntos entre " + u + " e " + v);
                }
            }
        }

        double average_time = (double)total_time / count;
        System.out.println("Tempo médio: " + average_time + " nanosegundos");
    }

    public static Graph fromFile(String filename) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(filename));

        int maxVertex = -1;
        List<int[]> edges = new ArrayList<>();
        while (scanner.hasNextInt()) {
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            edges.add(new int[]{v, w});
            if (v > maxVertex) maxVertex = v;
            if (w > maxVertex) maxVertex = w;
        }

        Graph g = new Graph(maxVertex + 1);
        for (int[] edge : edges) {
            g.addEdge(edge[0], edge[1]);
        }

        return g;
    }

    public static void generateRandomGraph(int vertices, String filename) throws IOException {
        Random rand = new Random();
        PrintWriter writer = new PrintWriter(new File(filename));

        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (rand.nextBoolean()) {
                    writer.println(i + " " + j);
                }
            }
        }

        writer.close();
    }
}