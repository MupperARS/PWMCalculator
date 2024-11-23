#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QSignalMapper>

class QTApplication : public QMainWindow
{
    Q_OBJECT
private:
    Ui_QTApplication *ui;
    QPushButton *numberButton[13];
    QString expression;
    double result;
    int decimal = 1;
    int methood = 0;
    int methoodCount = 0;

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:
    double combine(double Compute, int dec);

private slots:
    void ctrlClicked(int);
    void numberClicked(const QString &);
};