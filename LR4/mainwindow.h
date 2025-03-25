#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Figure{
protected:
    int x, y;
    QColor color;
public:
    Figure(int x, int y, QColor color): x(x), y(y), color(color){};
    virtual void draw(QPainter &painter) = 0;
    virtual void drawSelected(QPainter &painter);
    virtual void move(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom);
    virtual bool contains(int px, int py) = 0;
    void setColor(QColor color);
    virtual void resize(int mouseX, int mouseY, QPoint lastMousePoint, QRect frameGeom) = 0;
    virtual bool isOnEdge(int px, int py) = 0;
    virtual bool intersectsWithFrame(const QRect frameRect);
    virtual QRect getRect() = 0;
};

class Circle: public Figure{
private:
    int rad = 20;

public:
    Circle(int ValueX, int ValueY, QColor color, QRect frameGeom);
    void draw(QPainter &painter) override;
    bool contains(int px, int py) override;
    void drawSelected(QPainter &painter) override;
    bool isOnEdge(int px, int py) override;
    void resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) override;
    QRect getRect() override;
};

class Rectangle: public Figure {
private:
    int width, height;
public:
    Rectangle(int ValueX, int ValueY, QColor color, QRect frameGeom);
    void draw(QPainter &painter) override;
    bool contains(int px, int py) override;
    void drawSelected(QPainter &painter) override;
    bool isOnEdge(int px, int py) override;
    void resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) override;
    QRect getRect() override;

};
class Ellipse : public Figure {
private:
    int widthR, heightR;

public:
    Ellipse(int ValueX, int ValueY, QColor color, QRect frameGeom);
    void draw(QPainter &painter) override;
    bool contains(int px, int py) override;
    void drawSelected(QPainter &painter) override;
    bool isOnEdge(int px, int py) override;
    void resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) override;
    QRect getRect() override;
};

class Triangle: public Figure {
private:
    int size;
public:
    Triangle(int ValueX, int ValueY, QColor color, QRect frameGeom);
    void draw(QPainter &painter) override;

    bool contains(int px, int py) override;
    void drawSelected(QPainter &painter) override;

    bool isOnEdge(int px, int py) override;

    void resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) override;
    QRect getRect() override;
};

class Square: public Figure {
private:
    int width, height;
public:
    Square(int ValueX, int ValueY, QColor color, QRect frameGeom);
    void draw(QPainter &painter) override;

    bool contains(int px, int py) override;

    void drawSelected(QPainter &painter) override;
    bool isOnEdge(int px, int py) override;

    void resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) override;
    QRect getRect() override;

};

class MyStorage{
private:
    vector<Figure*> Figures;
    vector<Figure*> selected_Figures;
public:

    void AddObject(Figure *Figure);

    void drawFigures(QPainter &painter);

    void selectFigures(vector <Figure*> figuresInPoint, bool ctrl);

    void drawSelectedFigures(QPainter &painter);

    void deleteFigures();

    void setColor(QColor color);

    vector <Figure*> GetSelectedFigures();

    vector <Figure*> GetFigures();

    void moveShape(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom);

    void resizeShape(int x, int y, QPoint lastMousePos, QRect frameGeom);


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
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void openColorDialog();
    void setCircle();
    void setSqaure();
    void setEllipse();
    void setRectangle();
    void setTriangle();

private:
    Ui::MainWindow *ui;
    MyStorage storage;
    QPoint lastMousePos;
    QColor selectedColor = Qt::green;
    QPoint MousePosCirclePress;
    string selected_Figure = "Circle";
    bool isMoving = false;
    bool isResizing = false;
    bool ctrl = false;
    bool isResizingShape = false;
    vector <Figure*> figuresInPoint;
};

#endif // MAINWINDOW_H
