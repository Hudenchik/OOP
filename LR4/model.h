#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSettings>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

    // Геттеры
    int getA() const;
    int getB() const;
    int getC() const;

public slots:
    // Сеттеры
    void setA(int value);
    void setB(int value);
    void setC(int value);

signals:
    void aChanged(int value);
    void bChanged(int value);
    void cChanged(int value);

private:
    int a, b, c;

    void save();
    void load();
};

#endif // MODEL_H
