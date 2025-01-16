#include "QTApplication.h"
#include <QApplication>

typedef enum
{
	HAL_Drvices_OK = 0x00U,
	HAL_Drvices_ERROR = 0x01U,
    HAL_Drvices_BUSY = 0x02U,
    HAL_Drvices_TIMEOUT = 0x03U,
    HAL_Drvices_OFFLINE = 0x04U
}HAL_DrvicesStatusTypeDef;

HAL_DrvicesStatusTypeDef hello()
{
    return HAL_Drvices_OK;
}

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

    mapper->setMapping(ui->Addition, "+");
    mapper->setMapping(ui->Subtraction, "-");
    mapper->setMapping(ui->Multiplication, "x");
    mapper->setMapping(ui->Division, "÷");
    mapper->setMapping(ui->Backspace, "11");
    mapper->setMapping(ui->EqualButton, "12");
    mapper->setMapping(ui->Clear, "13");

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
            mapper->setMapping(numberButton[count], buttonName[count]);
            connect(numberButton[count], SIGNAL(clicked()), mapper, SLOT(map()));
            count++;
        }
    }
    connect(mapper, SIGNAL(mappedString(const QString &)), this, SLOT(onClicked(const QString &)));
}

QTApplication::~QTApplication()
{
    delete ui;
}

/**
 * 栈计算
 * 1 + 2 * 3 + 1 = 1 2 3 * +
 */
QString QTApplication::calculate()
{
    int i = 0;
    int j = 0;
    int value[] = {0};
    QString node;
    for (i = 0; i < expression.length(); i++)
    {
        /**
         * 入栈操作
         */
        if (expression[i].digitValue() != EOF) // 负一为假
        {
            /**
             * 如果为数字直接输出
             */
            node.append(expression[i]);
        }
        else
            /**
             * 如果为字符压栈
             */
            stack.push(expression[i]);
    }

    while (!stack.isEmpty())
    {
        node.append(stack.pop());
    }

    /**
     * 对字符串压栈
     * 遍历字符串判断有无计算字符
     */
    for (i = 0; i < node.length(); i++)
    {
        /**
         * 结果栈依次推出字符类型对数字进行计算
         * 双重循环解构字符串->数字
         */
        while (expression[i].digitValue() != EOF)
        {
            j++;
            i++;
        }
        stack.push(expression.mid(i, j));
    }

    // if (expression[i] == "+")
    // {
    //     for (i = 0; i < 2; i++)
    //     {
    //         qDebug() << stack.top();
    //         value[i] = stack.pop().toInt();
    //     }
    //     stack.push(QString::number(value[0]));
    // }
    // if (expression[i] == '-')
    // {
    //     for (i = 0; i < 2; i++)
    //     {
    //         value[i] = stack.pop().toInt();
    //     }
    //     stack.push(QString::number(value[0]));
    // }
    // if (expression[i] == "x")
    // {
    //     for (i = 0; i < 2; i++)
    //     {
    //         value[i] = stack.pop().toInt();
    //     }
    //     stack.push(QString::number(value[0]));
    // }
    // if (expression[i] == "÷")
    // {
    //     for (i = 0; i < 2; i++)
    //     {
    //         value[i] = stack.pop().toInt();
    //     }
    //     stack.push(QString::number(value[0]));
    // }

    return stack.pop();
}

/**
 * 点击事件 槽函数
 * @param value 枚举或数字
 */
void QTApplication::onClicked(const QString &text)
{
    bool zero = expression.at(0).digitValue();
    /**
     * 非受控功能
     * 得提前判断是否为功能
     */
    if (text.toInt() > 10)
    {
        /* code */
        switch (text.toInt())
        {
        case 11:
            /* 退格 */
            expression = expression.length() > 1 ? expression.chopped(1) : "0";
            break;
        case 12:
            /* 等于 */
            expression.append("=" + calculate());
            break;
        case 13:
            /* 清除 */
            expression.clear();
            expression = "0";

            break;
        default:
            break;
        }
        ui->mainLineEdit->setText(expression);
        return;
    }

    /* 判断数字框为零 */
    expression = zero ? expression + text : text; // 将数字转字符赋值到expression上

    ui->mainLineEdit->setText(expression); // 将expresssion写回到编辑框组件中
}
