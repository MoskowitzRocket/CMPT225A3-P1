GXX = g++
CFLAGS = -std=c++20 -Wall -Wextra

TARGET = TestIndPQ
SRC = TestIndPQ.cpp QuadraticProbing.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(GXX) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp heap.h IndPQ.h
	$(GXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)
