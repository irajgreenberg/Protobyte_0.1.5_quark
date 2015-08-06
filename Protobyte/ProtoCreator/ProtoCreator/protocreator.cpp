#include "protocreator.h"
#include "ui_protocreator.h"

ProtoCreator::ProtoCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtoCreator)
{
    ui->setupUi(this);
}

ProtoCreator::~ProtoCreator()
{
    delete ui;
}
