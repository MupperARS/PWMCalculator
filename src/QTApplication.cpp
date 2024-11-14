#include "QTApplication.h"
#include <QDesktopServices>
#include <iostream>

QTApplication::QTApplication(QWidget* parent) 
    : QMainWindow(parent)
    , ui(new Ui_QTApplication)
{
    setFixedSize(800, 600);
    std::cout << "hello word"<< std::endl;
}

QTApplication::~QTApplication()
{
    delete ui; 
}