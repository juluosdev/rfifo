/*
Copyright (C) 2017 Ben Wei <ben@juluos.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <stdarg.h>
#include <stdio.h>
#include <sys/time.h> /* gettimeofday */
#include <pthread.h>

#define MAX_JULOG_SIZE 1024
pthread_mutex_t logmutex     = PTHREAD_MUTEX_INITIALIZER;

void julog(const char *fmt, ...)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
    va_list args;
    char buf[MAX_JULOG_SIZE] = {0};
    pthread_mutex_lock(&logmutex);
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf) - 1, fmt, args);
    fprintf(stdout, "%8lu.%06lu %s", tv.tv_sec, tv.tv_usec, buf);
    fflush(stdout);
    pthread_mutex_unlock(&logmutex);
    va_end(args);
}
