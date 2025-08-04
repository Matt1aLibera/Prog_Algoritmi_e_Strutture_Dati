import java.util.Comparator;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;


public class PriorityQueueTestCase {

    private PriorityQueue<Integer> queue;
    private Comparator<Integer> comparator = Comparator.naturalOrder();


    @Before
    public void setUp(){
        this.queue = new PriorityQueue<>(comparator);
    }


    @Test
    public void testEmpty() {
        assertTrue(queue.empty());
        queue.push(10);
        assertFalse(queue.empty());
    }


    @Test
    public void testPush() {
        queue.push(10);
        queue.push(20);
        queue.push(15);
        assertEquals(3, queue.heap.size());
        assertEquals(Integer.valueOf(20), queue.top());
    }


    @Test
    public void testContains() {
        queue.push(10);
        queue.push(20);
        assertTrue(queue.contains(10));
        assertFalse(queue.contains(15));
    }


    @Test
    public void testTop() {
        assertNull(queue.top());
        queue.push(10);
        queue.push(20);
        queue.push(15);
        assertEquals(Integer.valueOf(20), queue.top());
    }


    @Test
    public void testPop() {
        queue.push(10);
        queue.push(20);
        queue.push(15);
        queue.pop();
        assertEquals(2, queue.heap.size());
        assertEquals(Integer.valueOf(15), queue.top());
    }


    @Test
    public void testRemove() {
        queue.push(10);
        queue.push(20);
        queue.push(15);
        assertTrue(queue.remove(20));
        assertFalse(queue.contains(20));
        assertEquals(2, queue.heap.size());
    }


    @Test
    public void testPushAndOrder() {
        queue.push(5);
        queue.push(3);
        queue.push(8);
        queue.push(1);
        assertEquals(Integer.valueOf(8), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(5), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(3), queue.top());
        queue.pop();
        assertEquals(Integer.valueOf(1), queue.top());
    }


    @Test
    public void testRemoveNonExistingElement() {
        queue.push(10);
        queue.push(20);
        assertFalse(queue.remove(30));
    }
}