#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionto_Gray_triggered();

    void on_actionAbout_Us_triggered();

    void on_actionBlur_triggered();

    void on_actionIlumination_triggered();

private:
    Ui::MainWindow *ui;
    int Img_width,Img_height;
    unsigned char* theImage;
    QImage uchar2Qimage(unsigned char*,int,int);
    unsigned char* readBMP(char*);
    //int widthOfFile(char*);
    //int heightOfFile(char*);
};

#endif // MAINWINDOW_H
