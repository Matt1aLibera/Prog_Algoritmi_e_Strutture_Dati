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
        if (containsEdge(a, b) || !containsNode(a) || !containsNode(b)) {
            return false;
        }
        if (isLabelled()) {//se grafo etichettato
            if (l == null) { // l'arco deve per forza contenere un etichetta
                return false;
            }
        } else {
            l = null; //se non etichettato allora l'etichetta deve essere sempre null
        }
        adiacencyList.get(a).add(new Edge<>(a, b, l));//aggiungo arco
        if (!directed) {// Se grafo non diretto, aggiungi l'arco inverso
            adiacencyList.get(b).add(new Edge<>(b, a, l));
        }
        numEdges++;
        return true;
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
        if (!containsNode(a)) return false;

        // 1. Rimozione archi uscenti
        for (V neighbor : getNeighbours(a)) {  // per ogni nodo vicino di a
            removeEdge(a, neighbor);  // cancello l'arco tra a e il suo vicino (e viceversa se grafo non diretto)
        }
        // 2. Rimozione archi entranti rimanenti (ne rimangono solo se il grafo è diretto)
        if(directed) {
            for (V node : adiacencyList.keySet()) {  // per ogni nodo nella lista di adiacenza
                if (!node.equals(a)) {  // che non sia il nodo da rimuovere
                    adiacencyList.get(node).removeIf(edge -> {  // rimuoviamo l'arco del nodo se:
                        if (edge.getEnd().equals(a)) {          // è un arco entrante nel nodo da cancellare
                            numEdges--;  // aggiorno contatore di archi
                            return true; //allora cancello l'arco
                        }
                        return false;    //non lo rimuovo altrimenti
                    });
                }
            }
        }
        // 3. Rimozione nodo dopo aver rimosso gli archi
        adiacencyList.remove(a);
        return true;
    }

    @Override
    public boolean removeEdge(V a, V b) {
        if (containsEdge(a, b)) {
            adiacencyList.get(a).removeIf(edge -> edge.getEnd().equals(b));
            if (!directed) {
                adiacencyList.get(b).removeIf(edge -> edge.getEnd().equals(a));
            }
            numEdges--;
            return true;
        }
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
        return adiacencyList.keySet();
    }

    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        Set<AbstractEdge<V, L>> allEdges = new HashSet<>();
        for (Set<AbstractEdge<V, L>> outgoingEdges : adiacencyList.values()) {
            allEdges.addAll(outgoingEdges);
        }
        return allEdges;

    }

    @Override
    public Collection<V> getNeighbours(V a) {
        Set<V> neighbours = new HashSet<>();
        if (containsNode(a)) {
            for (AbstractEdge<V, L> edge : adiacencyList.get(a)) { //per ogni arco del nodo a
                neighbours.add(edge.getEnd());//estraiamo tutti i nodi in cui entra l'arco (ovvero i vicini di a)
            }
        }
        return neighbours;
    }

    @Override
    public L getLabel(V a, V b) {
        if (isLabelled() && containsEdge(a, b)) { // se labelled e contiene l'arco da a in b
            for (AbstractEdge<V, L> edge : adiacencyList.get(a)) { //per ogni arco del nodo a
                if (edge.getEnd().equals(b)) { //se troviamo quello che ci interessa (da a in b)
                    return edge.getLabel(); //ritorniamo la sua label
                }
            }
        }
        return null;
    }
}
