import java.util.*;

public class PriorityQueue<E> implements AbstractQueue<E> {
    final Map<E, Integer> indexMap;
    final ArrayList<E> heap;
    private Comparator<E> comparator;

    public PriorityQueue(Comparator<E> comparator){
        if (comparator == null) {
            throw new IllegalArgumentException("Comparator cannot be null");
        }
        this.indexMap = new HashMap<>();
        this.heap = new ArrayList<>();
        this.comparator = comparator;
    }


    @Override
    public boolean empty() {
        return this.heap.isEmpty();
    }

    @Override
    public boolean push(E e) {
        if (contains(e)) {
            return false; // Elemento già presente, inserimento fallito
        }else {
            this.heap.add(e); //aggiunge elemento e in coda all ArrayList  (quindi in ultima posizione, indice size()-1)
            this.indexMap.put(e, this.heap.size() - 1); //mappo l'elemento e nella sua posizione corrente nello haep (cioè l'ultimo indice)
            heapifyUp(this.heap.size() - 1);//riordina lo heap dopo aver aggiunto l'elemento
            return true;
        }
    }

    @Override
    public boolean contains(E e) {
        return this.indexMap.containsKey(e);
    }

    @Override
    public E top() {
        if (empty()) {
            return null;
        }else {//se heap non è vuoto
            return this.heap.get(0); //ritorno il primo elemento
        }
    }

    @Override
    public void pop() {
        if(!empty()){
            removeAtPosition(0);
        }
    }

    @Override
    public boolean remove(E e) {
        Integer position = indexMap.get(e);//cerco indice dell'elemento e nella hashmap
        if (position != null) {
            removeAtPosition(position); //se l'elemento è stato trovato lo rimuovo
            return true;
        }else {
            return false;
        }
    }

    //ritorna l'indice del padre dell'i-node
    public int getParentIndex(int i) {
        return (i - 1) / 2;
    }
    //ritorna l'indice del figlio sinistro dell'i-node
    public int getLeftChildIndex(int i) {
        return ((2 * i) + 1);
    }

    //ritorna l'indice del figlio destro dell'i-node
    public int getRightChildIndex(int i) {
        return ((2 * i) + 2);
    }


    private void removeAtPosition(int position) {
        // Salva l'indice dell'ultimo elemento
        final int lastElementPosition = heap.size() - 1;

        // Se non stiamo rimuovendo l'ultimo elemento, scambia con l'ultimo
        if(position < lastElementPosition) {
            swapElements(position, lastElementPosition);
        }

        // Rimuovi l'elemento (ora in ultima posizione) O(1)
        E elementToRemove = heap.remove(lastElementPosition);
        indexMap.remove(elementToRemove);  // Rimuovi dalla mappa

        // Se la coda non è vuota e abbiamo scambiato elementi
        if(position < heap.size()) {
            // Confronta con il genitore per decidere la direzione di riordino
            if(position > 0 && comparator.compare(heap.get(position), heap.get(getParentIndex(position))) < 0) {
                heapifyUp(position);  // se l'elemento è più grande del genitore, allora lo facciamo salire
            } else {
                heapifyDown(position); //se l'elemento è più piccolo o uguale, allora lo facciamo scendere
            }
        }
    }


    private void heapifyDown(int currentPos) {
        // Ottieni le posizioni dei figli sinistro e destro
        int leftChildPos = getLeftChildIndex(currentPos);
        int rightChildPos = getRightChildIndex(currentPos);
        int dominantPos = currentPos;
        // Confronta con il figlio sinistro (se esiste)
        if (leftChildPos < heap.size() && comparator.compare(heap.get(leftChildPos), heap.get(dominantPos)) < 0) {
            dominantPos = leftChildPos;// Il figlio sinistro ha priorità maggiore
        }
        // Confronta con il figlio destro (se esiste)
        if (rightChildPos < heap.size() && comparator.compare(heap.get(rightChildPos), heap.get(dominantPos)) < 0) {
            dominantPos = rightChildPos;// Il figlio destro ha priorità maggiore
        }
        // Se la posizione dominante è cambiata, scambia e continua a riordinare
        if (dominantPos != currentPos) {
            swapElements(currentPos, dominantPos);
            heapifyDown(dominantPos); // Ricorsione sul figlio scambiato
        }
    }


    private void heapifyUp(int currentPos) {
        int parentPos = getParentIndex(currentPos);
        // Continua a salire finché l'elemento ha priorità maggiore del genitore
        while (currentPos > 0 && comparator.compare(heap.get(currentPos), heap.get(parentPos)) < 0) {
            swapElements(currentPos, parentPos); // Scambia con il genitore
            currentPos = parentPos;              // Sali al livello superiore
            parentPos = getParentIndex(currentPos); // Aggiorna la posizione del nuovo genitore
        }
    }


    private void swapElements(int firstPos, int secondPos) {
        // Recupera gli elementi dalle posizioni
        E firstElement = heap.get(firstPos);
        E secondElement = heap.get(secondPos);
        // Scambia gli elementi nello heap
        heap.set(firstPos, secondElement);
        heap.set(secondPos, firstElement);
        // Aggiorna le posizioni nella mappa degli indici
        indexMap.put(secondElement, firstPos);
        indexMap.put(firstElement, secondPos);
    }
}