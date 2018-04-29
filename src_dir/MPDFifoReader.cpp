//
// Created by chris on 4/29/18.
//

#include "MPDFifoReader.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

MPDFifoReader::MPDFifoReader(char *filename, int fftSize) : fftSize(fftSize) {
    this->fifo = open(filename, O_RDONLY);
    this->buf = (uint16_t *) malloc(sizeof(uint16_t) * fftSize);
}

MPDFifoReader::~MPDFifoReader() {
    close(this->fifo);
    free(buf);
}

int MPDFifoReader::readFifo() {
    return read(this->fifo,(uint16_t *) buf, 2*this->fftSize);
}

uint16_t * MPDFifoReader::getReadingBuffer(){
    return this->buf;
}