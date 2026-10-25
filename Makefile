# Compilador e flags de compilação
CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

# Diretórios
ENTITIES_DIR = Entities
FUNCTIONS_DIR = Functions
ALGORITHMS_DIR = Algorithms
OBJ_DIR = objects

# Arquivos fonte
SRCS = main.cpp \
       $(ENTITIES_DIR)/ProblemaManutencao.cpp \
       $(FUNCTIONS_DIR)/Utils.cpp \
       $(ALGORITHMS_DIR)/GreedyDescent.cpp \
       $(ALGORITHMS_DIR)/SimulatedAnnealing.cpp \
       $(ALGORITHMS_DIR)/GeneticAlgorithm.cpp

# Mapeia o .cpp para .o mantendo o caminho completo dentro de objects/
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável final
TARGET = executable/tp2_busca

all: $(TARGET)

# Regra para linkar os objetos e gerar o executável
$(TARGET): $(OBJS)
	@if not exist "executable" mkdir "executable"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# SOLUÇÃO PARA WINDOWS: Cria a subpasta usando a sintaxe do CMD antes de compilar
$(OBJ_DIR)/%.o: %.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza compatível com Windows
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist executable rmdir /s /q executable

run: $(TARGET)
	@if not exist "Results" mkdir "Results"
	.\$(TARGET)

.PHONY: all clean run
