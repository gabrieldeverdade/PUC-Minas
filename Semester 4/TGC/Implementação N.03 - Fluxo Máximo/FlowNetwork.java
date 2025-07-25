/******************************************************************************
 *  Compilation:  javac FlowNetwork.java
 *  Execution:    java FlowNetwork V E
 *  Dependencies: Bag.java FlowEdge.java
 *
 *  A capacitated flow network, implemented using adjacency lists.
 *
 ******************************************************************************/

import java.util.LinkedList;
import java.util.List;

/**
 *  The {@code FlowNetwork} class represents a capacitated network
 *  with vertices named 0 through <em>V</em> - 1, where each directed
 *  edge is of type {@link FlowEdge} and has a real-valued capacity
 *  and flow.
 *  It supports the following two primary operations: add an edge to the network,
 *  iterate over all of the edges incident to or from a vertex. It also provides
 *  methods for returning the number of vertices <em>V</em> and the number
 *  of edges <em>E</em>. Parallel edges and self-loops are permitted.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the edges incident to a given vertex, which takes
 *  time proportional to the number of such edges.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/64maxflow">Section 6.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
public class FlowNetwork {
    private static final String NEWLINE = System.getProperty("line.separator");

    private final int V;
    private int E;
    private Bag<FlowEdge>[] adj;

    /**
     * Initializes an empty flow network with {@code V} vertices and 0 edges.
     * @param V the number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    @SuppressWarnings("unchecked")
    public FlowNetwork(int V) {
        if (V < 0) throw new IllegalArgumentException("Number of vertices in a Graph must be non-negative");
        this.V = V;
        this.E = 0;
        adj = (Bag<FlowEdge>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<FlowEdge>();
    }

    /**
     * Initializes a random flow network with {@code V} vertices and <em>E</em> edges.
     * The capacities are integers between 0 and 99 and the flow values are zero.
     * @param V the number of vertices
     * @param E the number of edges
     * @throws IllegalArgumentException if {@code V < 0}
     * @throws IllegalArgumentException if {@code E < 0}
     */
    // public FlowNetwork(int V, int E) {
    //     this(V);
    //     if (E < 0) throw new IllegalArgumentException("Number of edges must be non-negative");
    //     for (int i = 0; i < E; i++) {
    //         int v = StdRandom.uniformInt(V);
    //         int w = StdRandom.uniformInt(V);
    //         double capacity = StdRandom.uniformInt(100);
    //         addEdge(new FlowEdge(v, w, capacity));
    //     }
    // }
    

@SuppressWarnings("unchecked")
public FlowNetwork(ForwardStar fs) {
        if (fs == null) throw new IllegalArgumentException("argument is null");
      
            this.V = fs.V;
            if (V < 0) throw new IllegalArgumentException("number of vertices in a Graph must be non-negative");
            adj = (Bag<FlowEdge>[]) new Bag[V+1];
            for (int v = 1; v <= V; v++) {
                adj[v] = new Bag<FlowEdge>();
            }
            int E = fs.E;
            if (E < 0) throw new IllegalArgumentException("number of edges in a Graph must be non-negative");
            for (int i = 1; i <= V; i++) {
                int[]vizinhos=fs.listaSucessores(i);
                for (int j = 0; j < vizinhos.length; j++) {
                    validateVertex(i);
                    validateVertex(vizinhos[j]);
                    addEdge(new FlowEdge(i, vizinhos[j],1));
                }

            }
        }
    /**
     * Initializes a flow network from an input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices and edge capacities,
     * with each entry separated by whitespace.
     * @param in the input stream
     * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     */
    // public FlowNetwork(In in) {
    //     this(in.readInt());
    //     int E = in.readInt();
    //     if (E < 0) throw new IllegalArgumentException("number of edges must be non-negative");
    //     for (int i = 0; i < E; i++) {
    //         int v = in.readInt();
    //         int w = in.readInt();
    //         validateVertex(v);
    //         validateVertex(w);
    //         double capacity = in.readDouble();
    //         addEdge(new FlowEdge(v, w, capacity));
    //     }
    // }


    /**
     * Returns the number of vertices in the edge-weighted graph.
     * @return the number of vertices in the edge-weighted graph
     */
    public int V() {
        return V;
    }

    /**
     * Returns the number of edges in the edge-weighted graph.
     * @return the number of edges in the edge-weighted graph
     */
    public int E() {
        return E;
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    private void validateVertex(int v) {
        if (v < 0 || v > V)
            throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V));
    }

    /**
     * Adds the edge {@code e} to the network.
     * @param e the edge
     * @throws IllegalArgumentException unless endpoints of edge are between
     *         {@code 0} and {@code V-1}
     */
    public void addEdge(FlowEdge e) {
        
        int v = e.from();
        int w = e.to();
        try{
        validateVertex(v);
        validateVertex(w);
        adj[v].add(e);
        adj[w].add(e);
        E++;
        }catch(Exception exception)
        {
            System.err.println("Deu pepino: e" +e+" v "+v+" w "+w);
        }
    }

    /**
     * Returns the edges incident on vertex {@code v} (includes both edges pointing to
     * and from {@code v}).
     * @param v the vertex
     * @return the edges incident on vertex {@code v} as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    public Iterable<FlowEdge> adj(int v) {
        validateVertex(v);
        return adj[v];
    }

    // return list of all edges - excludes self loops
    public Iterable<FlowEdge> edges() {
        Bag<FlowEdge> list = new Bag<FlowEdge>();
        for (int v = 0; v < V; v++)
            for (FlowEdge e : adj(v)) {
                if (e.to() != v)
                    list.add(e);
            }
        return list;
    }


    /**
     * Returns a string representation of the flow network.
     * This method takes time proportional to <em>E</em> + <em>V</em>.
     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
     *    followed by the <em>V</em> adjacency lists
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(V + " " + E + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append(v + ":  ");
            for (FlowEdge e : adj[v]) {
                if (e.to() != v) s.append(e + "  ");
            }
            s.append(NEWLINE);
        }
        return s.toString();
    } 
    public List<List<Integer>> listaCaminhosDisjuntos(int s, int t) {
        List<List<Integer>> resposta=new LinkedList<List<Integer>>();
        
        for (FlowEdge e:adj[t]) {
            if(e.flow()>0)
            {
                // System.out.println(e);
                List<Integer> lista=new LinkedList<>();
                lista.add(t);
                encontraUmCaminho(lista, e.other(t),s);
                resposta.add(lista);
            }
        }
        return resposta;
    }

    private void encontraUmCaminho(List<Integer> lista,int i,int s) {
        lista.add(i);
        if(i==s){
            return;
        }
       
        for (FlowEdge e:adj[i]) {
            // System.out.println(e);
            if(e.flow()>0&&e.from()!=i)
            
            {
                encontraUmCaminho(lista,e.from(),s);
                break;
            }
        }
    }

}



