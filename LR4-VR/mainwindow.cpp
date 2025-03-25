#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->circle, &QAction::triggered, this, &MainWindow::setCircle);
    connect(ui->square, &QAction::triggered, this, &MainWindow::setSqaure);
    connect(ui->ellipse, &QAction::triggered, this, &MainWindow::setEllipse);
    connect(ui->triangle, &QAction::triggered, this, &MainWindow::setTriangle);
    connect(ui->rectangle, &QAction::triggered, this, &MainWindow::setRectangle);
    connect(ui->chooseColor, &QAction::triggered, this, &MainWindow::openColorDialog);
}

int counter = 0;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setClipRect(ui->frame->geometry());
    painter.setPen(QPen(Qt::white));
    storage.drawFigures(painter);
    storage.drawSelectedFigures(painter);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){

        QRect frameGeom = ui->frame->geometry();
        QPoint PosInFrame = event->pos() - frameGeom.topLeft();
        MousePosCirclePress = event->pos();
        lastMousePos = event->pos();

        for (Figure* Figure: storage.GetFigures()){
            if (Figure->contains(event->pos().x(), event->pos().y())){
                figuresInPoint.push_back(Figure);
            }
        }

        int corner = 10;

        bool topLeft = (abs(PosInFrame.x()) < corner && abs(PosInFrame.y()) < corner);
        bool topRight = (abs(PosInFrame.x()-frameGeom.width()) < corner && abs(PosInFrame.y()) < corner);
        bool bottomLeft = (abs(PosInFrame.x()) < corner && abs(PosInFrame.y() - frameGeom.height()) < corner);
        bool bottomRight = (abs(PosInFrame.x()-frameGeom.width()) < corner && abs(PosInFrame.y() - frameGeom.height()) < corner);


        if (topLeft || topRight || bottomLeft || bottomRight) {
            isResizing = true;
            lastMousePos = event->pos();
            return;
        }


        if (figuresInPoint.size()!=0)
        {
            for (Figure* shapeInPoint: figuresInPoint){
                for (Figure* selected_Figure: storage.GetSelectedFigures()){
                    if (shapeInPoint == selected_Figure){
                        if (shapeInPoint->isOnEdge(event->pos().x(), event->pos().y())){
                            isResizingShape = true;
                            return;
                        }
                        else{
                            isMoving = true;
                            return;
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if (isResizingShape){
        storage.resizeShape(event->pos().x(), event->pos().y(), lastMousePos, ui->frame->geometry());
        lastMousePos = event->pos();
        update();
    }

    if (isMoving) {
        storage.moveShape(event->pos().x(), event->pos().y(), lastMousePos, ui->frame->geometry());
        lastMousePos = event->pos();
        update();
    }

    if (isResizing){

        int dx = event->pos().x() - lastMousePos.x();
        int dy = event->pos().y() - lastMousePos.y();

        int newWidth = qMax(100, ui->frame->width() + dx);
        int newHeight = qMax(80, ui->frame->height() + dy);

        QRect newFrameRect = ui->frame->geometry();
        newFrameRect.setWidth(newWidth);
        newFrameRect.setHeight(newHeight);

        bool intersects = false;
        for (Figure* Figure : storage.GetFigures()) {
            if (Figure->intersectsWithFrame(newFrameRect)) {
                intersects = true;
                break;
            }
        }

        if (!intersects) {
            ui->frame->resize(newWidth, newHeight);
            lastMousePos = event->pos();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMoving = false;
    isResizingShape = false;
    isResizing = false;
    update();

    QRect frameGeom = ui->frame->geometry();
    QPoint PosInFrame = event->pos() - frameGeom.topLeft();

    int corner = 10;

    bool topLeft = (abs(PosInFrame.x()) < corner && abs(PosInFrame.y()) < corner);
    bool topRight = (abs(PosInFrame.x()-frameGeom.width()) < corner && abs(PosInFrame.y()) < corner);
    bool bottomLeft = (abs(PosInFrame.x()) < corner && abs(PosInFrame.y() - frameGeom.height()) < corner);
    bool bottomRight = (abs(PosInFrame.x()-frameGeom.width()) < corner && abs(PosInFrame.y() - frameGeom.height()) < corner);


    if (topLeft || topRight || bottomLeft || bottomRight) {
        return;
    }
    if (MousePosCirclePress == event->pos()){
        if (ui->frame->geometry().contains(event->pos())) {
            if (figuresInPoint.size()!=0){
                storage.selectFigures(figuresInPoint, ctrl);
            }
            else{
                if (selected_Figure == "Circle"){
                    storage.AddObject(new Circle(event->pos().x(), event->pos().y(), selectedColor, frameGeom));
                }
                else if (selected_Figure == "Ellipse"){
                    storage.AddObject(new Ellipse(event->pos().x(), event->pos().y(), selectedColor, frameGeom));
                }
                else if (selected_Figure == "Rectangle"){
                    storage.AddObject(new Rectangle(event->pos().x(), event->pos().y(), selectedColor, frameGeom));
                }
                else if (selected_Figure == "Triangle"){
                    storage.AddObject(new Triangle(event->pos().x(), event->pos().y(), selectedColor, frameGeom));
                }
                else if (selected_Figure == "Square"){
                    storage.AddObject(new Square(event->pos().x(), event->pos().y(), selectedColor, frameGeom));
                }
            }
            update();
        }
    }
    figuresInPoint.clear();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        storage.deleteFigures();
        update();
    }

    if (event->key() == Qt::Key_Control){
        ctrl = true;
    }



    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control){
        ctrl = false;
    }
}

void MainWindow::openColorDialog()
{
    QColor color = QColorDialog::getColor(selectedColor, this);
    if (color.isValid()) {
        selectedColor = color;
        storage.setColor(color);
    }
}

void MainWindow::setCircle(){
    selected_Figure = "Circle";
}

void MainWindow::setSqaure(){
    selected_Figure = "Square";
}

void MainWindow::setEllipse(){
    selected_Figure = "Ellipse";
}

void MainWindow::setRectangle(){
    selected_Figure = "Rectangle";
}

void MainWindow::setTriangle(){
    selected_Figure = "Triangle";
}

Circle::Circle(int ValueX, int ValueY, QColor color, QRect frameGeom): Figure(ValueX, ValueY, color){
    if (x - rad < frameGeom.x()) x = rad+frameGeom.x();
    if (y - rad < frameGeom.y()) y = rad+frameGeom.y();
    if (x + rad > frameGeom.width()+frameGeom.x()) x = frameGeom.x() + frameGeom.width() - rad;
    if (y + rad > frameGeom.height()+frameGeom.y()) y = frameGeom.y() + frameGeom.height() - rad;
}

void Circle::draw(QPainter &painter)
{
    painter.setBrush(color);
    painter.drawEllipse(x - rad, y - rad, 2 * rad, 2 * rad);
}

bool Circle::contains(int px, int py)
{
    int dx = x - px;
    int dy = y - py;
    return (dx * dx + dy * dy) <= (rad * rad);
}

void Circle::drawSelected(QPainter &painter)
{
    Figure::drawSelected(painter);
    painter.setBrush(color);
    painter.drawEllipse(x - rad, y - rad, 2 * rad, 2 * rad);
}


bool Circle::isOnEdge(int px, int py){
    int distance = std::hypot(px - x, py - y);
    if (abs(distance - rad) < 5){
        qDebug() << "Edge";
        return true;
    }
    else {
        return false;
    }
}

void Circle::resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom){
    int dx = mouseX - lastMousePos.x();
    int dy = mouseY - lastMousePos.y();
    rad += dx;
    rad += dy;
    if (rad < 15) rad = 15;

    QRect rectbox = getRect();
    if (!frameGeom.contains(rectbox)) {
        rad += -dx;
        rad += -dy;
    }

}

QRect Circle::getRect()
{
    return QRect(x-rad, y - rad, rad*2, rad*2);
}

void MyStorage::AddObject(Figure *Figure)
{
    Figures.push_back(Figure);
    selected_Figures.clear();
}

void MyStorage::drawFigures(QPainter &painter)
{
    for (Figure* Figure: Figures){
        Figure->draw(painter);
    }
}

void MyStorage::selectFigures(vector <Figure*> figuresInPoint, bool ctrl)
{
    if (!ctrl)
    {
        if (selected_Figures == figuresInPoint){
            selected_Figures.clear();
        }
        else {
            selected_Figures = figuresInPoint;
        }
    }
    else {
        for (Figure* shapeInPoint: figuresInPoint){
            if (find(selected_Figures.begin(), selected_Figures.end(), shapeInPoint) == selected_Figures.end()){
                selected_Figures.push_back(shapeInPoint);
            }
            else {
                selected_Figures.erase(remove(selected_Figures.begin(), selected_Figures.end(), shapeInPoint), selected_Figures.end());
            }
        }
    }
}


void MyStorage::drawSelectedFigures(QPainter &painter)
{
    for (Figure* Figure: selected_Figures){
        Figure->drawSelected(painter);
    }
}


void MyStorage::deleteFigures()
{
    for (Figure* selected_Figure: selected_Figures){
        Figures.erase(remove(Figures.begin(), Figures.end(), selected_Figure), Figures.end());
    }
    selected_Figures.clear();
}

void MyStorage::setColor(QColor color)
{
    for (Figure * selected_Figure: selected_Figures)
    {
        selected_Figure->setColor(color);
    }
}

vector<Figure*> MyStorage::GetSelectedFigures(){
    return selected_Figures;
}

vector<Figure *> MyStorage::GetFigures(){
    return Figures;
}

void MyStorage::moveShape(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom)
{
    for (Figure* selected_Figure: selected_Figures)
    {
        selected_Figure->move(mouseX, mouseY, lastMousePos, frameGeom);
    }
}

void MyStorage::resizeShape(int x, int y, QPoint lastMousePos, QRect frameGeom){
    for (Figure* selected_Figure: selected_Figures){
        selected_Figure->resize(x, y, lastMousePos, frameGeom);
    }
}

Rectangle::Rectangle(int ValueX, int ValueY, QColor color, QRect frameGeom): Figure(ValueX, ValueY, color), width(60), height(40){
    if (x < frameGeom.x()) x = frameGeom.x();
    if (y < frameGeom.y()) y = frameGeom.y();
    if (x + width > frameGeom.x()+frameGeom.width()) x = frameGeom.x() + frameGeom.width() - width;
    if (y + height > frameGeom.y()+frameGeom.height()) y =frameGeom.y() + frameGeom.height() - height;
}

void Rectangle::draw(QPainter &painter) {
    painter.setBrush(color);
    painter.drawRect(x, y, width, height);
}

bool Rectangle::contains(int px, int py) {
    return (px >= x && px <= x + width && py >= y && py <= y + height);
}

void Rectangle::drawSelected(QPainter &painter)
{
    Figure::drawSelected(painter);
    painter.setBrush(color);
    painter.drawRect(x, y, width, height);
}

bool Rectangle::isOnEdge(int px, int py){
    int edgeThreshold = 5;
    bool left = abs(px - x) < edgeThreshold;
    bool right = abs(px - (x + width)) < edgeThreshold;
    bool top = abs(py - y) < edgeThreshold;
    bool bottom = abs(py - (y + height)) < edgeThreshold;
    return left || right || top || bottom;
}

void Rectangle::resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) {
    int dx = mouseX - lastMousePos.x();
    int dy = mouseY - lastMousePos.y();
    width += dx;
    height += dy;
    width = max(60, width);
    height = max(40, height);

    QRect rectbox = getRect();

    if (!frameGeom.contains(rectbox)) {
        width += -dx;
        height += -dy;
    }

}

QRect Rectangle::getRect()
{
    return QRect(x, y, width, height);
}

Ellipse::Ellipse(int ValueX, int ValueY, QColor color, QRect frameGeom) : Figure(ValueX, ValueY, color), widthR(30), heightR(20){

    if (x - widthR < frameGeom.x()) x = frameGeom.x() + widthR;
    if (y - heightR < frameGeom.y()) y = frameGeom.y() + heightR;
    if (x + widthR > frameGeom.x() + frameGeom.width()) x = frameGeom.x() + frameGeom.width() - widthR;
    if (y + heightR > frameGeom.y() + frameGeom.height()) y = frameGeom.y() + frameGeom.height() - heightR;

}



void Ellipse::draw(QPainter &painter) {
    painter.setBrush(color);
    painter.drawEllipse(QPoint(x, y), widthR, heightR);
}

bool Ellipse::contains(int px, int py) {
    double dx = px - x;
    double dy = py - y;

    double a = widthR;
    double b = heightR;

    return (dx * dx) / (a * a) + (dy * dy) / (b * b) <= 1.0;
}

void Ellipse::drawSelected(QPainter &painter)
{
    Figure::drawSelected(painter);
    painter.setBrush(color);
    painter.drawEllipse(QPoint(x, y), widthR, heightR);
}

bool Ellipse::isOnEdge(int px, int py) {
    double centerX = x;
    double centerY = y;

    double normX = (px - centerX) / (widthR);
    double normY = (py - centerY) / (heightR);

    double equation = normX * normX + normY * normY;
    return fabs(equation - 1.0) < 0.3;
}

void Ellipse::resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) {
    int dx = mouseX - lastMousePos.x();
    int dy = mouseY - lastMousePos.y();

    widthR += dx;
    heightR += dy;

    widthR = std::max(30, widthR);
    heightR = std::max(20, heightR);

    QRect rectbox = getRect();

    if (!frameGeom.contains(rectbox)) {
        widthR += -dx;
        heightR += -dy;
    }

}

QRect Ellipse::getRect()
{
    return QRect(x, y, widthR*2, heightR*2);
}

Triangle::Triangle(int ValueX, int ValueY, QColor color, QRect frameGeom): Figure(ValueX, ValueY, color), size(30){
    if (x - size < frameGeom.x()) x = size+frameGeom.x();
    if (y - size < frameGeom.y()) y = size+frameGeom.y();
    if (x + size > frameGeom.width()+frameGeom.x()) x = frameGeom.x() + frameGeom.width() - size;
    if (y + size > frameGeom.height()+frameGeom.y()) y = frameGeom.y() + frameGeom.height() - size;
}

void Triangle::draw(QPainter &painter) {
    painter.setBrush(color);
    QPolygon polygon;
    polygon << QPoint(x, y - size)
            << QPoint(x - size, y + size)
            << QPoint(x + size, y + size);
    painter.drawPolygon(polygon);
}

bool Triangle::contains(int px, int py) {
    QPoint A(x, y - size);
    QPoint B(x - size, y + size);
    QPoint C(x + size, y + size);
    QPoint P(px, py);

    auto area = [](QPoint p1, QPoint p2, QPoint p3) {
        return abs((p1.x() * (p2.y() - p3.y()) +
                    p2.x() * (p3.y() - p1.y()) +
                    p3.x() * (p1.y() - p2.y())) / 2.0);
    };

    double totalArea = area(A, B, C);
    double area1 = area(P, B, C);
    double area2 = area(A, P, C);
    double area3 = area(A, B, P);

    return fabs(totalArea - (area1 + area2 + area3)) < 1e-6;
}

void Triangle::drawSelected(QPainter &painter)
{
    Figure::drawSelected(painter);
    QPolygon polygon;
    polygon << QPoint(x, y - size)
            << QPoint(x - size, y + size)
            << QPoint(x + size, y + size);
    painter.setBrush(color);
    painter.drawPolygon(polygon);
}


bool Triangle::isOnEdge(int px, int py) {
    QPoint A(x, y - size);
    QPoint B(x - size, y + size);
    QPoint C(x + size, y + size);
    QPoint P(px, py);

    auto distance = [](QPoint p1, QPoint p2) {
        return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
    };
    auto pointToLineDistance = [&](QPoint A, QPoint B, QPoint P) {
        double area = abs((B.x() - A.x()) * (A.y() - P.y()) - (A.x() - P.x()) * (B.y() - A.y()));
        double base = distance(A, B);
        return area / base;
    };

    int threshold = 5;
    return (pointToLineDistance(A, B, P) < threshold ||
            pointToLineDistance(B, C, P) < threshold ||
            pointToLineDistance(C, A, P) < threshold);
}

void Triangle::resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) {
    int dx = mouseX - lastMousePos.x();
    int dy = mouseY - lastMousePos.y();

    int delta;
    if (dy < 0 || dx < 0){
        delta = std::min(dx, dy);
    }
    else {
        delta = std::max(dx, dy);
    }

    size += delta;
    size = std::max(30, size);

    QRect rectbox = getRect();

    if (!frameGeom.contains(rectbox)) {
        size += -delta;
    }

}

QRect Triangle::getRect()
{
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(x, y - size)
                    << QPoint(x - size, y + size)
                    << QPoint(x + size, y + size);
    return trianglePolygon.boundingRect();

}

Square::Square(int ValueX, int ValueY, QColor color, QRect frameGeom): Figure(ValueX, ValueY, color), width(40), height(40){
    if (x < frameGeom.x()) x = frameGeom.x();
    if (y < frameGeom.y()) y = frameGeom.y();
    if (x + width > frameGeom.x()+frameGeom.width()) x = frameGeom.x() + frameGeom.width() - width;
    if (y + height > frameGeom.y()+frameGeom.height()) y = frameGeom.y() + frameGeom.height() - height;
}

void Square::draw(QPainter &painter) {
    painter.setBrush(color);
    painter.drawRect(x, y, width, height);
}

bool Square::contains(int px, int py) {
    return (px >= x && px <= x + width && py >= y && py <= y + height);
}

void Square::drawSelected(QPainter &painter)
{
    Figure::drawSelected(painter);
    painter.setBrush(color);
    painter.drawRect(x, y, width, height);
}

bool Square::isOnEdge(int px, int py){
    int edgeThreshold = 5;
    bool left = abs(px - x) < edgeThreshold;
    bool right = abs(px - (x + width)) < edgeThreshold;
    bool top = abs(py - y) < edgeThreshold;
    bool bottom = abs(py - (y + height)) < edgeThreshold;
    return left || right || top || bottom;
}

void Square::resize(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom) {
    int dx = mouseX - lastMousePos.x();
    int dy = mouseY - lastMousePos.y();

    int delta;

    if (dy < 0 || dx < 0){
        delta = min(dx, dy);
    }
    else {
        delta = max(dx, dy);
    }

    width += delta;
    height += delta;

    int minSizeSquare = 40;
    width = max(minSizeSquare, width);
    height = max(minSizeSquare, height);

    QRect rectbox = getRect();

    if (!frameGeom.contains(rectbox)) {
        width += -delta;
        height += -delta;
    }
}

QRect Square::getRect()
{
    return QRect(x, y, width, height);

}

void Figure::drawSelected(QPainter &painter)
{
    QPen pen(Qt::DashLine);
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
}

void Figure::setColor(QColor color)
{
    this->color = color;
}

bool Figure::intersectsWithFrame(const QRect frameRect)
{
    QRect rectbox = getRect();
    return (!frameRect.contains(rectbox));
}

void Figure::move(int mouseX, int mouseY, QPoint lastMousePos, QRect frameGeom)
{
    int dx = (mouseX - lastMousePos.x());
    int dy = (mouseY - lastMousePos.y());

    QRect rectbox = getRect();

    QRect newrectbox = rectbox.translated(dx, dy);
    if (frameGeom.contains(newrectbox))
    {
        x += dx;
        y += dy;
    }
}


