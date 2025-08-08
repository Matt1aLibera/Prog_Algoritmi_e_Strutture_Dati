# Configurazioni base
SRC_DIR := src
BIN_DIR := bin
JAVAC := javac
JFLAGS := -d $(BIN_DIR) -sourcepath $(SRC_DIR) -Xlint:unchecked

# Trova TUTTI i file .java (senza esclusioni)
SOURCES := $(wildcard $(SRC_DIR)/*.java)

# Genera i corrispondenti file .class
CLASSES := $(SOURCES:$(SRC_DIR)/%.java=$(BIN_DIR)/%.class)

# Target principale - compila tutto
all: $(BIN_DIR) $(CLASSES)

# Regola per compilare i file .java
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	@echo "Compilando $<..."
	@$(JAVAC) $(JFLAGS) $<

# Crea la cartella bin se non esiste
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)false

# Target per eseguire il programma (usa: make run ARGS="input.csv")
run: all
	@java -cp $(BIN_DIR) Prim $(ARGS)

# Target per pulire
clean:
	@echo "Pulizia file compilati..."
	@rm -rf $(BIN_DIR)

# Target per visualizzare aiuto
help:
	@echo "Target disponibili:"
	@echo "  all       - Compila tutti i sorgenti (default)"
	@echo "  run       - Esegui il programma (ARGS=\"input.csv\")"
	@echo "  clean     - Elimina tutti i file compilati"
	@echo "  help      - Mostra questo aiuto"

.PHONY: all run clean help