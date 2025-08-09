# Cartelle del progetto
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib

# Comandi per Windows
ifeq ($(OS),Windows_NT)
    RM = cmd /C if exist "$(BIN_DIR)\*.class" del /Q "$(BIN_DIR)\*.class"
    MKDIR = if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
    PATH_SEP = \\
    CLASSPATH_SEP = ;
else
    RM = rm -f $(BIN_DIR)/*.class
    MKDIR = mkdir -p $(BIN_DIR)
    PATH_SEP = /
    CLASSPATH_SEP = :
endif

# Configurazione compilatore Java
JAVAC = javac --release 8
JFLAGS = -d $(BIN_DIR) -sourcepath $(SRC_DIR) -cp "$(LIB_DIR)$(PATH_SEP)junit-4.13.jar$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)hamcrest-core-1.3.jar"

# Trova tutti i file .java da compilare
SOURCES := $(wildcard $(SRC_DIR)/*.java)
CLASSES := $(patsubst $(SRC_DIR)/%.java,$(BIN_DIR)/%.class,$(SOURCES))

# Target principale
all: $(BIN_DIR) $(CLASSES)

$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	$(JAVAC) $(JFLAGS) $<

$(BIN_DIR):
	$(MKDIR)

run: all
ifndef CSV_PATH
	$(error Specificare il percorso CSV con CSV_PATH=path/to/file.csv)
endif
	java -cp $(BIN_DIR) Prim "$(CSV_PATH)"

test-graph: all
	java -cp "$(BIN_DIR)$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)junit-4.13.jar$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)hamcrest-core-1.3.jar" org.junit.runner.JUnitCore GraphUnitTest

test-pq: all
	java -cp "$(BIN_DIR)$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)junit-4.13.jar$(CLASSPATH_SEP)$(LIB_DIR)$(PATH_SEP)hamcrest-core-1.3.jar" org.junit.runner.JUnitCore PriorityQueueUnitTest

clean:
	$(RM)

.PHONY: all run test clean