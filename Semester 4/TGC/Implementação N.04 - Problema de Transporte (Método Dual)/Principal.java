import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class ProblemaTransporte {
    private int m, n; // m: pontos de oferta, n: pontos de demanda
    private int[] oferta;
    private int[] demanda;
    private int[][] custo;

    public ProblemaTransporte(int m, int n, int[] oferta, int[] demanda, int[][] custo) {
        this.m = m;
        this.n = n;
        this.oferta = oferta;
        this.demanda = demanda;
        this.custo = custo;
    }

    public void verificarBalanceamento() {
        int totalOferta = 0, totalDemanda = 0;
        for (int valor : oferta) totalOferta += valor;
        for (int valor : demanda) totalDemanda += valor;

        if (totalOferta > totalDemanda) {
            balancearComDemandaFicticia(totalOferta - totalDemanda);
        } else if (totalDemanda > totalOferta) {
            balancearComOfertaFicticia(totalDemanda - totalOferta);
        } else {
            System.out.println("Problema balanceado.");
        }
    }

    private void balancearComDemandaFicticia(int excesso) {
        System.out.println("Problema desbalanceado: excesso de oferta detectado. Adicionando demanda fictícia.");
        int novaDemanda[] = new int[n + 1];
        System.arraycopy(demanda, 0, novaDemanda, 0, n);
        novaDemanda[n] = excesso;

        int novoCusto[][] = new int[m][n + 1];
        for (int i = 0; i < m; i++) {
            System.arraycopy(custo[i], 0, novoCusto[i], 0, n);
            novoCusto[i][n] = 0; // Custo zero para demanda fictícia
        }

        n += 1;
        demanda = novaDemanda;
        custo = novoCusto;
    }

    private void balancearComOfertaFicticia(int excesso) {
        System.out.println("Problema desbalanceado: excesso de demanda detectado. Adicionando oferta fictícia.");
        int novaOferta[] = new int[m + 1];
        System.arraycopy(oferta, 0, novaOferta, 0, m);
        novaOferta[m] = excesso;

        int novoCusto[][] = new int[m + 1][n];
        for (int i = 0; i < m; i++) {
            System.arraycopy(custo[i], 0, novoCusto[i], 0, n);
        }
        for (int j = 0; j < n; j++) {
            novoCusto[m][j] = 0; // Custo zero para oferta fictícia
        }

        m += 1;
        oferta = novaOferta;
        custo = novoCusto;
    }

    public void resolverMetodoDual() {
        System.out.println("Resolvendo problema de transporte usando o método dual...");
        
        int custoTotal = 0;
        int[][] solucao = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (oferta[i] > 0 && demanda[j] > 0) {
                    int transp = Math.min(oferta[i], demanda[j]);
                    solucao[i][j] = transp;
                    custoTotal += transp * custo[i][j];
                    oferta[i] -= transp;
                    demanda[j] -= transp;
                }
            }
        }

        System.out.println("Custo total do transporte: " + custoTotal);
        for (int[] linha : solucao) {
            for (int valor : linha) {
                System.out.print(valor + " ");
            }
            System.out.println();
        }
    }
}

class LeitorArquivo {
    public static ProblemaTransporte lerDoArquivo(String nomeArquivo) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(nomeArquivo));
        int m = scanner.nextInt();
        int n = scanner.nextInt();

        int[] oferta = new int[m];
        for (int i = 0; i < m; i++) {
            oferta[i] = scanner.nextInt();
        }

        int[] demanda = new int[n];
        for (int j = 0; j < n; j++) {
            demanda[j] = scanner.nextInt();
        }

        int[][] custo = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                custo[i][j] = scanner.nextInt();
            }
        }

        scanner.close();
        return new ProblemaTransporte(m, n, oferta, demanda, custo);
    }
}

public class Principal {
    public static void main(String[] args) {
        try {
            ProblemaTransporte problema = LeitorArquivo.lerDoArquivo("transporte_balanceado.txt");
            problema.verificarBalanceamento();
            problema.resolverMetodoDual();
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado: " + e.getMessage());
        }
    }
}
