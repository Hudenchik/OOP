#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class CCircle{
private:
    int x, y;
    const int rad = 40;

public:
    CCircle(int ValueX, int ValueY):x(ValueX), y(ValueY){}
    void draw(QPainter &painter, QRect restriction);
    bool contains(int px, int py);

};


class MyStorage{
private:
    vector<CCircle*> circles;
    vector<CCircle*> selectedCircles;
public:

    void AddObject(int x, int y);

    void drawCircles(QPainter &painter, QRect restriction);

    ~MyStorage(){
        for (size_t i = 0; i<circles.size();i++){
            delete circles[i];
        }
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    MyStorage storage;
    bool isResizing = false;
    QPoint lastMousePosition;
};


#endif // MAINWINDOW_H
