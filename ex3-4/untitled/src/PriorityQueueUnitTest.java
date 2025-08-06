import java.util.Comparator;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;


public class PriorityQueueUnitTest {

    private PriorityQueue<Integer> queue;
    final private Comparator<Integer> comparator = Comparator.naturalOrder();


    @Before
    public void inizializeQueue(){
        this.queue = new PriorityQueue<>(comparator);
    }

    /* Test costruttore e stato iniziale */
    @Test(expected = IllegalArgumentException.class)
    public void constructorShouldRejectNullComparator() {
        new PriorityQueue<Integer>(null);
    }

    @Test
    public void newQueueShouldBeEmpty() {
        assertTrue(queue.empty());
        assertEquals(0, queue.heap.size());
        assertTrue(queue.indexMap.isEmpty()); // Coerenza interna
    }

    /* Test inserimento */
    @Test
    public void pushShouldAddElementToHeap() {
        queue.push(22);
        assertFalse(queue.empty());
        assertEquals(1, queue.heap.size());
        assertTrue(queue.contains(22));
    }

    @Test
    public void pushShouldMaintainHeapProperty() {
        queue.push(22);
        queue.push(5);
        queue.push(23);
        assertEquals(3, queue.indexMap.size());
        assertEquals(Integer.valueOf(5), queue.top());
    }
    @Test
    public void topShouldReturnNullWhenEmpty() {
        assertNull(queue.top());
    }

    @Test
    public void topShouldReturnMaxPriorityElement() {
        queue.push(19);
        queue.push(22);
        queue.push(17);
        queue.push(1);
        assertEquals(Integer.valueOf(1), queue.top());
    }


    /* Test rimozioni */
    @Test
    public void popShouldRemoveMaxPriorityElement() {
        queue.push(19);
        queue.push(22);
        queue.push(17);
        queue.push(1);
        queue.pop();
        assertFalse(queue.contains(1));
        assertEquals(Integer.valueOf(17), queue.top());
    }


    @Test
    public void popOnEmptyQueueShouldDoNothing() {
        queue.pop(); // Non dovrebbe lanciare eccezioni
        assertTrue(queue.empty());
    }


    @Test
    public void removeShouldReturnFalseForMissingElements() {
        assertFalse(queue.remove(1));
        queue.push(22);
        assertFalse(queue.remove(11));
    }

    @Test
    public void removeShouldDeleteSpecificElement() {
        queue.push(19);
        queue.push(22);
        queue.push(17);
        queue.push(1);
        assertTrue(queue.remove(17));
        assertFalse(queue.contains(17));
        assertEquals(3, queue.heap.size());
    }


    /* Test casi particolari */
    @Test
    public void shouldRejectDuplicateElements() {
        assertTrue(queue.push(19));  // Primo inserimento dovrebbe riuscire
        assertFalse(queue.push(19)); // Secondo inserimento dovrebbe fallire
        assertEquals(1, queue.heap.size()); // Dovrebbe contenere solo un elemento
        assertEquals(1, queue.indexMap.size()); // Anche la mappa dovrebbe contenere un solo elemento

        queue.pop();
        assertFalse(queue.contains(19)); // Dopo il pop, l'elemento non dovrebbe più esistere
    }

    @Test
    public void removeShouldWorkOnLastElement() {
        queue.push(19);
        assertTrue(queue.remove(19));
        assertTrue(queue.empty());
    }

    @Test
    public void testHeapOrderAfterMultipleOperations() {
        // Sequenza complessa per verificare stabilità
        queue.push(55);
        queue.push(37);
        queue.pop();
        queue.push(82);
        queue.push(19);
        queue.remove(55);
        assertEquals(Integer.valueOf(19), queue.top());
    }
}