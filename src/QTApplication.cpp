#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    this->setWindowIcon(QIcon("../static/calculator.ico"));
    this->setWindowTitle("计算器");
    this->setMinimumSize(320, 500);

    ui->setupUi(this);
    // setFont
    ui->mainLineEdit->setFont(QFont("仿宋", 26));
    // setButtonColor
    ui->equalButton->setStyleSheet("background:#65A5D1");
    ui->mainLineEdit->setText("0");

    QSignalMapper *mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mappedString(const QString &)), this, SLOT(doClicked(const QString &)));
    for (int i = 0; i < 3; i++)
    {
        numberButton[i] = new QPushButton("Button" + QString::number(i), this);
        numberButton[i]->setMinimumSize(60, 75);
        numberButton[i]->setText(QString::number(i));

        ui->gridLayout->addWidget(numberButton[i], 2, i);
        mapper->setMapping(numberButton[i], QString::number(i));
        connect(numberButton[i], SIGNAL(clicked()), mapper, SLOT(map()));
    }
}

QTApplication::~QTApplication()
{
    delete ui;
}

void QTApplication::doClicked(const QString &text)
{
    if (ui->mainLineEdit->text().toInt() != 0)
    {
        expression += text;
    }
    else
    {
    }
    ui->mainLineEdit->setText(expression);
}