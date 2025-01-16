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


public:
    explicit QTApplication(QWidget *parent = nullptr);
    ~QTApplication();

private:

private slots:
    void onClicked(const QString &text);
};