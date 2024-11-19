#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>

class QTApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();
    

private:
    Ui_QTApplication *ui;
    QString expression;

private slots:
    void on_oneButton_clicked();
};