import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class metodoii {

    public static List<Integer> encontrarPontosDeArticulacao(int[][] grafo, int V) {
        List<Integer> pontosDeArticulacao = new ArrayList<>();

        for (int v = 0; v < V; v++) {
            if (ePontoDeArticulacao(grafo, V, v)) {
                pontosDeArticulacao.add(v);
            }
        }

        return pontosDeArticulacao;
    }

    private static boolean ePontoDeArticulacao(int[][] grafo, int V, int verticeRemovido) {
        boolean[] visitado = new boolean[V];
        int quantidadeAlcancavel = 0;

        for (int v = 0; v < V; v++) {
            if (v != verticeRemovido && !visitado[v]) {
                dfs(grafo, V, v, verticeRemovido, visitado);
                quantidadeAlcancavel++;
            }
        }

        return quantidadeAlcancavel > 1;
    }

    private static void dfs(int[][] grafo, int V, int v, int verticeRemovido, boolean[] visitado) {
        visitado[v] = true;
        for (int u = 0; u < V; u++) {
            if (u != verticeRemovido && grafo[v][u] == 1 && !visitado[u]) {
                dfs(grafo, V, u, verticeRemovido, visitado);
            }
        }
    }

    public static int[][] gerarGrafoAPartirDeArestas(List<int[]> arestas, int V) {
        int maxVertice = 0;
        for (int[] aresta : arestas) {
            maxVertice = Math.max(maxVertice, Math.max(aresta[0], aresta[1]));
        }
        int[][] grafo = new int[maxVertice + 1][maxVertice + 1];

        for (int[] aresta : arestas) {
            int v = aresta[0];
            int u = aresta[1];
            grafo[v][u] = 1;
            grafo[u][v] = 1;
        }

        return grafo;
    }

    public static List<int[]> lerArestasDeArquivo(String nomeArquivo) throws FileNotFoundException {
        List<int[]> arestas = new ArrayList<>();
        File arquivo = new File(nomeArquivo);
        Scanner scanner = new Scanner(arquivo);
        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            String[] partes = linha.split(" ");
            int v = Integer.parseInt(partes[0]);
            int u = Integer.parseInt(partes[1]);
            arestas.add(new int[]{v, u});
        }
        scanner.close();
        return arestas;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o caminho completo do arquivo contendo a lista de arestas: ");
        String caminhoArquivo = scanner.nextLine();

        List<int[]> arestas;
        try {
            arestas = lerArestasDeArquivo(caminhoArquivo);
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado!");
            return;
        }

        int maxVertice = 0;
        for (int[] aresta : arestas) {
            maxVertice = Math.max(maxVertice, Math.max(aresta[0], aresta[1]));
        }
        int V = maxVertice + 1;

        int[][] grafo = gerarGrafoAPartirDeArestas(arestas, V);

        long inicioExecucao = System.currentTimeMillis();
        List<Integer> pontosDeArticulacao = encontrarPontosDeArticulacao(grafo, V);
        long fimExecucao = System.currentTimeMillis();
        long tempoExecucao = fimExecucao - inicioExecucao;

        if (pontosDeArticulacao.isEmpty()) {
            System.out.println("Não há pontos de articulação neste grafo.");
        } else {
            System.out.println("Pontos de articulação encontrados nos vértices: " + pontosDeArticulacao);
        }

        List<Integer> verticesFalhados = new ArrayList<>();
        for (int v = 0; v < V; v++) {
            if (!pontosDeArticulacao.contains(v)) {
                verticesFalhados.add(v);
            }
        }

        if (!verticesFalhados.isEmpty()) {
            System.out.println("Vertices que falharam no teste: " + verticesFalhados);
        }

        System.out.println("Tempo de execução: " + tempoExecucao + " milissegundos.");
    }
}
