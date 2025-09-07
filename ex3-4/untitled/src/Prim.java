import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Implementation of Prim's algorithm for finding Minimum Spanning Trees (MST)
 * and Minimum Spanning Forests (MSF) in undirected, weighted graphs.
 *
 * This class provides functionality to:
 * - Load graph data from CSV files
 * - Compute minimum spanning forests using Prim's algorithm
 * - Output results in CSV format with statistical information
 *
 * The algorithm handles both connected graphs (producing a single MST) and
 * disconnected graphs (producing a MSF with multiple trees).
 */
public class Prim {

    /**
     * Loads graph data from a CSV file and populates the provided graph.
     *
     * The expected CSV format is: "source,target,weight" per line.
     * Spaces around commas are automatically trimmed.
     *
     * @param filePath the path to the CSV file containing graph data
     * @param graph the graph to populate with nodes and edges
     * @throws IOException if an I/O error occurs reading the file
     * @throws IllegalArgumentException if the file format is invalid
     */
    public static void loadGraphAndPopulate(String filePath, Graph<String, Double> graph) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            br.lines()
                    .filter(line -> !line.trim().isEmpty())  // Ignore empty lines
                    .forEach(line -> {
                        String[] parts = line.split("\\s*,\\s*");  // Split ignoring spaces
                        if (parts.length != 3) {
                            throw new IllegalArgumentException("Invalid line format: " + line);
                        }
                        try {
                            String source = parts[0];
                            String target = parts[1];
                            double weight = Double.parseDouble(parts[2]);

                            // Add nodes if they don't exist (idempotent)
                            graph.addNode(source);
                            graph.addNode(target);

                            // Add edge
                            graph.addEdge(source, target, weight);
                        } catch (NumberFormatException e) {
                            throw new IllegalArgumentException("Non-numeric weight in line: " + line, e);
                        }
                    });
        }
    }

    /**
     * Comparator for comparing edges based on their numeric labels (weights).
     * Used by the priority queue to always select the edge with minimum weight.
     *
     * @param <V> the type of vertices
     * @param <L> the type of edge labels (must extend Number)
     */
    static class DoubleEdgeComparator<V, L> implements Comparator<Edge<V, L>> {
        /**
         * Compares two edges based on their numeric labels.
         *
         * @param e1 the first edge to compare
         * @param e2 the second edge to compare
         * @return a negative integer, zero, or positive integer as the first edge's
         *         weight is less than, equal to, or greater than the second edge's weight
         */
        @Override
        public int compare(Edge<V, L> e1, Edge<V, L> e2) {
            return Double.compare((Double) e1.getLabel(), (Double) e2.getLabel());
        }
    }

    /**
     * Computes the Minimum Spanning Forest (MSF) of an undirected weighted graph
     * using Prim's algorithm.
     *
     * For connected graphs, this returns a single Minimum Spanning Tree (MST).
     * For disconnected graphs, this returns a forest of MSTs for each connected component.
     *
     * @param <V> the type of vertices in the graph
     * @param <L> the type of edge labels (must extend Number)
     * @param graph the input graph (must be undirected and weighted)
     * @return a collection of edges forming the Minimum Spanning Forest
     * @throws RuntimeException if the graph contains invalid data
     */
    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        List<AbstractEdge<V, L>> minimumSpanningForest = new ArrayList<>();
        if (graph == null || graph.numNodes() == 0) {
            return minimumSpanningForest;
        }

        try {
            PriorityQueue<Edge<V, L>> priorityQueue = new PriorityQueue<>(new DoubleEdgeComparator<>());
            Set<V> visitedNodes = new HashSet<>(graph.numNodes());

            for (V node : graph.getNodes()) { // Iterate over all nodes to handle disconnected graphs
                if (visitedNodes.add(node)) { // Add node to visited set, skip if already visited
                    while (visitedNodes.size() < graph.numNodes()) { // Continue until all nodes visited
                        // Add all edges to unvisited neighbors to the priority queue
                        for (V neighbour : graph.getNeighbours(node)) {
                            if (!visitedNodes.contains(neighbour)) {
                                Edge<V, L> edge = new Edge<>(node, neighbour, graph.getLabel(node, neighbour));
                                priorityQueue.push(edge);
                            }
                        }

                        // Find the minimum weight edge leading to an unvisited node
                        Edge<V, L> minEdge = priorityQueue.top();
                        while (minEdge != null && visitedNodes.contains(minEdge.getEnd())) {
                            priorityQueue.pop();
                            minEdge = priorityQueue.top();
                        }

                        if (minEdge == null) {
                            break;  // No valid edges in queue, move to next unvisited node
                        }
                        minimumSpanningForest.add(minEdge); // Add edge to MSF
                        visitedNodes.add(minEdge.getEnd()); // Mark destination node as visited
                        node = minEdge.getEnd(); // Continue from the destination node
                    }

                    if (visitedNodes.size() == graph.numNodes()) {
                        break; // All nodes visited, terminate early
                    }
                }
            }
        } catch (IllegalArgumentException e) {
            throw new RuntimeException(e);
        }
        return minimumSpanningForest;
    }

    /**
     * Main method for command-line execution of Prim's algorithm.
     *
     * Usage: java Prim [input_file.csv]
     *
     * Outputs:
     * - Standard output: CSV representation of the Minimum Spanning Forest
     * - Standard error: Statistical information about the computed forest
     *
     * @param args command-line arguments (args[1] should contain the CSV file path)
     */
    public static void main(String[] args) {
        // Read graph data from CSV file specified in args[1]
        if (args.length < 2) {
            System.err.println("Please specify the CSV file path");
            return;
        }

        Graph<String, Double> graph = new Graph<>(false, true);  // Undirected, weighted
        try {
            loadGraphAndPopulate(args[1], graph);
            System.out.println("Graph loaded: " + graph.numNodes() + " nodes, " +
                    graph.numEdges() + " edges.");
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }

        // Compute Minimum Spanning Forest
        Collection<? extends AbstractEdge<String, Double>> minimumSpanningForest = minimumSpanningForest(graph);

        // Standard output: CSV representation of the forest (same format as input)
        double totalWeight = 0.0;
        for (AbstractEdge<String, Double> edge : minimumSpanningForest) {
            System.out.println(
                    edge.getStart() + "," +
                            edge.getEnd() + "," +
                            edge.getLabel());
            totalWeight += edge.getLabel();
        }

        // Standard error: Statistical information about the forest
        System.err.println("\nForest stats:");
        System.err.println("- Connected components: " + (graph.numNodes() - minimumSpanningForest.size()));
        System.err.println("- Total nodes: " + graph.numNodes());
        System.err.println("- Total edges: " + minimumSpanningForest.size());
        System.err.println("- Total weight: " + String.format("%.3f", totalWeight / 1000) + " km");
    }
}

