//
// Created by chris on 4/26/18.
//

#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "VisualizerArea.h"

VisualizerArea::VisualizerArea()
: m_radius(0.42), m_line_width(0.05)
{
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &VisualizerArea::on_timeout), 1000);
}

VisualizerArea::~VisualizerArea()
{

}

bool VisualizerArea::on_draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cr->scale(width, height);
    cr->translate(0.5, 0.5);
    cr->set_line_width(m_line_width);

    cr->save();
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9);
    cr->paint();
    cr->restore();
    cr->arc(0,0, m_radius, 0, 2 * M_PI);
    cr->save();
    cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
    cr->fill_preserve();
    cr->restore();
    cr->stroke_preserve();
    cr->clip();

    for(int i = 0; i < 12; i++){
        double inset = 0.05;

        cr->save();
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        if(i % 3 != 0){
            inset *= 0.8;
            cr->set_line_width(0.03);
        }

        cr->move_to(
                (m_radius - inset) * cos (i * M_PI / 6),
                (m_radius - inset) * sin(i * M_PI / 6));
        cr->line_to(
                m_radius * cos(i * M_PI / 6),
                m_radius * sin(i * M_PI / 6));
        cr->stroke();
        cr->restore();
    }

    time_t rawtime;
    time(&rawtime);

    struct tm * timeinfo = localtime(&rawtime);

    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds = timeinfo->tm_sec * M_PI / 30;

    cr->save();
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    cr->save();
    cr->set_line_width(m_line_width / 3);
    cr->set_source_rgba(0.7, 0.7, 0.7, 0.8);
    cr->move_to(0, 0);
    cr->line_to(sin(seconds) * (m_radius * 0.9), -cos(seconds) * (m_radius * 0.9));
    cr->stroke();
    cr->restore();

    // draw the minutes hand
    cr->set_source_rgba(0.117, 0.337, 0.612, 0.9);   // blue
    cr->move_to(0, 0);
    cr->line_to(sin(minutes + seconds / 60) * (m_radius * 0.8), -cos(minutes + seconds / 60) * (m_radius * 0.8));
    cr->stroke();

    // draw the hours hand
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
    cr->move_to(0, 0);
    cr->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5), -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    cr->stroke();
    cr->restore();

    cr->arc(0,0, m_line_width / 3.0, 0, 2 * M_PI);
    cr->fill();

    return true;
}

bool VisualizerArea::on_timeout() {
    auto win = get_window();
    if(win){
        Gdk::Rectangle r(0,0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}