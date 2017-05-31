CFLAGS    = -Wall -fPIC
OBJS      = rfifo.o  julog.o
TEST_OBJS = test_rfifo.o
LDFLAGS   = -lpthread
LIBA      = librfifo.a
TARGET_BIN= test_rfifo 

all: $(TARGET_BIN)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET_BIN): $(TEST_OBJS) $(LIBA)
	$(CC) $^ -o $@ $(LDFLAGS)

$(LIBA): $(OBJS)
	$(AR) cru $@ $^

tests: $(TARGET_BIN)
	./$^

clean:
	rm -f *.o $(TARGET_BIN)
