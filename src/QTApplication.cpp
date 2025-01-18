#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    QSignalMapper *mapper = new QSignalMapper(this);

    ui->setupUi(this);

    this->setWindowIcon(QIcon("../static/calculator.ico"));
    this->setWindowTitle("PWM计算器");
    this->setMinimumSize(320, 500);

    QString name[] = {"核心频率(MHz):", "预分频系数:", "装载值:", "心跳值:"};
    QStringList list = {"TIM_CLOCKDIVISION_DIV1", "TIM_CLOCKDIVISION_DIV2", "TIM_CLOCKDIVISION_DIV4"};

    for (uint16_t i = 0; i < 4; i++)
    {
        label[i] = new QLabel(this);
        lineEdit[i] = new QLineEdit(this);
        label[i]->setText(name[i]);
        label[i]->setMinimumSize(10, 15);
        lineEdit[i]->setMinimumSize(200, 15);
        ui->gridLayout->addWidget(label[i]);
        ui->gridLayout->addWidget(lineEdit[i]);
        if (i == 1)
        {
            comboBox = new QComboBox(this);
            comboBox->addItems(list);
            ui->gridLayout->addWidget(comboBox);
        }
        mapper->setMapping(lineEdit[i], i);
        connect(lineEdit[i], SIGNAL(textChanged(const QString &)), mapper, SLOT(map()));
    }
    label[4] = new QLabel("PWM:", this);
    label[5] = new QLabel("", this);

    label[5]->setMinimumHeight(50);
    label[5]->setStyleSheet({"background-color: #FFF; border:1px solid black;"});
    QFont font;
    font.setPointSize(24);
    label[5]->setFont(font);

    ui->gridLayout->addWidget(label[4]);
    ui->gridLayout->addWidget(label[5]);

    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(onChange(int)));
    connect(comboBox, SIGNAL(textActivated(const QString &)), this, SLOT(onComboChange(const QString &)));
}
/**
 * @brief 析构函数
 */
QTApplication::~QTApplication()
{
    delete ui;
}

void QTApplication::calculator()
{
    if (core != 0 && Prescaler != 0 && resetCount != 0)
    {
        PWM = core / (Prescaler * resetCount);
        if (PWM != 0)
        {
            label[5]->setText(QString::number(PWM));
            return;
        }
        label[5]->setText("");
    }
}

/**
 * @brief 槽函数
 * @param text 字符串
 */
void QTApplication::onComboChange(const QString &text)
{
    lineEdit[1]->blockSignals(true);
    lineEdit[1]->setText(text);
    Prescaler = text.back().digitValue();
    lineEdit[1]->blockSignals(false);
    calculator();
}

/**
 * 槽函数
 * @param value 枚举或数字
 */
void QTApplication::onChange(int vlaue)
{
    switch (vlaue)
    {
    case 0:
        /* 核心频率(MHz) */
        core = lineEdit[0]->text().toUInt() * 1000;
        break;
    case 1:
        /* PWM分频 */
        Prescaler = lineEdit[1]->text().toUInt();

        break;
    case 2:
        /* 装载值 */
        resetCount = lineEdit[2]->text().toUInt();
        break;
    case 3:
        /* 心跳值 */
        pulse = lineEdit[3]->text().toUInt();
        break;
    default:
        break;
    }
    calculator();
}
