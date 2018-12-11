#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("../Tapiz1.png"); //  /home/vittorino/ImageEditor/
    //ui->label->setPixmap(pix.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images(*.bmp)")); // "Images(*.png *.jpg *.jpeg *.bmp *.gif)"
    if(QString::compare(filename,QString())!=0){
         QImage image;
         QByteArray ba = filename.toLocal8Bit();
         char *c_str2 = ba.data();
         theImage = readBMP(c_str2);
         //bool valid = image.load(filename);
         image = uchar2Qimage(theImage,Img_width,Img_height);
         image = image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
         ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

unsigned char* MainWindow::readBMP(char* filename){
        int i;
        FILE* f = fopen(filename, "rb");
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

        // extract image height and width from header
        Img_width = *(int*)&info[18]; //
        Img_height = *(int*)&info[22]; //

        int size = 3 * Img_width * Img_height;
        unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
        fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
        fclose(f);
        unsigned char tmp;
        for(int i=0;i<size/2;i++){
            tmp = data[i];
            data[i] = data[size-i-1];
            data[size-i-1] = tmp;
        }

        return data;
}


QImage MainWindow::uchar2Qimage(unsigned char* array,int width,int height){
    QImage unaImagen(array, width, height,  QImage::Format_RGB888);
    return unaImagen;
}



void MainWindow::on_actionto_Gray_triggered()
{
    int Img_size = Img_width*Img_height;
    unsigned char Img_gray[Img_size];
    for(int i=0;i<Img_size;i++){
        Img_gray[i] = (theImage[3*i]+theImage[3*i+1]+theImage[3*i+2])/3;
    }
    QImage unaImagen(Img_gray, Img_width, Img_height,  QImage::Format_Indexed8);
    unaImagen = unaImagen.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);
    ui->label_2->setPixmap((QPixmap::fromImage(unaImagen)).scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));
    //ui->label_2->setPixmap(unaImagen.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));
}

void MainWindow::on_actionAbout_Us_triggered()
{
    QMessageBox::about(this,"About This","This work correspond to a Master in Computer Science in the UCSP. The author is Vittorino Mandujano Cornejo.");
}


