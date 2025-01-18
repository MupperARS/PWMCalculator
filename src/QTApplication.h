#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

class QTApplication : public QMainWindow
{
    Q_OBJECT
private:
    Ui_QTApplication *ui;
    QLabel *label[4];
    QLineEdit *lineEdit[4];
    QComboBox *comboBox;
    uint16_t core;          //核心数
    uint16_t PWM;           //pwm
    uint16_t resetCount;    //计数
    uint16_t Prescaler;     //预分频系数
    uint16_t pulse;         //

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:

private slots:
    void onChange(int vlaue);
};