//
// Created by chris on 5/1/18.
//

#ifndef VIS_TEST_CPP_FIFOPROCESSOR_H
#define VIS_TEST_CPP_FIFOPROCESSOR_H

#include <stdint.h>
#include <iostream>
#include <fftw3.h>
#include "FifoReader.h"
#include "MPDFifoReader.h"
#include <stdlib.h>
#include <math.h>

class FifoProcessor{
public:
    FifoProcessor(int sampleSize);
    ~FifoProcessor();
    void setData(uint16_t *data);
    uint16_t *getProcessedData();
    void process();
    uint16_t *average();

protected:
    FifoReader *reader;
    fftw_complex *fftInput, *fftOutput;
    fftw_plan fftPlan;
    uint16_t *dataBuffer;
    uint16_t *processedDataBuffer;
    uint16_t *averageDataBuffer;
    int sampleSize;
    int averageStep;
};

#endif //VIS_TEST_CPP_FIFOPROCESSOR_H
