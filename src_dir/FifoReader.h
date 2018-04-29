//
// Created by chris on 4/29/18.
//

#ifndef VIS_TEST_CPP_FIFOREADER_H
#define VIS_TEST_CPP_FIFOREADER_H

#include <stdint.h>

class FifoReader{
public:
    virtual int readFifo()= 0;
    virtual uint16_t * getReadingBuffer() = 0;
};


#endif //VIS_TEST_CPP_FIFOREADER_H
