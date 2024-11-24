#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <Qstack.h>

class QTApplication : public QMainWindow
{
    Q_OBJECT
private:
    Ui_QTApplication *ui;
    QPushButton *numberButton[13];
    QString expression;
    QStack<int> stack;


public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:
    enum method
    {
        Addition = 11,
        Subtraction,
        Multiplication,
        Division,
        Backspace,
        EqualButton,
        Clear,
        Point,
        Negative
    };

private slots:
    void onClicked(int);
};