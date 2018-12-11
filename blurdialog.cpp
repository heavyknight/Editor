#include "blurdialog.h"
#include "ui_blurdialog.h"

BlurDialog::BlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlurDialog)
{
    ui->setupUi(this);
}

BlurDialog::~BlurDialog()
{
    delete ui;
}
