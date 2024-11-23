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

    mapper->setMapping(ui->EqualButton, 10);
    mapper->setMapping(ui->Addition, 11);
    mapper->setMapping(ui->Subtraction, 12);
    mapper->setMapping(ui->Multiplication, 13);
    mapper->setMapping(ui->Division, 14);
    mapper->setMapping(ui->Backspace, 15);
    mapper->setMapping(ui->Clear, 16);

    connect(ui->EqualButton, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Addition, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Subtraction, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Multiplication, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Division, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(ui->Backspace, SIGNAL(clicked()), mapper, SLOT(map()));
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
            mapper->setMapping(numberButton[count], buttonName[count]);
            connect(numberButton[count], SIGNAL(clicked()), mapper, SLOT(map()));
            count++;
        }
    }
    connect(mapper, SIGNAL(mappedString(const QString &)), this, SLOT(numberClicked(const QString &)));
    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(ctrlClicked(int)));
}

QTApplication::~QTApplication()
{
    delete ui;
}

double QTApplication::combine(double Compute, int dec)
{
    result = Compute;
    decimal = dec;
    return result;
}

void QTApplication::numberClicked(const QString &text)
{
    int id = text.toInt();
    switch (methood)
    {
    case 11:
        decimal = 1;
        combine(result + id * decimal, decimal * 10);
        break;
    case 12:
        decimal = 1;
        combine(result - id * decimal, decimal * 10);
        break;
    case 13:
        decimal = 1;
        result *= text.toInt(); // x
        break;
    case 14:
        decimal = 1;
        result /= text.toInt(); // ÷
        break;
    default:
        int value = ui->mainLineEdit->text().at(0).digitValue();
        result = value ? combine(id + result * decimal * 10, decimal * 10) : id;
        expression = value ? expression + text : text;
        break;
    }
    if (methood)
    {
        methoodCount--;
        methood = 0;
        expression.append(text);
    }

    ui->mainLineEdit->setText(expression);
}

void QTApplication::ctrlClicked(int value)
{
    if (!expression.back().digitValue())
        return;
    methood = value;
    methoodCount++;
    switch (value)
    {
    case 10:
        expression.append("=" + QString::number(result)); //=
        break;
    case 11:
        expression.append("+"); //+
        break;
    case 12:
        expression.append("-"); //-
        break;
    case 13:
        expression.append("x"); // x
        break;
    case 14:
        expression.append("÷"); // ÷
        break;
    case 15:
        // Backspace
        if (expression.length() > 1)
        {
            expression = expression.chopped(1);
            break;
        }
        result = 0;
        methood = 0;
        expression = "0";
        break;
    case 16:
        result = 0;
        methood = 0;
        decimal = 1;
        expression = "0";
        break;
    }

    ui->mainLineEdit->setText(expression);
}