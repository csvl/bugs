CC = gcc
CFLAGS  = -O0 -ggdb3
TARGET = oob_static

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
