TARGET=main
CFLAGS=-Wall -O2
LDFLAGS=
CC=gcc

all: $(TARGET)

$(TARGET): main.c individu.o population.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -lm -o $@ $< 

clean:
	rm -f $(TARGET) *.o