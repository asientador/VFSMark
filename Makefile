CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

SRC_DIR = src
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)

EXECUTABLE = $(BIN_DIR)/exec

all: $(EXECUTABLE)

$(EXECUTABLE) : $(SOURCES)
	@mkdir -p $(BIN_DIR)	
	$(CC) $(CFLAGS) $^ -o $@ 

clean :
	rm -rf $(BIN_DIR)


