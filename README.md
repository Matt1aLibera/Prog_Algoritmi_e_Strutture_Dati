# Algoritmi e Strutture Dati: Progetto di Laboratorio

### 🎓 Percorso Accademico
**Studente:** Mattia Liberatore  
**Corso:** Algoritmi e Strutture Dati  
**Università:** Università degli Studi di Torino - Dipartimento di Informatica

---

## 📝 Panoramica del Progetto
Il repository contiene l'implementazione di strutture dati classiche e algoritmi fondamentali, sviluppati con un focus sulla **genericità** e l'**efficienza asintotica**. Il progetto copre algoritmi di ordinamento, programmazione dinamica e strutture dati avanzate su grafi.

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![Java](https://img.shields.io/badge/Java-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white)
![JUnit](https://img.shields.io/badge/JUnit-25A162?style=for-the-badge&logo=junit5&logoColor=white)
![Make](https://img.shields.io/badge/Build-Makefile-orange?style=for-the-badge)

---

## 📂 Struttura del Lavoro

### Esercizio 1: Ordinamento Generico (C)
Sviluppo di una libreria per l'ordinamento di tipi di dato generici (`void *`) tramite comparatori esterni.
* **Algoritmi:** Merge Sort e Quick Sort.
* **Benchmark:** Test di ordinamento su un dataset di **20 milioni di record** (CSV), analizzando i tempi di esecuzione per diversi campi (id, stringhe, interi, float).
* **Cartella:** `/ex1`

### Esercizio 2: Edit Distance (C)
Calcolo della distanza di Levenshtein tra stringhe con focus sull'ottimizzazione algoritmica.
* **Algoritmo:** Implementazione di una versione ricorsiva pura e di una versione ottimizzata tramite **Programmazione Dinamica (Top-Down con Memoizzazione)** su matrice $O(m \times n)$.
* **Applicazione:** Correttore ortografico basato su un dizionario di riferimento.
* **Cartella:** `/ex2`

### Esercizio 3: Priority Queue (Java)
Implementazione di una coda con priorità generica basata su **Binary Heap**.
* **Complessità:** `push` e `pop` in $O(\log N)$, `top` in $O(1)$.
* **Integrazione:** Gestione di tipi parametrici (`Generics`) e comparatori flessibili.
* **Cartella:** `/ex3-4`

### Esercizio 4: Grafi Sparsi e Algoritmo di Prim (Java)
Libreria per la gestione di grafi sparsi ottimizzata per l'uso di memoria e tempi di accesso.
* **Algoritmo:** Implementazione dell'algoritmo di **Prim** per il calcolo della **Minima Foresta Ricoprente** (MSF).
* **Caso d'uso:** Analisi delle distanze geografiche tra località italiane (~18.600 nodi e archi), utilizzando la Priority Queue sviluppata nell'Ex 3.
* **Cartella:** `/ex3-4`

---

## 🛠️ Testing e Qualità
Il progetto adotta approcci di testing differenziati per linguaggio:
- **In C:** Unit testing personalizzato implementato tramite suite dedicate (`test_ex1.c`, `test_ex2.c`) caricate direttamente via Makefile.
- **In Java:** Testing automatizzato tramite **JUnit 4**, con suite per la validazione della Priority Queue e della struttura Grafo.

---

## 🚀 Compilazione
Il progetto è interamente automatizzato tramite **Makefile**.

**Esercizi in C:**
```bash
cd ex1 # o ex2
make all
./bin/test_ex1 # Esegue i test
```

**Esercizi in Java:**
```bash
cd ex3-4
make all
make test-pq    # Esegue i test della Priority Queue
make test-graph # Esegue i test del Grafo
```

---

### 💡 Note Tecniche

* **Gestione Memoria (C):** L'implementazione di `edit_distance_dyn` utilizza l'allocazione dinamica tramite `malloc` per la matrice di memoizzazione, garantendo la completa deallocazione dello heap (`free`) al termine del calcolo per evitare memory leak.
* **Flessibilità (Java):** La libreria dei grafi è stata progettata per supportare combinazioni di grafi diretti/non diretti e pesati/non pesati tramite costruttori booleani, massimizzando il riutilizzo del codice e rispettando i vincoli di complessità $O(1)$ per le operazioni sparse (assumendo l'uso di liste di adiacenza).
* **Algoritmi Avanzati:** L'uso della `PriorityQueue` custom all'interno dell'algoritmo di **Prim** permette di estrarre il nodo a costo minimo in $O(\log N)$, rendendo l'approccio efficiente anche su grafi di grandi dimensioni, come quello delle località italiane (~18k nodi).
