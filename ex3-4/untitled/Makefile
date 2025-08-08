# Cartelle del progetto
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib       # Dove sono le librerie (JUnit)

# Comandi per Windows
ifeq ($(OS),Windows_NT)
    RM = cmd /C if exist "$(BIN_DIR)\*.class" del /Q "$(BIN_DIR)\*.class"  # Cancella i file .class
    MKDIR = if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"                   # Crea cartella bin se non esiste
    PATH_SEP = \\                                                          # Separatore percorso per Windows
    CLASSPATH_SEP = ;                                                      # Separatore classpath per Windows
else
    # Comandi per Linux/Mac
    RM = rm -f $(BIN_DIR)/*.class                                          # Cancella i file .class
    MKDIR = mkdir -p $(BIN_DIR)                                            # Crea cartella bin
    PATH_SEP = /                                                           # Separatore percorso per Unix
    CLASSPATH_SEP = :                                                      # Separatore classpath per Unix
endif

# Configurazione compilatore Java
JAVAC = javac --release 8   # Compila per Java 8 (compatibile con versioni successive)
JFLAGS = -d $(BIN_DIR) -sourcepath $(SRC_DIR) -cp "$(LIB_DIR)$(PATH_SEP)junit-4.13.jar$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)hamcrest-core-1.3.jar"

# Trova tutti i file .java da compilare
SOURCES := $(wildcard $(SRC_DIR)/*.java)
# Lista dei file .class da generare
CLASSES := $(patsubst $(SRC_DIR)/%.java,$(BIN_DIR)/%.class,$(SOURCES))

# Target principale - compila tutto
all: $(BIN_DIR) $(CLASSES)

# Regola per compilare i .java in .class
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	$(JAVAC) $(JFLAGS) $<

# Crea la cartella bin se non esiste
$(BIN_DIR):
	$(MKDIR)

# Esegui il programma principale
run: all
ifndef CSV_PATH
	$(error Specificare il percorso CSV con CSV_PATH=path/to/file.csv)  # Chiede il percorso del CSV
endif
	java -cp $(BIN_DIR) Prim "$(CSV_PATH)"                            # Avvia il programma

# Esegui i test
test: all
	java -cp "$(BIN_DIR)$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)junit-4.13.jar$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)hamcrest-core-1.3.jar" org.junit.runner.JUnitCore GraphUnitTest

# Pulisci i file compilati
clean:
	$(RM)

.PHONY: all run test clean