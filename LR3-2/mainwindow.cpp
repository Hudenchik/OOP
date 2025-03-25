#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model->loadSettings();

    connect(model, &Model::valueChanged, this, &MainWindow::updateFromModel);

    updateFromModel();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void Model::saveSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("a", a);
    settings.setValue("b", b);
    settings.setValue("c", c);
}

void Model::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    int savedA = settings.value("a", 0).toInt();
    int savedB = settings.value("b", 0).toInt();
    int savedC = settings.value("c", 100).toInt();

    int newA = qBound(0, savedA, 100);
    int newC = qBound(0, savedC, 100);

    if (newA > newC)
    {
        newC = newA;
    }

    setA(newA);
    setC(newC);
    setB(savedB);
}

void MainWindow::updateFromModel()
{
    ui->lineEditA->setText(QString::number(model->getA()));
    ui->spinBoxA->setValue(model->getA());
    ui->sliderA->setValue(model->getA());

    ui->lineEditB->setText(QString::number(model->getB()));
    ui->spinBoxB->setValue(model->getB());
    ui->sliderB->setValue(model->getB());

    ui->lineEditC->setText(QString::number(model->getC()));
    ui->spinBoxC->setValue(model->getC());
    ui->sliderC->setValue(model->getC());

}

int Model::getA()
{
    return a;
}

int Model::getB()
{
    return b;
}

int Model::getC()
{
    return c;
}
void Model::setA(int value)
{
    int newA = qBound(0, value, 100);
    a = newA;
    if (a > c)
    {
        c = a;
    }
    if (a>b)
    {
        b = a;
    }
    saveSettings();
    emit valueChanged();
}

void Model::setB(int value)
{
    if ((a<=value && value<=c))
    {
        b = value;
        saveSettings();
    }
    emit valueChanged();
}

void Model::setC(int value)
{
    int newC = qBound(0, value, 100);
    c = newC;
    if (c < a)
    {
        a = c;
    }
    if (b>c)
    {
        b = c;
    }
    saveSettings();
    emit valueChanged();
}

void MainWindow::on_lineEditA_returnPressed()
{
    model->setA(ui->lineEditA->text().toInt());
}


void MainWindow::on_spinBoxA_valueChanged(int arg1)
{
    model->setA(arg1);
}

void MainWindow::on_sliderA_sliderReleased()
{
    model->setA(ui->sliderA->value());
}


void MainWindow::on_lineEditB_returnPressed()
{
    model->setB(ui->lineEditB->text().toInt());
}

void MainWindow::on_spinBoxB_valueChanged(int arg1)
{
    model->setB(arg1);
}

void MainWindow::on_sliderB_sliderReleased()
{
    model->setB(ui->sliderB->value());
}

void MainWindow::on_lineEditC_returnPressed()
{
    model->setC(ui->lineEditC->text().toInt());
}

void MainWindow::on_spinBoxC_valueChanged(int arg1)
{
    model->setC(arg1);
}

void MainWindow::on_sliderC_sliderReleased()
{
    model->setC(ui->sliderC->value());
}


void MainWindow::on_lineEditA_editingFinished()
{
    ui->lineEditA->setText(QString::number(model->getA()));
}

void MainWindow::on_lineEditB_editingFinished()
{
    ui->lineEditB->setText(QString::number(model->getB()));
}

void MainWindow::on_lineEditC_editingFinished()
{
    ui->lineEditC->setText(QString::number(model->getC()));
}


void MainWindow::on_spinBoxA_editingFinished()
{
    ui->spinBoxA->setValue(model->getA());
}

