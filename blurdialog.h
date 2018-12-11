#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QDialog>

namespace Ui {
class BlurDialog;
}

class BlurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlurDialog(QWidget *parent = nullptr);
    ~BlurDialog();

private:
    Ui::BlurDialog *ui;
};

#endif // BLURDIALOG_H