void MainWindow::on_actionBlur_triggered()
{
    int factor;
    int Img_blur1[Img_width][Img_height];
    int Img_blur2[Img_width][Img_height];
    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j] = theImage[3*i+j*Img_height];
            Img_blur2[i][j] = 0;
            //Img_blur3[i][j] = 0;
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            for(int q=-2;q<3;q++){
                if(0<=j+q && j+q<Img_height){
                    Img_blur2[i][j] += Img_blur1[i][j+q];
                }
            }
        }
    }


    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j]  = 0;
            for(int q=-2;q<3;q++){
                if(0<=i+q && i+q<Img_width){
                    Img_blur1[i][j] += Img_blur2[i+q][j];
                }
            }
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            if(2<i && i<Img_width-2 && 2<j && j<Img_height-2){
                factor = 25;
            }else if(((i==1 ||i==Img_width-2) && 1<j && j<Img_height-2) || ( (j==1 ||j==Img_height-2) && 1<j && j<Img_width-2) ){
                factor = 20;
            }else if(((i==0 ||i==Img_width-1) && 1<j && j<Img_height-1) || ( (j==0 ||j==Img_height-1) && 1<j && j<Img_width-1) ) {
                factor = 15;
            }else if( ( (j==0||j==Img_height-1) && (i==1||j==Img_width-2) ) || ( (j==1||j==Img_height-2) && (i==0||j==Img_width-1) ) ){
                factor = 12;
            }else if( (i==1||i==Img_width-2)&&(j==1||j==Img_height-2) ){
                factor = 16;
            }else{
                factor = 9;
            }

            Img_blur1[i][j] /=factor;
            theImage[3*i+j*Img_height] = (unsigned char)Img_blur1[i][j];
        }
    }
    //======================================================================================================================================
    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j] = theImage[3*i+1+j*Img_height];
            Img_blur2[i][j] = 0;
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            for(int q=-2;q<3;q++){
                if(0<=j+q && j+q<Img_height){
                    Img_blur2[i][j] += Img_blur1[i][j+q];
                }
            }
        }
    }


    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j]  = 0;
            for(int q=-2;q<3;q++){
                if(0<=i+q && i+q<Img_width){
                    Img_blur1[i][j] += Img_blur2[i+q][j];
                }
            }
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            if(2<i && i<Img_width-2 && 2<j && j<Img_height-2){
                factor = 25;
            }else if(((i==1 ||i==Img_width-2) && 1<j && j<Img_height-2) || ( (j==1 ||j==Img_height-2) && 1<j && j<Img_width-2) ){
                factor = 20;
            }else if(((i==0 ||i==Img_width-1) && 1<j && j<Img_height-1) || ( (j==0 ||j==Img_height-1) && 1<j && j<Img_width-1) ) {
                factor = 15;
            }else if( ( (j==0||j==Img_height-1) && (i==1||j==Img_width-2) ) || ( (j==1||j==Img_height-2) && (i==0||j==Img_width-1) ) ){
                factor = 12;
            }else if( (i==1||i==Img_width-2)&&(j==1||j==Img_height-2) ){
                factor = 16;
            }else{
                factor = 9;
            }

            Img_blur1[i][j] /=factor;
            theImage[3*i+1+j*Img_height] = (unsigned char)Img_blur1[i][j];
        }
    }

    //=========================================================================================================================================


    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j] = theImage[3*i+2+j*Img_height];
            Img_blur2[i][j] = 0;
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            for(int q=-2;q<3;q++){
                if(0<=j+q && j+q<Img_height){
                    Img_blur2[i][j] += Img_blur1[i][j+q];
                }
            }
        }
    }


    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            Img_blur1[i][j]  = 0;
            for(int q=-2;q<3;q++){
                if(0<=i+q && i+q<Img_width){
                    Img_blur1[i][j] += Img_blur2[i+q][j];
                }
            }
        }
    }

    for(int i=0;i<Img_width;i++){
        for(int j=0;j<Img_height;j++){
            if(2<i && i<Img_width-2 && 2<j && j<Img_height-2){
                factor = 25;
            }else if(((i==1 ||i==Img_width-2) && 1<j && j<Img_height-2) || ( (j==1 ||j==Img_height-2) && 1<j && j<Img_width-2) ){
                factor = 20;
            }else if(((i==0 ||i==Img_width-1) && 1<j && j<Img_height-1) || ( (j==0 ||j==Img_height-1) && 1<j && j<Img_width-1) ) {
                factor = 15;
            }else if( ( (j==0||j==Img_height-1) && (i==1||j==Img_width-2) ) || ( (j==1||j==Img_height-2) && (i==0||j==Img_width-1) ) ){
                factor = 12;
            }else if( (i==1||i==Img_width-2)&&(j==1||j==Img_height-2) ){
                factor = 16;
            }else{
                factor = 9;
            }

            Img_blur1[i][j] /=factor;
            theImage[3*i+2+j*Img_height] = (unsigned char)Img_blur1[i][j];
        }
    }

    //==================================================================================================================================

    QImage unaImagen(theImage, Img_width, Img_height,  QImage::Format_RGB888);
    unaImagen = unaImagen.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);
    ui->label_2->setPixmap((QPixmap::fromImage(unaImagen)).scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));

}

void MainWindow::on_actionIlumination_triggered()
{
    unsigned char theImage2[Img_width*Img_height];
    int Img_Ilum[Img_width*Img_height];
    for(int i=0;i<Img_width*Img_height;i++){
        Img_Ilum[i] = *(int*)&theImage[i];
        Img_Ilum[i] = 100+5*Img_Ilum[i];
        if(Img_Ilum[i]<0){
            Img_Ilum[i]=0;
        }

        if(255<Img_Ilum[i]){
            Img_Ilum[i]=255;
        }
        theImage2[i] = *(unsigned char*)&Img_Ilum[i] ;
    }
    QImage unaImagen(theImage2, Img_width, Img_height,  QImage::Format_RGB888);
    unaImagen = unaImagen.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);
    ui->label_2->setPixmap((QPixmap::fromImage(unaImagen)).scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));
}
