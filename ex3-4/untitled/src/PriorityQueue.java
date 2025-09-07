import java.util.*;
/**
 * A priority queue implementation using a binary heap with efficient element tracking.
 *
 * This class implements a priority queue where elements are ordered according to a specified comparator.
 * It uses a combination of an ArrayList for heap storage and a HashMap for efficient element lookup
 * and index tracking. This allows for O(1) contains checks and O(log n) operations for push, pop,
 * and remove operations.
 *
 * The heap is maintained as a min-heap based on the provided comparator, meaning the smallest
 * element (according to the comparator) is always at the root position.
 *
 * @param <E> the type of elements held in this priority queue
 */
public class PriorityQueue<E> implements AbstractQueue<E> {
    final Map<E, Integer> indexMap;
    final ArrayList<E> heap;
    private Comparator<E> comparator;

    /**
     * Constructs a new PriorityQueue with the specified comparator.
     *
     * @param comparator the comparator to determine the ordering of elements
     * @throws IllegalArgumentException if the comparator is null
     */
    public PriorityQueue(Comparator<E> comparator) {
        if (comparator == null) {
            throw new IllegalArgumentException("Comparator cannot be null");
        }
        this.indexMap = new HashMap<>();
        this.heap = new ArrayList<>();
        this.comparator = comparator;
    }

    /**
     * Checks if the priority queue is empty.
     *
     * @return true if the queue is empty, false otherwise
     */
    @Override
    public boolean empty() {
        return this.heap.isEmpty();
    }

    /**
     * Inserts the specified element into the priority queue.
     *
     * @param e the element to be inserted
     * @return true if the element was added successfully, false if the element already exists
     */
    @Override
    public boolean push(E e) {
        if (contains(e)) {
            return false; // Element already present, insertion failed
        } else {
            this.heap.add(e); // Add element to the end of the ArrayList
            this.indexMap.put(e, this.heap.size() - 1); // Map element to its current position
            heapifyUp(this.heap.size() - 1); // Reorder the heap after adding
            return true;
        }
    }

    /**
     * Checks if the priority queue contains the specified element.
     *
     * @param e the element to check for presence
     * @return true if the element is present, false otherwise
     */
    @Override
    public boolean contains(E e) {
        return this.indexMap.containsKey(e);
    }

    /**
     * Retrieves, but does not remove, the element with the highest priority.
     *
     * @return the element with the highest priority, or null if the queue is empty
     */
    @Override
    public E top() {
        if (empty()) {
            return null;
        } else {
            return this.heap.get(0); // Return the root element
        }
    }

    /**
     * Removes the element with the highest priority from the queue.
     * Does nothing if the queue is empty.
     */
    @Override
    public void pop() {
        if (!empty()) {
            removeAtPosition(0);
        }
    }

    /**
     * Removes the first occurrence of the specified element from the queue.
     *
     * @param e the element to be removed
     * @return true if the element was found and removed, false otherwise
     */
    @Override
    public boolean remove(E e) {
        Integer position = indexMap.get(e); // Find element's index in the heap
        if (position != null) {
            removeAtPosition(position); // Remove element if found
            return true;
        } else {
            return false;
        }
    }

    /**
     * Returns the index of the parent node for the given index.
     *
     * @param i the index of the child node
     * @return the index of the parent node
     */
    public int getParentIndex(int i) {
        return (i - 1) / 2;
    }

    /**
     * Returns the index of the left child for the given index.
     *
     * @param i the index of the parent node
     * @return the index of the left child
     */
    public int getLeftChildIndex(int i) {
        return ((2 * i) + 1);
    }

    /**
     * Returns the index of the right child for the given index.
     *
     * @param i the index of the parent node
     * @return the index of the right child
     */
    public int getRightChildIndex(int i) {
        return ((2 * i) + 2);
    }

    /**
     * Removes the element at the specified position from the heap.
     * Maintains heap properties after removal.
     *
     * @param position the index of the element to be removed
     */
    private void removeAtPosition(int position) {
        final int lastElementPosition = heap.size() - 1;

        // If not removing the last element, swap with the last element
        if (position < lastElementPosition) {
            swapElements(position, lastElementPosition);
        }

        // Remove the element (now in last position)
        E elementToRemove = heap.remove(lastElementPosition);
        indexMap.remove(elementToRemove); // Remove from index map

        // If queue is not empty and elements were swapped
        if (position < heap.size()) {
            // Compare with parent to decide reordering direction
            if (position > 0 && comparator.compare(heap.get(position), heap.get(getParentIndex(position))) < 0) {
                heapifyUp(position); // Move up if element is smaller than parent
            } else {
                heapifyDown(position); // Move down if element is larger or equal
            }
        }
    }

    /**
     * Maintains heap property by moving an element down the heap.
     *
     * @param currentPos the starting position for the heapify operation
     */
    private void heapifyDown(int currentPos) {
        int leftChildPos = getLeftChildIndex(currentPos);
        int rightChildPos = getRightChildIndex(currentPos);
        int dominantPos = currentPos;

        // Compare with left child (if exists)
        if (leftChildPos < heap.size() && comparator.compare(heap.get(leftChildPos), heap.get(dominantPos)) < 0) {
            dominantPos = leftChildPos; // Left child has higher priority
        }

        // Compare with right child (if exists)
        if (rightChildPos < heap.size() && comparator.compare(heap.get(rightChildPos), heap.get(dominantPos)) < 0) {
            dominantPos = rightChildPos; // Right child has higher priority
        }

        // If dominant position changed, swap and continue
        if (dominantPos != currentPos) {
            swapElements(currentPos, dominantPos);
            heapifyDown(dominantPos); // Recursively heapify the swapped child
        }
    }

    /**
     * Maintains heap property by moving an element up the heap.
     *
     * @param currentPos the starting position for the heapify operation
     */
    private void heapifyUp(int currentPos) {
        int parentPos = getParentIndex(currentPos);
        // Continue moving up while element has higher priority than parent
        while (currentPos > 0 && comparator.compare(heap.get(currentPos), heap.get(parentPos)) < 0) {
            swapElements(currentPos, parentPos); // Swap with parent
            currentPos = parentPos;              // Move to parent level
            parentPos = getParentIndex(currentPos); // Update new parent position
        }
    }

    /**
     * Swaps two elements in the heap and updates their positions in the index map.
     *
     * @param firstPos the index of the first element to swap
     * @param secondPos the index of the second element to swap
     */
    private void swapElements(int firstPos, int secondPos) {
        E firstElement = heap.get(firstPos);
        E secondElement = heap.get(secondPos);

        // Swap elements in the heap
        heap.set(firstPos, secondElement);
        heap.set(secondPos, firstElement);

        // Update positions in the index map
        indexMap.put(secondElement, firstPos);
        indexMap.put(firstElement, secondPos);
    }
}