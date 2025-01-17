#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

class QTApplication : public QMainWindow
{
    Q_OBJECT
private:
    Ui_QTApplication *ui;
    QLabel *label[4];
    QLineEdit *lineEdit[4];
    uint16_t core;
    uint16_t PWM;
    uint16_t resetCount;
    uint16_t pulse;

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:

private slots:
    void onChange(int vlaue);
};