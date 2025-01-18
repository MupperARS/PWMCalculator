#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    QSignalMapper *mapper = new QSignalMapper(this);

    ui->setupUi(this);

    this->setWindowIcon(QIcon("../static/calculator.ico"));
    this->setWindowTitle("PWMcalculator");
    this->setMinimumSize(360, 500);

    QString name[] = {"Core frequency(MHz):", "Precrossover factor:", "Overload value(0-65535):", "pulse:"};
    QStringList list = {"TIM_CLOCKDIVISION_DIV1", "TIM_CLOCKDIVISION_DIV2", "TIM_CLOCKDIVISION_DIV4"};
    QFont font;

    for (uint16_t i = 0; i < 4; i++)
    {
        label[i] = new QLabel(name[i], this);
        lineEdit[i] = new QLineEdit(this);

        if (i == 1)
        {
            QHBoxLayout *hboxLaylout = new QHBoxLayout();
            comboBox = new QComboBox(this);
            comboBox->addItems(list);
            hboxLaylout->addWidget(lineEdit[i], 1);
            hboxLaylout->addWidget(comboBox);
            ui->gridLayout->addWidget(label[i], i, 0);
            ui->gridLayout->addLayout(hboxLaylout, i, 1);
        }
        else
        {
            ui->gridLayout->addWidget(label[i], i, 0);
            ui->gridLayout->addWidget(lineEdit[i], i, 1);
        }
        mapper->setMapping(lineEdit[i], i);
        connect(lineEdit[i], SIGNAL(textChanged(const QString &)), mapper, SLOT(map()));
    }
    label[4] = new QLabel("PWM:", this);
    label[4]->setMaximumHeight(20);
    label[5] = new QLabel("", this);

    label[5]->setStyleSheet({"background-color: #FFF; border:1px solid black;"});
    font.setPointSize(16);
    label[5]->setFont(font);

    ui->gridLayout->addWidget(label[4], 4, 0, 1, 2);
    ui->gridLayout->addWidget(label[5], 5, 0, 1, 2);

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
