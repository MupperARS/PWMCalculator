#include "QTApplication.h"
#include <QApplication>
#include <QPushButton>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    ui->setupUi(this);
}

QTApplication::~QTApplication()
{
    delete ui;
}