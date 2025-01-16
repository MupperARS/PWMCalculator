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
    QStack<QString> stack;


public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:
    QString calculate();

private slots:
    void onClicked(const QString &text);
};