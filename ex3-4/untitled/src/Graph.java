import java.util.*;

public class Graph<V, L> implements AbstractGraph<V, L> {
    private Map<V, Set<AbstractEdge<V, L>>> adiacencyList;
    private boolean directed;
    private boolean labelled;
    private int numEdges; //O(1)

    public Graph(boolean directed, boolean labelled) {
        this.adiacencyList = new HashMap<>();
        this.directed = directed;
        this.labelled = labelled;
        this.numEdges = 0;
    }


    @Override
    public boolean isDirected() {
        return this.directed;
    }

    @Override
    public boolean isLabelled() {
        return this.labelled;
    }

    @Override
    public boolean addNode(V a) {
        if (containsNode(a)) {
            return false;
        } else {
            this.adiacencyList.put(a, new HashSet<>());
            return true;
        }
    }

    @Override
    public boolean addEdge(V a, V b, L l) {
        if (containsEdge(a, b) || !containsNode(a) || !containsNode(b)) {//se abbiamo gia l'arco o se non abbiamo i nodi
            return false;
        } else {
            adiacencyList.get(a).add(new Edge<>(a, b, l)); //aggiungiamo l'arco da a in b
            if (!directed) {
                adiacencyList.get(b).add(new Edge<>(b, a, l)); //se non diretto aggiungiamo anche arco b in a
            }
            numEdges++;
            return true;
        }
    }

    @Override
    public boolean containsNode(V a) {
        return this.adiacencyList.containsKey(a);
    }

    @Override
    public boolean containsEdge(V a, V b) {
        if (!containsNode(a) || !containsNode(b)) {//inseriamo arco tra a e b solo se esistono i rispettivi nodi
            return false;
        }
        for (AbstractEdge<V, L> edge : adiacencyList.get(a)) { //Per ogni arco edge nella lista degli archi di a
            if (edge.getEnd().equals(b)) { //se esiste gia un arco che finisce in b allora true (ovvero esiste gia arco tra a e b)
                return true;
            }
        }
        return false; //false altrimenti
    }

    @Override
    public boolean removeNode(V a) {
        return false;
    }

    @Override
    public boolean removeEdge(V a, V b) {
        return false;
    }

    @Override
    public int numNodes() {
        return this.adiacencyList.size();
    }

    @Override
    public int numEdges() {
        return this.numEdges;
    }

    @Override
    public Collection<V> getNodes() {
        return null;
    }

    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        return null;
    }

    @Override
    public Collection<V> getNeighbours(V a) {
        return null;
    }

    @Override
    public L getLabel(V a, V b) {
        return null;
    }
}
