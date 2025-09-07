/**
 * A concrete implementation of an edge in a graph.
 *
 * This class represents a directed edge between two vertices, with an associated label.
 * The edge is characterized by a start vertex, an end vertex, and a label.
 *
 * @param <V> the type of the vertices connected by this edge
 * @param <L> the type of the label associated with this edge
 */
public class Edge<V, L> implements AbstractEdge<V, L>{
    private V start;
    private V end;
    private L label;

    /**
     * Constructs a new edge with the specified start vertex, end vertex, and label.
     *
     * @param start the starting vertex of this edge; must not be null
     * @param end the ending vertex of this edge; must not be null
     * @param label the label associated with this edge; can be null
     * @throws NullPointerException if the start or end vertex is null
     */
    public Edge(V start, V end, L label) {
        this.start = start;
        this.end = end;
        this.label = label;
    }

    /**
     * Returns the starting vertex of this edge.
     *
     * @return the start vertex; never null
     */
    @Override
    public V getStart() {
        return this.start;
    }

    /**
     * Returns the ending vertex of this edge.
     *
     * @return the end vertex; never null
     */
    @Override
    public V getEnd() {
        return this.end;
    }

    /**
     * Returns the label associated with this edge.
     *
     * @return the label of this edge; can be null
     */
    @Override
    public L getLabel() {
        return this.label;
    }
}
