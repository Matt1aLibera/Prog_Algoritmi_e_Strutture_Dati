import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Prim {
    public static void loadGraphAndPopulate(String filePath, Graph<String, Double> graph) throws IOException {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            br.lines()
                    .filter(line -> !line.trim().isEmpty())  // Ignora righe vuote
                    .forEach(line -> {
                        String[] parts = line.split("\\s*,\\s*");  // Split che ignora spazi
                        if (parts.length != 3) {
                            throw new IllegalArgumentException("Formato riga non valido: " + line);
                        }
                        try {
                            String source = parts[0];
                            String target = parts[1];
                            double weight = Double.parseDouble(parts[2]);

                            // Aggiungi nodi se non esistono già (idempotente)
                            graph.addNode(source);
                            graph.addNode(target);

                            // Aggiungi arco
                            graph.addEdge(source, target, weight);
                        } catch (NumberFormatException e) {
                            throw new IllegalArgumentException("Peso non numerico in riga: " + line, e);
                        }
                    });
        }


    }

    static class DoubleEdgeComparator<V, L> implements Comparator<Edge<V, L>> {
        @Override
        public int compare(Edge<V, L> e1, Edge<V, L> e2) {
            // Soluzione 1: Per tipi Number generici (più lenta)
            return Double.compare((Double) e1.getLabel(), (Double) e2.getLabel());
        }
    }
        public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
            List<AbstractEdge<V, L>> minimumSpanningForest = new ArrayList<>();
            if (graph == null || graph.numNodes() == 0) {
                return minimumSpanningForest;
            }

            try {
                PriorityQueue<Edge<V, L>> priorityQueue = new PriorityQueue<>(new DoubleEdgeComparator<>());

                Set<V> visitedNodes = new HashSet<>(graph.numNodes());

                for (V node : graph.getNodes()) { // Itera su tutti i nodi del grafo per gestire anche grafi non connessi
                    if (visitedNodes.add(node)) { //aggiungiamo il nodo a quelli visitati, se è gia presente allora passiamo al prossimo
                        while (visitedNodes.size() < graph.numNodes()) { //se non abbiamo ancora visitato tutti i nodi del grafo
                            for (V neighbour : graph.getNeighbours(node)) { //aggiungiamo alla PQ tutti gli archi verso nodi non visitati (archi uscenti del nodo che stiamo visitando)
                                if (!visitedNodes.contains(neighbour)) {
                                    Edge<V, L> edge = new Edge<>(node, neighbour, graph.getLabel(node, neighbour));
                                    priorityQueue.push(edge);
                                }
                            }

                            Edge<V, L> minEdge = priorityQueue.top(); //estraiamo arco con peso minimo che porta ad un nodo non visitato
                            while (minEdge != null && visitedNodes.contains(minEdge.getEnd())) {
                                priorityQueue.pop();
                                minEdge = priorityQueue.top();
                            }

                            if (minEdge == null){
                                break;  // non ci sono piu archi validi nella coda, passiamo ad un altro nodo del grafo non alcora visitato
                            }
                                minimumSpanningForest.add(minEdge); //se no aggiungiamo alla foresta il nodo analizzato (sorgente)
                                visitedNodes.add(minEdge.getEnd()); //aggiungiamo ai visitati la destinazione dell'arco uscente dalla sorgente
                                node = minEdge.getEnd(); //nodo destinazione diventa il n uovo nodo sorgente da analizzare
                        }

                        if (visitedNodes.size() == graph.numNodes()) {
                            break; //abbiamo visitato tutti i nodi del grafo, wtermino anticipatamente
                        }
                    }
                }
            } catch (IllegalArgumentException e) {
                throw new RuntimeException(e);
            }
            return minimumSpanningForest;
        }

        public static void main(String[] args) {
            // leggi i dati CSV del grafo dal percorso in args[1]
            if (args.length < 1) {
                System.err.println("Specificare il percorso del file CSV");
                return;
            }

            Graph<String, Double> graph = new Graph<>(false, true);  // Non orientato, pesato
            try {
                loadGraphAndPopulate(args[0], graph);
                System.out.println("Grafo caricato: " + graph.numNodes() + " nodi, " +
                        graph.numEdges() + " archi.");
            } catch (Exception e) {
                System.err.println("Errore: " + e.getMessage());
            }
            // calcola la minima foresta ricoprente con minimumSpanningForest
            // scrivi su standard output solo la descrizione della foresta calcolata come CSV con formato analogo a quello in input
            // su standard error si possono scrivere ulteriori informazioni, come il numero di nodi e archi nella foresta calcolata,
            // o il peso totale della foresta
        }
    }

