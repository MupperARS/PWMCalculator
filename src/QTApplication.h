#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QException>
#include <QProcess>

class QTApplication : public QMainWindow, QException
{
    Q_OBJECT

public:
    QTApplication(QWidget *parent = nullptr);
    ~QTApplication();
    

private:
    Ui_QTApplication *ui;

private slots:
};