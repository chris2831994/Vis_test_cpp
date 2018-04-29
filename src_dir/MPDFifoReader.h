//
// Created by chris on 4/29/18.
//

#ifndef VIS_TEST_CPP_MPDFIFOREADER_H
#define VIS_TEST_CPP_MPDFIFOREADER_H

#include "FifoReader.h"
#include <stdint.h>

class MPDFifoReader : public FifoReader {

int fifo, fftSize;
uint16_t *buf;

public:
    MPDFifoReader(char *filename, int fftSize);
    ~MPDFifoReader();
    int readFifo();
    uint16_t * getReadingBuffer();
};

#endif //VIS_TEST_CPP_MPDFIFOREADER_H
