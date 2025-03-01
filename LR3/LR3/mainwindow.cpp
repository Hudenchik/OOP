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

bool CCircle::circleContains(int px, int py)
{
    return (px - x) * (px - x) + (py - y) * (py - y) <= rad*rad;
}

void CCircle::select(QPainter &painter)
{
    painter.setBrush(Qt::darkBlue);
    painter.drawEllipse(x - rad, y - rad, 2 * rad, 2 * rad);
}

int CCircle::getX()
{
    return x;
}

int CCircle::getY()
{
    return y;
}

int CCircle::getRad()
{
    return rad;
}


void MyStorage::AddObject(int x, int y)
{
    circles.push_back(new CCircle(x, y));
    qDebug() << "Added circle: " << circles.back();
}

void MyStorage::drawCircles(QPainter &painter, QRect restriction)
{
    for (size_t i = 0; i<circles.size();i++){
        circles[i]->draw(painter, restriction);
    }
}

bool MyStorage::isCircle(int px, int py, bool ctrlPressed)
{
    bool flag = false;
    vector<CCircle*> intersectedCircles;
    for (size_t i = 0; i < circles.size(); i++)
    {
        if (circles[i]->circleContains(px, py))
        {
            intersectedCircles.push_back(circles[i]);
        }
    }

    if (!intersectedCircles.empty())
    {
        if (ctrlPressed)
        {
            bool allSelected = true;
            for (size_t i = 0; i<intersectedCircles.size(); i++)
            {
                if (find(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]) == selectedCircles.end())
                {
                    allSelected = false;
                    break;
                }
            }

            if (allSelected)
            {
                for (size_t i = 0; i<intersectedCircles.size(); i++)
                {
                    selectedCircles.erase(remove(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]), selectedCircles.end());
                    qDebug() << "Unselected circle: " << intersectedCircles[i];
                }
            }
            else
            {
                for (size_t i = 0; i<intersectedCircles.size(); i++)
                {
                    if (find(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]) == selectedCircles.end())
                    {
                        selectedCircles.push_back(intersectedCircles[i]);
                        qDebug() << "Selected circle: " << intersectedCircles[i];
                    }
                }
            }
        }
        else
        {
            bool allSelected = true;
            for (size_t i = 0; i<intersectedCircles.size(); i++)
            {
                if (find(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]) == selectedCircles.end())
                {
                    selectedCircles.clear();
                    allSelected = false;
                    break;
                }
            }

            if (allSelected)
            {
                for (size_t i = 0; i<intersectedCircles.size(); i++)
                {
                    selectedCircles.erase(remove(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]), selectedCircles.end());
                    qDebug() << "Unselected circle: " << intersectedCircles[i];
                }
            }
            else
            {
                for (size_t i = 0; i<intersectedCircles.size(); i++)
                {
                    if (find(selectedCircles.begin(), selectedCircles.end(), intersectedCircles[i]) == selectedCircles.end())
                    {
                        // selectedCircles.clear();
                        selectedCircles.push_back(intersectedCircles[i]);
                        qDebug() << "Selected circle: " << intersectedCircles[i];
                    }
                }
            }
        }
        flag = true;
    }
    return flag;
}

void MyStorage::selectCircles(QPainter &painter)
{
    for (size_t i = 0; i < selectedCircles.size(); i++)
    {
        selectedCircles[i]->select(painter);
    }
}

void MyStorage::deleteCircles()
{
    for (size_t i = 0; i < selectedCircles.size(); i++)
    {
        qDebug() << "Deleted circle: " << selectedCircles.back();
        circles.erase(remove(circles.begin(), circles.end(), selectedCircles[i]), circles.end());
    }
    selectedCircles.clear();
}

void MyStorage::squareSelect(QRect &square)
{
    for (size_t i = 0; i < circles.size(); i++)
    {
        int cx = circles[i]->getX();
        int cy = circles[i]->getY();
        int rad = circles[i]->getRad();

        bool intersects = false;

        if (square.contains(cx - rad, cy - rad) || square.contains(cx + rad, cy + rad) ||
            square.contains(cx - rad, cy + rad) || square.contains(cx + rad, cy - rad) ||
            square.intersects(QRect(cx - rad, cy - rad, 2 * rad, 2 * rad)))
        {
            intersects = true;
        }

        if (intersects)
        {
            if (find(selectedCircles.begin(), selectedCircles.end(), circles[i]) == selectedCircles.end())
            {
                selectedCircles.push_back(circles[i]);
                qDebug() << "Selected circle: " << circles[i];
            }
        }
        else
        {
            selectedCircles.erase(remove(selectedCircles.begin(), selectedCircles.end(), circles[i]), selectedCircles.end());
            qDebug() << "Unselected circle: " << circles[i];
        }
    }
}


MyStorage::~MyStorage()
{
    for (size_t i = 0; i<circles.size();i++){
        delete circles[i];
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setClipRect(ui->frame->geometry());
    storage.drawCircles(painter, ui->frame->geometry());
    storage.selectCircles(painter);

    if (squareIsResizing)
    {
        QPen pen(Qt::black, 2, Qt::DashLine);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(square);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QRect frameGeometry = ui->frame->geometry();
        QPoint localPos = event->pos() - frameGeometry.topLeft();

        int corner = 5;

        bool topLeft = (abs(localPos.x()) < corner && abs(localPos.y()) < corner);
        bool topRight = (abs(localPos.x()-frameGeometry.width()) < corner && abs(localPos.y()) < corner);
        bool bottomLeft = (abs(localPos.x()) < corner && abs(localPos.y() - frameGeometry.height()) < corner);
        bool bottomRight = (abs(localPos.x()-frameGeometry.width()) < corner && abs(localPos.y() - frameGeometry.height()) < corner);

        if (topLeft || topRight || bottomLeft || bottomRight)
        {
            isResizing = true;
            lastMousePosition = event->pos();
            return;
        }

        if (frameGeometry.contains(event->pos()))
        {

            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            if (storage.isCircle(event->pos().x(), event->pos().y(), ctrlPressed))
            {
                update();
                return;
            }
            else
            {
                if (!ctrlPressed)
                {
                    storage.AddObject(event->pos().x(), event->pos().y());
                    update();

                }
                else
                {
                    squareIsResizing = true;
                    startPoint = event->pos();
                    square.setTopLeft(startPoint);
                    square.setBottomRight(startPoint);
                    update();
                }
            }

        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
    {
        storage.deleteCircles();
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isResizing)
    {
        int dx = event->position().x() - lastMousePosition.x();
        int dy = event->position().y() - lastMousePosition.y();

        ui->frame->resize(ui->frame->width() + dx, ui->frame->height() + dy);
        lastMousePosition = event->pos();
    }

    if (squareIsResizing)
    {
        QPoint currentPos = event->pos();

        QRect frameGeometry = ui->frame->geometry();

        int newX = currentPos.x();
        int newY = currentPos.y();

        if (newX > frameGeometry.right()) {
            newX = frameGeometry.right();
        }

        if (newY > frameGeometry.bottom()) {
            newY = frameGeometry.bottom();
        }

        if (newX < frameGeometry.left()) {
            newX = frameGeometry.left();
        }

        if (newY < frameGeometry.top()) {
            newY = frameGeometry.top();
        }

        square.setBottomRight(QPoint(newX, newY));
        storage.squareSelect(square);
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isResizing = false;
    if (squareIsResizing)
    {
        squareIsResizing = false;
        update();
    }
}


