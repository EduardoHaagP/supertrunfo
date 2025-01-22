# Nome do executável
TARGET = programa

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -g

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Sistema operacional
ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

# Configurações específicas do sistema operacional
ifeq ($(OS),Windows_NT)
  LIB_DIR = libwin
  RAYLIB_FLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR) -lraylib -lm -lopengl32 -lgdi32 -lwinmm
  RM = del /Q /F
  MKDIR = mkdir
  TARGET := $(TARGET).exe
else
  LIB_DIR = lib
  RAYLIB_FLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  RM = rm -f
  MKDIR = mkdir -p
endif

# Arquivos fonte e objeto
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: $(OBJ_DIR) $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(RAYLIB_FLAGS)

# Regra para compilar os arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para criar o diretório obj, se não existir
$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

# Limpar os arquivos objeto e o executável
clean:
	$(RM) $(OBJ_DIR)/*.o $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para forçar a recompilação
.PHONY: all clean run

