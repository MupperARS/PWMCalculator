#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    QFont f("仿宋", 26);
    QIcon icon("../static/calculator.ico");

    ui->setupUi(this);

    this->setWindowTitle("计算器");
    this->setMinimumSize(320, 500);

    ui->mainLineEdit->setFont(f);

    
    this->setWindowIcon(icon);
}

QTApplication::~QTApplication()
{
    delete ui;
}

void QTApplication::on_oneButton_clicked()
{
    expression += "1";
    ui->mainLineEdit->setText(expression);
}