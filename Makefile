CC = gcc
CFLAGS = -O0 -g3 -Wall
LFLAGS = 
DEPS = protobuf.h
OBJS = testit.o protobuf.o varint.o Test1_protobuf.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_protobuf: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

all: test_protobuf

clean:
	rm -f *.o
	rm -f test_protobuf
	
rebuild: clean all