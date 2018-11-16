#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGridLayout>
#include <QWidget>
#include "mainwidget.h"

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWindow(int sizeW, int sizeH, int W, QWidget *parent = 0);
    ~MainWindow();
    void add(MainWidget *w);
    void show();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    //void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *k) override;

signals :
    void event(int x, int y, QKeyEvent* key);

private:

    int sizeW;
    int sizeH;
    int W;
    int x;
    int y;
    QVector2D mousePressPosition;
    int mouseXPosition;
    int mouseYPosition;
    QGridLayout *layout = new QGridLayout;
};

#endif // MAINWINDOW_H
