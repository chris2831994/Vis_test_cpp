#include <gtkmm.h>
#include <iostream>
using namespace std;
#include "VisualizerArea.h"
#include "FifoReader.h"
#include "MPDFifoReader.h"
#include <fftw3.h>
#include <thread>

#define samples 1024

void processing(uint16_t *resultBuffer){

    FifoReader *reader = new MPDFifoReader("/tmp/mpd.fifo", samples);

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samples);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * samples);
    p = fftw_plan_dft_1d(samples, in, out, FFTW_FORWARD,  FFTW_ESTIMATE);



    while(true){
        if(cin.get() == 'q') break;
        if(reader->readFifo()!=0){
            uint16_t * buf = reader->getReadingBuffer();
            for(int i = 0; i < samples; i++){
                in[i][0] = buf[i];
                in[i][1] = 0;
            }
            fftw_execute(p);
            for(int i =0; i<samples; i++){


                int sq = sqrt(pow(out[i][0], 2) + pow(out[i][1], 2));
                int res = round(20*log10(sq));

                resultBuffer[i] = res;

                cout << res << endl;
            }
        } else {
            cout << "error reading fifo";
        }
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    free(resultBuffer);
    delete reader;

}

void ui(uint16_t * bufDb, int argc, char **argv ){

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_title("Music Visualizer");
    VisualizerArea vis(samples);
    vis.setDisplayBuffer(bufDb);
    window.add(vis);
    vis.show();
    app->run(window);

}

int main(int argc, char **argv){

    uint16_t * bufDb = (uint16_t *) malloc(sizeof(uint16_t) * samples);
    std::thread processing_thread(processing, bufDb);
    std::thread ui_thread(ui, bufDb, argc, argv);

    processing_thread.join();
    ui_thread.join();

    return 0;
}