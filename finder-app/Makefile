# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Define the target executable
TARGET = writer

# Define the source files
SRCS = writer.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Default target: build the application
all: $(TARGET)

# Target to compile the application
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove the application and all .o files
clean:
	rm -f $(TARGET) $(OBJS)

# Support for cross-compilation
ifdef CROSS_COMPILE
CC = $(CROSS_COMPILE)gcc
endif

.PHONY: all clean
