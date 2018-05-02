#ifndef MPD_LINE_VISUALIZER_H
#define MPD_LINE_VISUALIZER_H

#include <gtkmm/drawingarea.h>
#include "FifoProcessor.h"
#include "Visualizer.h"

class LineVisualizer : public Visualizer
{
public:
    LineVisualizer(int samples);
    ~LineVisualizer();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    FifoProcessor * processor;
    int samples;
};

#endif // MPD_LINE_VISUALIZER_H