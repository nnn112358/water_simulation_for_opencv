
CC :=g++

CFLAGS :=`pkg-config opencv4 --cflags` `pkg-config opencv4 --libs` -I/usr/include/eigen3
LDFLAGS :=

SOURCES :=$(wildcard *.cpp)

EXECUTABLE :=$(SOURCES:.cpp=)

all:$(EXECUTABLE)

$(EXECUTABLE):$(SOURCES)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o $@

clean:
	rm -rf $(EXECUTABLE)
