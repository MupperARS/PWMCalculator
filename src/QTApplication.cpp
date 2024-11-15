#include "QTApplication.h"
#include <QApplication>

QTApplication::QTApplication(QWidget *parent) : QMainWindow(parent), ui(new Ui_QTApplication)
{
    ui->setupUi(this);

    connect(ui->commitLineEdit, SIGNAL(returnPressed()), this, SLOT(on_commitButton_clicked()));
}

QTApplication::~QTApplication()
{
    delete ui;
}

void QTApplication::on_commitButton_clicked()
{

    QString context = ui->commitLineEdit->text();

    ui->label->setText(context);
    ui->commitLineEdit->setText("");
    //QProcess *process = new QProcess(this);
    //process->start(context);
}