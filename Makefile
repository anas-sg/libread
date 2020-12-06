CC = gcc
CFLAGS = -Wall -std=c11
TARGET = main
FILES = read.c main.c

.SILENT:
.PHONY: all
all: $(TARGET) run

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES)

run:
	$(info Running $(TARGET)...)
	./$(TARGET)
