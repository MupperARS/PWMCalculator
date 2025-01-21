#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QPushButton>
#include <QClipboard>

class QTApplication : public QMainWindow
{
    Q_OBJECT
private:
    Ui_QTApplication *ui;
    QLabel *label[5];
    QLineEdit *lineEdit[3];
    QComboBox *comboBox;
    QSlider *slider;
    QClipboard *clip;
    uint16_t core = 0U;          //核心数
    uint16_t PWM = 0U;           //pwm
    uint16_t resetCount = 0U;    //计数
    uint16_t Prescaler = 0U;     //预分频系数
    uint16_t pulse = 0U;         //

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

    void calculator();
private:

private slots:
    void onChange(int vlaue);
    void onComboChange(const QString &text);
    void changed(int vlaue);
    void copy();
};