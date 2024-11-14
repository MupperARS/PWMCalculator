#pragma once
#include "ui_QTApplication.h"
#include <QMainWindow>

class QTApplication : public QMainWindow {
    Q_OBJECT
    
public:
    QTApplication(QWidget* parent = nullptr);
    ~QTApplication();

private:
    Ui_QTApplication* ui;
};