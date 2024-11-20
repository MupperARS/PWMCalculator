#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    QFont f("仿宋", 26);
    QIcon icon("../static/calculator.ico");
    QString buttonColor("");

    ui->setupUi(this);

    this->setWindowIcon(icon);
    this->setWindowTitle("计算器");
    this->setMinimumSize(320, 500);

    //setFont
    ui->mainLineEdit->setFont(f);
    //setButtonColor
    ui->equalButton->setStyleSheet("background:#65A5D1");
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