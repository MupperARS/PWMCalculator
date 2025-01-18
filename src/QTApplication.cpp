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
        lineEdit[i]->setMinimumSize(60, 15);
        lineEdit[i]->setMaximumWidth(60);
        ui->gridLayout->addWidget(label[i]);
        ui->gridLayout->addWidget(lineEdit[i]);
        if (i == 1)
        {
            comboBox = new QComboBox(this);
            comboBox->addItems(list);
            comboBox->setMaximumWidth(40);
            ui->gridLayout->addWidget(comboBox);
        }

        mapper->setMapping(lineEdit[i], i);
        connect(lineEdit[i], SIGNAL(textChanged(const QString &)), mapper, SLOT(map()));
    }

    connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(onChange(int)));
}
// PWM分频
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
void QTApplication::onChange(int vlaue)
{
    qDebug() << vlaue;
    switch (vlaue)
    {
    case 0:
        /* 核心频率(MHz) */
        core = lineEdit[0]->text().toUInt();
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
}
