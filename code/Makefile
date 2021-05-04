CC = gcc
CFLAGS = -std=gnu11 -std=c99 -Wall -Wextra -pedantic-errors -O -g
LIBS = -lm
OBJS = main.o convertions.o equations.o types.o parser.o stack.o blocks.o
TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main

clean:
	@rm -f $(TARGET) $(OBJS)