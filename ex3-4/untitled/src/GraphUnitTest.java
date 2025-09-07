import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;
import java.util.Collection;
/**
 * Unit test class for the Graph implementation.
 *
 * This class contains comprehensive tests for the Graph class, covering
 * all major functionalities including graph construction, node and edge
 * operations, and graph properties verification. The tests are organized
 * into logical sections and use both directed/labelled and undirected/unlabelled
 * graph instances to ensure complete coverage.
 */
public class GraphUnitTest {
    private Graph<String, Integer> directedLabelledGraph;
    private Graph<String, Void> undirectedUnlabelledGraph;
    private final String nodeA = "A", nodeB = "B", nodeC = "C", nodeD = "D";

    @Before
    public void initializeGraphs() {
        directedLabelledGraph = new Graph<>(true, true);  // Grafo diretto con label
        undirectedUnlabelledGraph = new Graph<>(false, false);  // Grafo non diretto senza label
    }

    /* =============== TEST COSTRUTTORE E PROPERTIES =============== */
    @Test
    public void newlyCreatedGraphShouldBeEmpty() {
        assertEquals(0, directedLabelledGraph.numNodes());
        assertEquals(0, directedLabelledGraph.numEdges());
    }

    @Test
    public void shouldCorrectlyReportGraphType() {
        assertTrue(directedLabelledGraph.isDirected());
        assertTrue(directedLabelledGraph.isLabelled());
        assertFalse(undirectedUnlabelledGraph.isDirected());
        assertFalse(undirectedUnlabelledGraph.isLabelled());
    }

    /* =============== TEST AGGIUNTA NODI =============== */
    @Test
    public void addingNodeShouldIncreaseNodeCount() {
        assertTrue(directedLabelledGraph.addNode(nodeA));
        assertEquals(1, directedLabelledGraph.numNodes());
    }

    @Test
    public void addingDuplicateNodeShouldFail() {
        directedLabelledGraph.addNode(nodeA);
        assertFalse(directedLabelledGraph.addNode(nodeA));
        assertEquals(1, directedLabelledGraph.numNodes());
    }

