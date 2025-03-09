# Definindo o compilador
CXX = g++
CXXFLAGS = -I/home/rodrigo/github/OpenGL/include -I/usr/include/GLFW -I./src  # Corrigir caminho para o diretório 'include'
LIBS = -lglfw -lGL -lm -ldl # Bibliotecas para linkar (GLFW, OpenGL e matemática)

# Nome do executável
TARGET = meu_programa

# Arquivos de origem
SRC = src/main.cpp src/glad.c 
OBJ = $(SRC:.cpp=.o)

# Regra padrão: compilar o executável
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -v -o $@ $^ $(LIBS)

# Compilar o arquivo .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos de compilação
clean:
	rm -f $(OBJ) $(TARGET)


