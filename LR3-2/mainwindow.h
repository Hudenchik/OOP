#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Model: public QObject
{
    Q_OBJECT

private:
    int a;
    int b;
    int c;

public:

    int getA();
    void setA(int value);

    int getB();
    void setB(int value);

    int getC();
    void setC(int value);

    void saveSettings();
    void loadSettings();

    ~Model()
    {
        saveSettings();
    }

signals:
    void valueChanged();

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFromModel();

    void on_lineEditA_returnPressed();

    void on_spinBoxA_valueChanged(int arg1);

    void on_sliderA_sliderReleased();

    void on_lineEditB_returnPressed();

    void on_spinBoxB_valueChanged(int arg1);

    void on_sliderB_sliderReleased();

    void on_lineEditC_returnPressed();

    void on_spinBoxC_valueChanged(int arg1);

    void on_sliderC_sliderReleased();

    void on_lineEditA_editingFinished();

    void on_lineEditB_editingFinished();

    void on_lineEditC_editingFinished();

    void on_spinBoxA_editingFinished();

private:
    Ui::MainWindow *ui;
    Model *model = new Model();
};


#endif // MAINWINDOW_H
