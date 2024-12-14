# Nome do executável
TARGET = programa

# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -g

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos objeto e o executável
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Regras para forçar a recompilação
.PHONY: all clean