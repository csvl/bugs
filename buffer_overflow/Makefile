CC = gcc
CFLAGS  = -O0 -ggdb3 -fno-stack-protector
TARGET = buffer_overflow

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
