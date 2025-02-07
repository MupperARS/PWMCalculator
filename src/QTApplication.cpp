#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    QSignalMapper *mapper = new QSignalMapper(this);

    ui->setupUi(this);

    this->setWindowIcon(QIcon("../static/calculator.ico"));
    this->setWindowTitle("PWMcalculator");
    this->setMinimumSize(360, 500);

    QString labelName[] = {"Core frequency(MHz):", "Precrossover factor:", "Overload value(0-65535):", "pulse: 0%"};
    QFont font;

    for (uint16_t i = 0; i < 3; i++)
    {
        label[i] = new QLabel(labelName[i], this);
        lineEdit[i] = new QLineEdit(this);
        if (i == 1)
        {
            QHBoxLayout *hboxLaylout = new QHBoxLayout();
            comboBox = new QComboBox(this);
            comboBox->addItems({"TIM_CLOCKDIVISION_DIV1", "TIM_CLOCKDIVISION_DIV2", "TIM_CLOCKDIVISION_DIV4"});
            comboBox->setMaximumWidth(40);
            hboxLaylout->addWidget(lineEdit[i]);
            hboxLaylout->addWidget(comboBox);
            ui->gridLayout->addWidget(label[i], i, 0, 1, 2);
            ui->gridLayout->addLayout(hboxLaylout, i, 1, 1, 1);
        }
        else
        {
            lineEdit[i]->setMaxLength(5);
            ui->gridLayout->addWidget(label[i], i, 0);
            ui->gridLayout->addWidget(lineEdit[i], i, 1);
        }
        mapper->setMapping(lineEdit[i], i);
        connect(lineEdit[i], SIGNAL(textChanged(const QString &)), mapper, SLOT(map()));
    }

    QPushButton *copyButton = new QPushButton("copy", this);
    label[3] = new QLabel(labelName[3], this);
    label[4] = new QLabel("PWM:", this);
    slider = new QSlider(Qt::Horizontal, this);

    label[3]->setMaximumHeight(20);
    label[4]->setMaximumHeight(20);

    ui->gridLayout->addWidget(label[3], 3, 0);
    ui->gridLayout->addWidget(slider, 3, 1, 1, 1);
    ui->gridLayout->addWidget(label[4], 5, 0, 1, 2);
    ui->gridLayout->addWidget(copyButton, 5, 1, 1, 1);

    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(onChange(int)));
    connect(comboBox, SIGNAL(textActivated(const QString &)), this, SLOT(onComboChange(const QString &)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));
    connect(copyButton, SIGNAL(clicked()), this, SLOT(copy()));

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
            label[4]->setText("PWM:" + QString::number(PWM) + "hz");
            return;
        }
        label[4]->setText("PWM: No value");
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

void QTApplication::changed(int vlaue)
{
    label[3]->setText("pulse: " + QString::number(vlaue) + "%");
}

void QTApplication::copy()
{
    clip = QApplication::clipboard();
    if (PWM != 0)
        clip->setText(QString::number(PWM));
}

/**
 * 槽函数
 * @param value 枚举或数字
 */
void QTApplication::onChange(int vlaue)
{
    int number;
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
        number = lineEdit[2]->text().toUInt();
        if (number > 65535)
        {
            resetCount = 65535;
            lineEdit[2]->blockSignals(true);
            lineEdit[2]->setText("65535");
            lineEdit[2]->blockSignals(false);
            break;
        }
        resetCount = number;
        break;
    default:
        break;
    }
    calculator();
}
