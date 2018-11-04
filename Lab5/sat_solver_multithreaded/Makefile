SRC=mainMT.c
HEADERS=
TARGET=sat_solver
CC=gcc-8
CC_FLAGS=-pthread -std=c99

all: $(SRC) $(HEADERS)
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)