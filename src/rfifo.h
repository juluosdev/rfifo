/*
Copyright (C) 2017 Ben Wei <ben@juluos.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef RFIFO_H
#define RFIFO_H 1

/**
 * chunk structure 
 * 
 * should keep timpstamp?
 *     state    frmno    data
 *    +--------+-----+------------+
 *    |state(1)| 1   |   data 1   |
 *    +--------+-----+------------+
 *    +--------+-----+------------+
 *    +--------+-----+------------+
 *    +--------+-----+------------+
 *    |state(1)| N   |   data N   |
 *    +--------+-----+------------+
 */

#define CHUNK_DATA_SIZE 1024
/* definitions of chunk state */
#define CHUNK_STATE_EMPTY    0  /* default unsed */
#define CHUNK_STATE_ACQUIRED 1  /* chunk state wait to receive data via network */
#define CHUNK_STATE_READY    2  /* data filled, ready to use */ 
#define CHUNK_STATE_PLAYING  3  /* playing data */ 

typedef struct _rfifo_chunk {
    unsigned char state;
    unsigned long seq;
    unsigned short size;
    char data[CHUNK_DATA_SIZE];
} rfifo_chunk;

typedef struct _rfifo {
    unsigned short num;
    unsigned short head;
    unsigned short tail;
    unsigned short count;  /* chunk num in queue  */
    rfifo_chunk *chunks;
} rfifo;

int rfifo_init(rfifo *f, unsigned short num);
 
char *rfifo_acquire_chunk_buf(rfifo *f);

int rfifo_filled_chunk_buf(rfifo *f,
        unsigned long seq,
        unsigned int data_size);

int rfifo_set_chunk_state(rfifo *f, unsigned short index, unsigned char state);
void rfifo_dump_chunk(rfifo *f, unsigned short index);

char *rfifo_play_chunk(rfifo *f);
int rfifo_played_chunk(rfifo *f);

#endif /* RFIFO_H */
