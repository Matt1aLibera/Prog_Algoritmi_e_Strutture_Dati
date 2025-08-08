import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collection;

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
    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        // calcola la minima foresta ricoprente con l'algoritmo di Prim
        // restituisce la collezione degli archi che formano la foresta
        return null;
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

