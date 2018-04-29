#include <gtkmm.h>
#include <iostream>
using namespace std;
#include "VisualizerArea.h"
#include "FifoReader.h"
#include "MPDFifoReader.h"
#include <fftw3.h>

// void process_mpd (int fifo) {
// 	uint16_t buf[N_SAMPLES];
// 	unsigned int *fftBuf, *fftAvg;
// 	int correction; //curses

// 	while(read(fifo, (uint16_t*)buf, 2*N_SAMPLES) != 0){
// 		// close on keypress 'q'
// 		if(wgetch(stdscr)=='q'){
// 			break;
// 		}

// 		// performs a Fourier Transform of the buffer data
// 		fftBuf = fast_fft(N_SAMPLES, (uint16_t*)buf);

// 		// computes an average of the signals in fftBuf
// 		// based on t                                                                                                                                                           he number of columns of the screen
// 		fftAvg = average_signal(fftBuf, N_SAMPLES, maxC);	
// 		free(fftBuf);

// 		// clear the screen


// 		// correction can be used to exclude certain frequencies
// 		// not advised nor customary
// 		correction = 0;
// 		int i;
// 		for(i=correction; i<maxC; i=i+2){
// 			// check boundaries of the signals respect the boundaries of the screen
// 			// if they don't, setting them to 1 is a safety measure
// 			// 0 and maxR can give segmentation errors on curses printing
// 			if(fftAvg[i] > maxR || fftAvg[i] < 0){
// 				fftAvg[i] = 1;
// 			}

// 		}
// 		// refresh the screen, free the allocated buffer

// 		free(fftAvg);
// 	}
// }

int main(int argc, char **argv){


    //auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    //Gtk::Window window;
    //window.set_title("Music Visualizer");

    //VisualizerArea vis;
    //window.add(vis);
    //vis.show();

    //return app->run(window);

    int samples = 1024;

    FifoReader *reader = new MPDFifoReader("/tmp/mpd.fifo", samples);

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samples);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samples);
    p = fftw_plan_dft_1d(samples, in, out, FFTW_FORWARD,  FFTW_ESTIMATE);

    while(true){
        if(reader->readFifo()!=0){
            uint16_t * buf = reader->getReadingBuffer();
            for(int i = 0; i < samples; i++){
                in[i][0] = buf[i];
                in[i][1] = 0;
            }
            fftw_execute(p);
            for(int i =0; i<samples; i++){
                cout << "r :" << out[i][0] << ", i :" << out[i][1] << endl;
            }
        } else {
            cout << "error reading fifo";
        }
    }

    return 0;
}