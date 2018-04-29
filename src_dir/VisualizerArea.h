#ifndef MPD_VISUALIZER_AREA_H
#define MPD_VISUALIZER_AREA_H

#include <gtkmm/drawingarea.h>

class VisualizerArea : public Gtk::DrawingArea
{
public:
    VisualizerArea(int samples);
    virtual ~VisualizerArea();
    void setDisplayBuffer(uint16_t * buf);
    void update();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    uint16_t * displayBuffer;
    int samples;
};

#endif // MPD_VISUALIZER_AREA_H