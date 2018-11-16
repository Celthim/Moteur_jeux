#ifndef CALENDAR_H
#define CALENDAR_H

#include <QBasicTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Calendar : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Calendar(int DayTime, QWidget *parent = 0);
    ~Calendar();
    void initCalendar();

signals :
    void seasonChanged();

protected:
    void timerEvent(QTimerEvent *e) override;


private:
    QBasicTimer timer;
    int DayTime;
};


#endif // CALENDAR_H

