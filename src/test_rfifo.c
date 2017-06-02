#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdarg.h>

#include "rfifo.h"
#include "julog.h"

int runloop = 0;
static rfifo fifo;
#define RET_DATA_SIZE 10


#define MAX_CHUNK_NUM 6

static unsigned short frame_no = 0;
static unsigned int cid = 0;
#define RFIFO_FULL 1

int new_chunk_to_rfifo(rfifo *f ,unsigned int i)
{
    char *pdata = NULL;
    int data_size = 0;
    int rc = 0;

    pdata = rfifo_acquire_chunk_buf(f);
    if (!pdata)
        return RFIFO_FULL;

    cid %= MAX_CHUNK_NUM;
    data_size = snprintf((char *)pdata, CHUNK_DATA_SIZE-1, "c%u data%u", cid, i);
    cid++;

    rc = rfifo_filled_chunk_buf(f,
            frame_no++,
            (unsigned int )data_size);
#ifdef HAVE_DUMP_CHUNK
    rfifo_dump_chunk(&fifo, i);
#endif /* HAVE_DUMP_CHUNK */
    return rc;
}

void *thread_chunk_consumer(void *parg)
{
    char *ret = (char *)malloc(RET_DATA_SIZE);
    pthread_t tid = pthread_self();
    JULOG("thread consumer started %lu\n", tid);
    while (1)
    {
        int rc = 0;
        runloop++;
    
        char *r = rfifo_play_chunk(&fifo);
        if (r == NULL) {
//#define HAVE_DEBUG_NO_NEW_CHUNK 1
#ifdef HAVE_DEBUG_NO_NEW_CHUNK
            JULOG("%d no new chunk, wait...\n", runloop);
#endif
            usleep(15000);
            continue;
        }
        JULOG("%d cnt=%u rc = %d, data: %s\n", runloop, fifo.count, rc, r);
        rc = rfifo_played_chunk(&fifo);
        usleep(33000);
    }
    strncpy(ret, "123456789", RET_DATA_SIZE);
    JULOG("thread comsumer exit %lu\n", tid);
    pthread_exit((void *) ret);
}


void *thread_chunk_producer(void *parg)
{
    unsigned int i = 1;
    unsigned int delay = 1;

    pthread_t tid = pthread_self();
    JULOG("thread producer started %lu\n", tid);
    while (1)
    {
        int rc = 0;
        if (i % 50 == 0) {
            delay = 15000;
        } else {
            if (i % 85 == 0)
                delay = 1000000;
            else
                delay = 33000;
        }
        rc = new_chunk_to_rfifo(&fifo, ++i);
        while (rc == RFIFO_FULL) {
            usleep(10);
            continue;
        }
        usleep(delay);
    }

    JULOG("thread producer exit %lu\n", tid);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    unsigned int num = MAX_CHUNK_NUM;
    char *r = NULL;
    int rc = 0;
    pthread_t tid[2];

    rc = rfifo_init(&fifo, num);
    pthread_create(&tid[0], NULL, &thread_chunk_consumer, &num);
    pthread_create(&tid[1], NULL, &thread_chunk_producer, &num);

    pthread_join(tid[0], (void **)&r);
    pthread_join(tid[1], NULL);
    JULOG("r=[%s]\n", r);
    free(r);

    return rc;
}
