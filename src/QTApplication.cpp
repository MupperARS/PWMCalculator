#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    int count = 0;
    QString buttonName[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "±", "0", "."};
    QSignalMapper *mapper = new QSignalMapper(this);

    ui->setupUi(this);
    // setFont
    ui->mainLineEdit->setFont(QFont("仿宋", 26));
    // setButtonColor
    ui->EqualButton->setStyleSheet("background:#65A5D1");
    ui->mainLineEdit->setText(expression = "0");

    this->setWindowIcon(QIcon("../static/calculator.ico"));
    this->setWindowTitle("计算器");
    this->setMinimumSize(320, 500);
}

/**
 * @brief 析构函数
 */
QTApplication::~QTApplication()
{
    delete ui;
}

/**
 * 槽函数
 * @param value 枚举或数字
 */
void QTApplication::onClicked(const QString &text)
{

}
