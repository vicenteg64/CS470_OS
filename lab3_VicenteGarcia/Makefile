#Define compiler to use
CC=gcc

#Define any Flags in compile time
CFLAGS=-Wall -Wextra -g

TARGET=SJF_inital
TARGET2=RR_inital

all: $(TARGET) $(TARGET2)

$(TARGET): $(TARGET).c
		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

$(TARGET2): $(TARGET2).c
		$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c