#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void CCircle::draw(QPainter &painter, QRect restriction)
{
    painter.setClipRect(restriction);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(x - rad, y - rad, 2 * rad, 2 * rad);
}

bool CCircle::contains(int px, int py)
{
    return (px - x) * (px - x) + (py - y) * (py - y) <= rad*rad;
}


void MyStorage::AddObject(int x, int y)
{
    circles.push_back(new CCircle(x, y));
}

void MyStorage::drawCircles(QPainter &painter, QRect restriction)
{
    for (size_t i = 0; i<circles.size();i++){
        circles[i]->draw(painter, restriction);
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    storage.drawCircles(painter, ui->frame->geometry());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QRect frameGeometry = ui->frame->geometry();
        QPoint localPos = event->pos() - frameGeometry.topLeft();

        int cornerThreshold = 20;

        bool topLeft = (localPos.x() < cornerThreshold && localPos.y() < cornerThreshold);
        bool topRight = (localPos.x() > frameGeometry.width() - cornerThreshold && localPos.y() < cornerThreshold);
        bool bottomLeft = (localPos.x() < cornerThreshold && localPos.y() > frameGeometry.height() - cornerThreshold);
        bool bottomRight = (localPos.x() > frameGeometry.width() - cornerThreshold && localPos.y() > frameGeometry.height() - cornerThreshold);


        if (topLeft || topRight || bottomLeft || bottomRight)
        {
            isResizing = true;
            lastMousePosition = event->pos();
            return;
        }

        storage.AddObject(event->pos().x(), event->pos().y());
        update();

    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isResizing) {
        int dx = event->position().x() - lastMousePosition.x();
        int dy = event->position().y() - lastMousePosition.y();

        ui->frame->resize(ui->frame->width() + dx, ui->frame->height() + dy);
        lastMousePosition = event->pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isResizing = false;
}


