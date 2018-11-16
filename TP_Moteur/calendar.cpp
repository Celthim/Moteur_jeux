
#include "calendar.h"

Calendar::Calendar(int DayTime, QWidget *parent) :
    QOpenGLWidget(parent),
    DayTime(DayTime)
{
}

Calendar::~Calendar()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    doneCurrent();
}

void Calendar::initCalendar(){
    timer.start(DayTime*1000, this);
}

void Calendar::timerEvent(QTimerEvent *)
{
    emit seasonChanged();
}
