#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>
#include <QProcess>

class QTApplication : public QMainWindow
{
    Q_OBJECT

public:
    QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:
    Ui_QTApplication *ui;

private slots:
    void on_commitButton_clicked();
};