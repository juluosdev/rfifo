/*
Copyright (C) 2017 Ben Wei <ben@juluos.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "rfifo.h"

pthread_mutex_t rmutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  rcond   = PTHREAD_COND_INITIALIZER;

int rfifo_init(rfifo *f, unsigned short num)
{
    f->num = num;
    f->tail = 0;
    f->head = 0;
    f->chunks = (rfifo_chunk *) malloc(sizeof(rfifo_chunk) * num);
    if (!f->chunks)
        return -1;

    return 0;
}

/*
 * used point to receive data directly, avoid to memory.
 */
unsigned char *rfifo_acquire_chunk_buf(rfifo *f)
{
    rfifo_chunk *p = NULL;

    pthread_mutex_lock(&rmutex);
    p = &f->chunks[f->tail];
    while (f->count == f->num || p->state != CHUNK_STATE_EMPTY)
    {
        pthread_cond_wait(&rcond, &rmutex);
    }

    p->state = CHUNK_STATE_ACQUIRED;
    pthread_mutex_unlock(&rmutex);
    return p->data;
}

int rfifo_filled_chunk_buf(rfifo *f,
        unsigned long seq,
        unsigned int data_size)
{
    rfifo_chunk *p = NULL;

    pthread_mutex_lock(&rmutex);

    p = &f->chunks[f->tail];
    p->seq = seq;
    p->size = data_size;
    f->tail++;
    if (f->tail == f->num) {
        f->tail = 0;
    }
    p->state = CHUNK_STATE_READY;
    f->count++;
    pthread_mutex_unlock(&rmutex);
    return 0;
}

const unsigned char *rfifo_play_chunk(rfifo *f)
{
    unsigned char *r = NULL;
    rfifo_chunk *p = NULL;

    pthread_mutex_lock(&rmutex);
    
//    while (f->count == 0)
//        pthread_cond_wait(&rcond, &rmutex);

    p = &f->chunks[f->head];
    if (p->state == CHUNK_STATE_READY) {
        p->state = CHUNK_STATE_PLAYING;
        r = p->data;
    }
    pthread_mutex_unlock(&rmutex);
    return r;
}

int rfifo_played_chunk(rfifo *f)
{
    rfifo_chunk *p = NULL;

    pthread_mutex_lock(&rmutex);
    p = &f->chunks[f->head];
    p->state = CHUNK_STATE_EMPTY;
    f->head++;
    if (f->head == f->num) {
        f->head = 0;
    }
    f->count--;
    pthread_cond_signal(&rcond);
    pthread_mutex_unlock(&rmutex);
    return 0;
}

int rfifo_set_chunk_state(rfifo *f, unsigned short index, unsigned char state)
{
    if (index < f->num) {
        rfifo_chunk *p = &f->chunks[index];
        p->state = state;
        return 0;
    }

    return -1;
}


void rfifo_dump_chunk(rfifo *f, unsigned short index)
{
    if (index < f->num) {
        rfifo_chunk *p = &f->chunks[index];

        printf("state:%u frmno:%lu d[%u]:%s\n", p->state,
                p->seq,
                p->size,
                p->data
              );
        return ;
    }

    printf("no such chunk id\n");
}