    /* =============== TEST AGGIUNTA ARCHI =============== */
    @Test
    public void addingEdgeShouldIncreaseEdgeCount() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        assertTrue(directedLabelledGraph.addEdge(nodeA, nodeB, 5));
        assertEquals(1, directedLabelledGraph.numEdges());
    }

    @Test
    public void addingEdgeBetweenNonexistentNodesShouldFail() {
        assertFalse(directedLabelledGraph.addEdge(nodeA, nodeB, 10));
        directedLabelledGraph.addNode(nodeA);
        assertFalse(directedLabelledGraph.addEdge(nodeA, nodeB, 10));
    }

    @Test
    public void addingDuplicateEdgeShouldFail() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        assertFalse(directedLabelledGraph.addEdge(nodeA, nodeB, 8));
    }

    @Test
    public void labelledGraphShouldRejectNullLabels() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        assertFalse(directedLabelledGraph.addEdge(nodeA, nodeB, null));
    }

    @Test
    public void unlabelledGraphShouldForceNullLabel() {
        undirectedUnlabelledGraph.addNode(nodeA);
        undirectedUnlabelledGraph.addNode(nodeB);
        assertTrue(undirectedUnlabelledGraph.addEdge(nodeA, nodeB, null));
        assertNull(undirectedUnlabelledGraph.getLabel(nodeA, nodeB));
    }

    /* =============== TEST RIMOZIONE NODI =============== */
    @Test
    public void removingNodeShouldDecreaseNodeCount() {
        directedLabelledGraph.addNode(nodeA);
        assertEquals(1, directedLabelledGraph.numNodes());
        assertTrue(directedLabelledGraph.removeNode(nodeA));
        assertEquals(0, directedLabelledGraph.numNodes());
    }

    @Test
    public void removingNodeShouldRemoveIncidentEdges() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addNode(nodeC);
        directedLabelledGraph.addEdge(nodeA, nodeB, 7);
        directedLabelledGraph.addEdge(nodeC, nodeA, 5);
        directedLabelledGraph.removeNode(nodeA);
        assertEquals(0, directedLabelledGraph.numEdges());
    }

    @Test
    public void removingNonexistentNodeShouldFail() {
        assertFalse(directedLabelledGraph.removeNode(nodeA));
    }

    /* =============== TEST RIMOZIONE ARCHI =============== */
    @Test
    public void removingEdgeShouldDecreaseEdgeCount() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        assertEquals(1, directedLabelledGraph.numEdges());
        assertTrue(directedLabelledGraph.removeEdge(nodeA, nodeB));
        assertEquals(0, directedLabelledGraph.numEdges());
    }

    @Test
    public void removingNonexistentEdgeShouldFail() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        assertFalse(directedLabelledGraph.removeEdge(nodeA, nodeB));
    }

    @Test
    public void removingEdgeInUndirectedGraphShouldRemoveBothDirections() {
        undirectedUnlabelledGraph.addNode(nodeA);
        undirectedUnlabelledGraph.addNode(nodeB);
        undirectedUnlabelledGraph.addEdge(nodeA, nodeB, null);
        undirectedUnlabelledGraph.removeEdge(nodeA, nodeB);
        assertFalse(undirectedUnlabelledGraph.containsEdge(nodeA, nodeB));
        assertFalse(undirectedUnlabelledGraph.containsEdge(nodeB, nodeA));
    }

    /* =============== TEST QUERY DI BASE =============== */
    @Test
    public void shouldCorrectlyReportNodeExistence() {
        directedLabelledGraph.addNode(nodeA);
        assertTrue(directedLabelledGraph.containsNode(nodeA));
        assertFalse(directedLabelledGraph.containsNode(nodeB));
    }

    @Test
    public void shouldCorrectlyReportEdgeExistence() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        assertTrue(directedLabelledGraph.containsEdge(nodeA, nodeB));
        assertFalse(directedLabelledGraph.containsEdge(nodeB, nodeA));
    }

    /* =============== TEST OPERAZIONI COLLECTION =============== */
    @Test
    public void getNodesShouldReturnAllNodes() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addNode(nodeC);
        directedLabelledGraph.addNode(nodeD);
        Collection<String> nodes = directedLabelledGraph.getNodes();
        assertTrue(nodes.contains(nodeA) && nodes.contains(nodeB) && nodes.contains(nodeC) && nodes.contains(nodeD));
        assertEquals(4, nodes.size());
    }

    @Test
    public void getEdgesShouldReturnAllEdges() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        assertEquals(1, directedLabelledGraph.getEdges().size());
    }

    @Test
    public void getNeighboursShouldReturnAdjacentNodes() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addNode(nodeC);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        directedLabelledGraph.addEdge(nodeA, nodeC, 10);
        Collection<String> neighbours = directedLabelledGraph.getNeighbours(nodeA);
        assertTrue(neighbours.contains(nodeB) && neighbours.contains(nodeC));
        assertEquals(2, neighbours.size());
    }

    @Test
    public void getLabelShouldReturnCorrectValue() {
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        assertEquals(Integer.valueOf(5), directedLabelledGraph.getLabel(nodeA, nodeB));
    }

    @Test
    public void getLabelShouldReturnNullForUnlabelledGraph() {
        undirectedUnlabelledGraph.addNode(nodeA);
        undirectedUnlabelledGraph.addNode(nodeB);
        undirectedUnlabelledGraph.addEdge(nodeA, nodeB, null);
        assertNull(undirectedUnlabelledGraph.getLabel(nodeA, nodeB));
    }

    /* =============== TEST CASI PARTICOLARI =============== */
    @Test
    public void selfLoopShouldBeHandledCorrectly() {
        directedLabelledGraph.addNode(nodeA);
        assertTrue(directedLabelledGraph.addEdge(nodeA, nodeA, 1));
        assertTrue(directedLabelledGraph.containsEdge(nodeA, nodeA));
        assertEquals(1, directedLabelledGraph.numEdges());
    }

    @Test
    public void multipleOperationsShouldMaintainConsistency() {
        // Test complesso per verificare la coerenza dopo più operazioni
        directedLabelledGraph.addNode(nodeA);
        directedLabelledGraph.addNode(nodeB);
        directedLabelledGraph.addNode(nodeC);
        directedLabelledGraph.addEdge(nodeA, nodeB, 5);
        directedLabelledGraph.addEdge(nodeB, nodeC, 10);
        directedLabelledGraph.removeEdge(nodeA, nodeB);
        directedLabelledGraph.removeNode(nodeB);
        assertEquals(2, directedLabelledGraph.numNodes());
        assertEquals(0, directedLabelledGraph.numEdges());
    }
}