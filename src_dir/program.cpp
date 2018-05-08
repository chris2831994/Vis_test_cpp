#include <gtkmm.h>
#include <iostream>
using namespace std;
#include "LineVisualizer.h"
#include <fftw3.h>
#include <thread>

#define samples 1024

int main(int argc, char **argv){

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_title("Music Visualizer");
    Visualizer *vis = new LineVisualizer(samples);
    window.add(*vis);
    vis->show();
    app->run(window);

}