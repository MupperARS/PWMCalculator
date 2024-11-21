#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <iostream>
#include <QSignalMapper>

class QTApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:
    Ui_QTApplication *ui;
    QString expression;
    QPushButton *numberButton[9];

private slots:
    void doClicked(const QString &text);
};