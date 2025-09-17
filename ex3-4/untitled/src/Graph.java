import java.util.*;

/**
 * A concrete implementation of a graph data structure using an adjacency list.
 *
 * This class represents a graph that can be either directed or undirected,
 * and labelled or unlabelled. It stores nodes of type V and edges with labels of type L.
 * The graph uses a HashMap to store adjacency lists for efficient node and edge operations.
 *
 * @param <V> the type of the vertices/nodes in the graph
 * @param <L> the type of the labels associated with edges
 */
public class Graph<V, L> implements AbstractGraph<V, L> {
    private Map<V, Set<AbstractEdge<V, L>>> adiacencyList;
    private boolean directed;
    private boolean labelled;
    private int numEdges; // O(1) edge count for efficient size queries

    /**
     * Constructs a new graph with the specified properties.
     *
     * @param directed true if the graph should be directed, false for undirected
     * @param labelled true if edges should have labels, false for unlabelled edges
     */
    public Graph(boolean directed, boolean labelled) {
        this.adiacencyList = new HashMap<>();
        this.directed = directed;
        this.labelled = labelled;
        this.numEdges = 0;
    }

    /**
     * Returns whether this graph is directed.
     *
     * @return true if the graph is directed, false otherwise
     */
    @Override
    public boolean isDirected() {
        return this.directed;
    }

    /**
     * Returns whether this graph has labelled edges.
     *
     * @return true if edges are labelled, false otherwise
     */
    @Override
    public boolean isLabelled() {
        return this.labelled;
    }

    /**
     * Adds a node to the graph.
     *
     * @param a the node to be added
     * @return true if the node was added successfully, false if the node already exists
     */
    @Override
    public boolean addNode(V a) {
        if (containsNode(a)) {
            return false;
        } else {
            this.adiacencyList.put(a, new HashSet<>());
            return true;
        }
    }

    /**
     * Adds an edge between two nodes with an optional label.
     *
     * @param a the starting node of the edge
     * @param b the ending node of the edge
     * @param l the label for the edge (must be non-null for labelled graphs, ignored for unlabelled graphs)
     * @return true if the edge was added successfully, false if the edge already exists or nodes don't exist
     * @throws IllegalArgumentException if the graph is labelled and a null label is provided
     */
    @Override
    public boolean addEdge(V a, V b, L l) {
        if (containsEdge(a, b) || !containsNode(a) || !containsNode(b)) {
            return false;
        }
        if (isLabelled()) { // If graph is labelled
            if (l == null) { // Edge must have a label
                return false;
            }
        } else {
            l = null; // If unlabelled, label must always be null
        }
        adiacencyList.get(a).add(new Edge<>(a, b, l)); // Add edge
        if (!directed) { // If undirected graph, add reverse edge
            adiacencyList.get(b).add(new Edge<>(b, a, l));
        }
        numEdges++;
        return true;
    }

    /**
     * Checks if a node exists in the graph.
     *
     * @param a the node to check
     * @return true if the node exists, false otherwise
     */
    @Override
    public boolean containsNode(V a) {
        return this.adiacencyList.containsKey(a);
    }

    /**
     * Checks if an edge exists between two nodes.
     *
     * @param a the starting node
     * @param b the ending node
     * @return true if an edge exists from a to b, false otherwise
     */
    @Override
    public boolean containsEdge(V a, V b) {
        if (!containsNode(a) || !containsNode(b)) {
            return false;
        }
        for (AbstractEdge<V, L> edge : adiacencyList.get(a)) {
            if (edge.getEnd().equals(b)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Removes a node and all associated edges from the graph.
     *
     * @param a the node to remove
     * @return true if the node was removed successfully, false if the node doesn't exist
     */
    @Override
    public boolean removeNode(V a) {
        if (!containsNode(a)) return false;

        // 1. Remove outgoing edges
        for (V neighbor : getNeighbours(a)) {
            removeEdge(a, neighbor);
        }
        // 2. Remove remaining incoming edges (only for directed graphs)
        if (directed) {
            for (V node : adiacencyList.keySet()) {
                if (!node.equals(a)) {
                    adiacencyList.get(node).removeIf(edge -> {
                        if (edge.getEnd().equals(a)) {
                            numEdges--;
                            return true;
                        }
                        return false;
                    });
                }
            }
        }
        // 3. Remove node after removing all edges
        adiacencyList.remove(a);
        return true;
    }

    /**
     * Removes an edge between two nodes.
     *
     * @param a the starting node
     * @param b the ending node
     * @return true if the edge was removed successfully, false if the edge doesn't exist
     */
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

    /**
     * Returns the number of nodes in the graph.
     *
     * @return the number of nodes
     */
    @Override
    public int numNodes() {
        return this.adiacencyList.size();
    }

    /**
     * Returns the number of edges in the graph.
     *
     * @return the number of edges
     */
    @Override
    public int numEdges() {
        return this.numEdges;
    }

    /**
     * Returns a collection of all nodes in the graph.
     *
     * @return a collection containing all nodes
     */
    @Override
    public Collection<V> getNodes() {
        return adiacencyList.keySet();
    }

    /**
     * Returns a collection of all edges in the graph.
     *
     * @return a collection containing all edges
     */
    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        Set<AbstractEdge<V, L>> allEdges = new HashSet<>();
        for (Set<AbstractEdge<V, L>> outgoingEdges : adiacencyList.values()) {//iteara su tutti i valori della adiacency list
            allEdges.addAll(outgoingEdges);//agginge tutti gli archi
        }
        return allEdges;
    }

    /**
     * Returns the neighbors of a given node.
     *
     * @param a the node whose neighbors are to be returned
     * @return a collection of neighboring nodes, empty collection if the node doesn't exist
     */
    @Override
    public Collection<V> getNeighbours(V a) {
        Set<V> neighbours = new HashSet<>();
        if (containsNode(a)) {
            for (AbstractEdge<V, L> edge : adiacencyList.get(a)) {
                neighbours.add(edge.getEnd());
            }
        }
        return neighbours;
    }

    /**
     * Returns the label of the edge between two nodes.
     *
     * @param a the starting node
     * @param b the ending node
     * @return the label of the edge, or null if the edge doesn't exist or the graph is unlabelled
     */
    @Override
    public L getLabel(V a, V b) {
        if (isLabelled() && containsEdge(a, b)) {
            for (AbstractEdge<V, L> edge : adiacencyList.get(a)) {
                if (edge.getEnd().equals(b)) {
                    return edge.getLabel();
                }
            }
        }
        return null;
    }
}
