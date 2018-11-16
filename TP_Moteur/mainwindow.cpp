#include "mainwindow.h"

#include <QMouseEvent>

MainWindow::MainWindow(int sizeW, int sizeH, int W, QWidget *parent) :
    sizeW(sizeW),
    sizeH(sizeH),
    W(W),
    x(0),
    y(0),
    mouseXPosition(0),
    mouseYPosition(0)
{
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    doneCurrent();
}

void MainWindow::add(MainWidget *w){

    layout->addWidget(w,x,y,1,1);

    w->setLayoutCoord(x,y);

    x++;
    if(x>W-1){
        x=0;
        y++;
    }
}

void MainWindow::show(){
    this->resize(sizeW,sizeH);
    QWidget::show();
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    // Save mouse press position
    //mousePressPosition = QVector2D(e->localPos());
    mouseXPosition = e->localPos().y()*y/sizeH;
    mouseYPosition = e->localPos().x()*W/sizeW;
}

void MainWindow::keyPressEvent(QKeyEvent *k){
    emit event(mouseXPosition,mouseYPosition,k);
    layout;
    update();
}
