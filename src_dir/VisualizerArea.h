#ifndef MPD_VISUALIZER_AREA_H
#define MPD_VISUALIZER_AREA_H

#include <gtkmm/drawingarea.h>

class VisualizerArea : public Gtk::DrawingArea
{
public:
    VisualizerArea();
    virtual ~VisualizerArea();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

    double m_radius;
    double m_line_width;
    
};

#endif // MPD_VISUALIZER_AREA_H