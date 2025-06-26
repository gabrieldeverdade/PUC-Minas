import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Aresta {
    int de, para;

    Aresta(int de, int para) {
        this.de = de;
        this.para = para;
    }
}

class Grafo {
    private List<List<Integer>> listaAdjacencia;
    private List<Aresta> arestas;
    private boolean[] visitado;
    private List<Aresta> arestasArvore;
    private List<Aresta> arestasDivergentes;

    Grafo(int n) {
        listaAdjacencia = new ArrayList<>();
        arestas = new ArrayList<>();
        visitado = new boolean[n + 1];
        arestasArvore = new ArrayList<>();
        arestasDivergentes = new ArrayList<>();

        for (int i = 0; i <= n; i++) {
            listaAdjacencia.add(new ArrayList<>());
        }
    }

    void adicionarAresta(int de, int para) {
        listaAdjacencia.get(de).add(para);
        arestas.add(new Aresta(de, para));
    }

    void DFS(int v) {
        visitado[v] = true;
        for (int u : listaAdjacencia.get(v)) {
            if (!visitado[u]) {
                arestasArvore.add(new Aresta(v, u));
                DFS(u);
            } else {
                Aresta aresta = new Aresta(v, u);
                if (!arestas.contains(aresta)) {
                    arestasDivergentes.add(aresta);
                }
            }
        }
    }

    void imprimirArestasArvore() {
        System.out.println("Arestas da Árvore:");
        for (Aresta aresta : arestasArvore) {
            System.out.println(aresta.de + " -> " + aresta.para);
        }
    }

    void imprimirArestasDivergentes() {
        System.out.println("Arestas Divergentes do vértice escolhido:");
        for (Aresta aresta : arestasDivergentes) {
            System.out.println(aresta.de + " -> " + aresta.para);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o nome do arquivo: ");
        String nomeArquivo = scanner.nextLine().trim();
        System.out.print("Digite o número do vértice: ");
        int vertice = scanner.nextInt();

        try {
            File arquivo = new File(nomeArquivo);
            Scanner leitorArquivo = new Scanner(arquivo);

            int n = leitorArquivo.nextInt();
            int m = leitorArquivo.nextInt();

            Grafo grafo = new Grafo(n);

            for (int i = 0; i < m; i++) {
                int de = leitorArquivo.nextInt();
                int para = leitorArquivo.nextInt();
                grafo.adicionarAresta(de, para);
            }

            grafo.DFS(vertice);

            grafo.imprimirArestasArvore();
            grafo.imprimirArestasDivergentes();

            leitorArquivo.close();
        } catch (FileNotFoundException e) {
            System.err.println("Erro ao abrir o arquivo.");
            e.printStackTrace();
        }
    }
}
