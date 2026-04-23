# --- CONFIGURAZIONE macOS ---
TARGET = main
CC = gcc
CFLAGS = -Wall -std=c99 -Wno-missing-braces

# Percorsi Homebrew (Necessari su Apple Silicon M1/M2/M3)
INCLUDE_PATH = -I/opt/homebrew/include
LIBRARY_PATH = -L/opt/homebrew/lib

# Framework richiesti da macOS per la grafica
LDFLAGS = $(LIBRARY_PATH) -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL

# --- REGOLE ---

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS) $(INCLUDE_PATH) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
