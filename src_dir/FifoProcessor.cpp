//
// Created by chris on 5/1/18.
//

#include "FifoProcessor.h"

FifoProcessor::FifoProcessor(int sampleSize) : sampleSize(sampleSize) , averageStep(sampleSize/128){

    this->reader = new MPDFifoReader("/tmp/mpd.fifo", this->sampleSize);
    //this->dataBuffer = (uint16_t *) malloc(sizeof(uint16_t) * this->sampleSize);
    this->dataBuffer = reader->getReadingBuffer();
    this->averageDataBuffer = (uint16_t *) malloc(sizeof(uint16_t) * 128);
    this->processedDataBuffer = (uint16_t *) malloc(sizeof(uint16_t) * this->sampleSize);
    this->fftInput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * this->sampleSize);
    this->fftOutput = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * this->sampleSize);
    this->fftPlan = fftw_plan_dft_1d(this->sampleSize, this->fftInput, this->fftOutput, FFTW_FORWARD,  FFTW_ESTIMATE);

}

FifoProcessor::~FifoProcessor() {

    free(this->processedDataBuffer);
    free(this->averageDataBuffer);
    delete(this->reader);
    fftw_destroy_plan(fftPlan);
    fftw_free(fftInput);
    fftw_free(fftOutput);

}

/**
 * Processes data in dataBuffer, writes to processedDataBuffer
 */
void FifoProcessor::process() {
    if(reader->readFifo()!=0){
        for(int i = 0; i < sampleSize; i++){
            fftInput[i][0] = dataBuffer[i];
            fftInput[i][1] = 0;
        }
        fftw_execute(fftPlan);
        for(int i =0; i<sampleSize; i++){


            int sq = sqrt(pow(fftOutput[i][0], 2) + pow(fftOutput[i][1], 2));
            int res = round(20*log10(sq));

            this->processedDataBuffer[i] = res;
            //std::cout << res;

        }
    } else {
        std::cout << "error reading fifo";
    }
}

uint16_t *FifoProcessor::average(){

    int k = 0;
    for(int i = 0; i < sampleSize; i+=averageStep){
        int avg = 0;
        for(int j = 0; j < averageStep; j++){
            avg += processedDataBuffer[i+j];
        }
        this->averageDataBuffer[k] = avg/averageStep;
        k++;
    }

    return averageDataBuffer;

}

void FifoProcessor::setData(uint16_t *data) {
    this->dataBuffer = data;
}

uint16_t * FifoProcessor::getProcessedData() {
    return this->processedDataBuffer;
}