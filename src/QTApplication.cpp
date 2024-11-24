#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    int count = 0;
    QString buttonName[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "±", "0", "."};
    int value[] = {7, 8, 9, 4, 5, 6, 1, 2, 3, Point, 0, Negative};
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

    mapper->setMapping(ui->Addition, Addition);
    mapper->setMapping(ui->Subtraction, Subtraction);
    mapper->setMapping(ui->Multiplication, Multiplication);
    mapper->setMapping(ui->Division, Division);
    mapper->setMapping(ui->Backspace, Backspace);
    mapper->setMapping(ui->EqualButton, EqualButton);
    mapper->setMapping(ui->Clear, Clear);

    connect(ui->Addition, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Subtraction, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Multiplication, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Division, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Backspace, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->EqualButton, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Clear, SIGNAL(clicked()), mapper, SLOT(map()));

    for (int i = 1; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            numberButton[count] = new QPushButton("Button" + QString::number(i), this);
            numberButton[count]->setMinimumSize(75, 75);
            numberButton[count]->setMaximumSize(75, 75);
            numberButton[count]->setText(buttonName[count]);

            ui->gridLayout->addWidget(numberButton[count], i, j);
            mapper->setMapping(numberButton[count], value[count]);
            connect(numberButton[count], SIGNAL(clicked()), mapper, SLOT(map()));
            count++;
        }
    }
    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(onClicked(int)));
}

QTApplication::~QTApplication()
{
    delete ui;
}

/**
 * 点击事件 槽函数
 * @param value 枚举或数字
 */
void QTApplication::onClicked(int value)
{
    bool zero = ui->mainLineEdit->text().at(0).digitValue();
    /**
     * 判断数字框不为零
     * 受控功能
     */
    if (zero)
    {
        switch (value)
        {
        case Addition:
            /*加法*/
            expression.append("+"); //=
            break;
        case Subtraction:
            /* 减法 */
            expression.append("-"); //+
            break;
        case Multiplication:
            /* 乘法 */
            expression.append("x"); //-
            break;
        case Division:
            /* 除法 */
            expression.append("÷"); // x
            break;
        case EqualButton:
            /* 等于 */
            expression.append("="); // x
            break;
        }
        stack.push(value);
    }

    /**
     * 非受控功能
     */
    switch (value)
    {
    case Point:
        /* 点 */
        expression.append("."); // x
        break;
    case Negative:
        /* 正负号 */
        expression.append("±"); // x
        break;
    case Clear:
        /* 清除 */
        expression = "0";
    case Backspace:
        /* 退格 */
        
        break;
    }

    /* 判断数字框为零 */
    if (!zero)
    {
        stack.push(value);
        expression = QString::number(value); // 将数字转字符赋值到expression上
    }
    expression.append(QString::number(value)); // 将数字转字符添加到expression字符串尾

    ui->mainLineEdit->setText(expression); // 将expresssion写回到编辑组件中
}
