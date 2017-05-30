CFLAGS=-Wall
OBJS=rfifo.o test_rfifo.o julog.o
LDFLAGS = -lpthread
TARGET_BIN=test_rfifo 

all: $(TARGET_BIN)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET_BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

tests: $(TARGET_BIN)
	./$^

clean:
	rm -f *.o test_ring_fifo
