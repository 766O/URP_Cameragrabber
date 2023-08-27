#include "mainwindow.h"
#include "camthread.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mDecoding = false;

    /* Get Mac address and IP addeBUS SDK pipeline에 대한 이해를 바탕으로 메뉴얼을 참고하여 스켈레톤 코드 작성
코드에 대한 전반적인 이해eBUS SDK pipeline에 대한 이해를 바탕으로 메뉴얼을 참고하여 스켈레톤 코드 작성
코드에 대한 전반적인 이해ress (eBUSPlayer) */
    mCamMac = "00:b0:9d:be:70:50";   //"00:b0:9d:be:70:50";
    mCamIP = "192.168.0.2"; //"192.168.0.2";

    mCamMac2 ="00:11:1c:02:92:81";   //"00:b0:9d:be:70:50"; // thermal camera mac
    mCamIP2 =  "192.168.0.4"; //"192.168.0.2"; //thermal camera ip



    mCamera = new CamThread;
    mCamera2 = new CamThread;

    // SIGNAL? SLOT?)
    connect( mCamera, SIGNAL( Display(QImage) ), this, SLOT( Display_CAM(QImage) ) );
    connect( mCamera2, SIGNAL( Display(QImage) ), this, SLOT( Display_CAM2(QImage) ) );

}



MainWindow::~MainWindow()
{
    delete mCamera;
    delete ui;
}

void MainWindow::on_mInit_clicked()
{
    ShellScript();

    CamInitialize( mCamMac.toStdString().c_str(), mCamIP.toStdString().c_str());

    CamInitialize( mCamMac2.toStdString().c_str(), mCamIP2.toStdString().c_str());


}

void MainWindow::on_mConnect_clicked()
{
    if ( !mCamera->mAcquisition )
    {
        if ( mCamera->Connect( mCamMac.toStdString().c_str() ) ) cout << "Connected" << endl;

        mCamera->mAcquisition = true;


        mCamera->start();

        ui->mConnect->setText("DisConnected");
    }
    else
    {
        mCamera->mAcquisition = false;

        mCamera->quit();
        mCamera->wait();

        if (!mCamera->DisConnect()) cout << "Disconnection failed" << endl;

        ui->mConnect->setText("Connecode bcted");
    }

    if ( !mCamera2->mAcquisition )
    {
        if ( mCamera2->Connect( mCamMac2.toStdString().c_str() ) ) cout << "Connected" << endl;

        mCamera2->mAcquisition = true;

        mCamera2->start();

        ui->mConnect->setText("DisConnected");
    }
    else
    {
        mCamera2->mAcquisition = false;

        mCamera2->quit();
        mCamera2->wait();

        if (!mCamera2->DisConnect()) cout << "Disconnection failed" << endl;

        ui->mConnect->setText("Connecode bcted");
    }




}



void MainWindow::Display_CAM( QImage img )
{
    ui->mDisplay->setPixmap( QPixmap::fromImage( img.scaled( ui->mDisplay->width(), ui->mDisplay->height() ) ) );


}

void MainWindow::Display_CAM2( QImage img )
{
    ui->mDisplay_2->setPixmap( QPixmap::fromImage( img.scaled( ui->mDisplay_2->width(), ui->mDisplay_2->height() ) ) );


}

void MainWindow::ShellScript()
{
    if (system("echo 'urp11' |"
               " sudo -SAcquireImages /opt/pleora/ebus_sdk/linux-aarch64-arm/bin/set_rp_filter.sh"
               " --mode=0 --restartnetworkstack=yes"))
    {
        cout << "set_rp_filter failed" << endl;
    }

    if (system("echo 'urp11' | sudo -S /opt/pleora/ebus_sdk/linux-aarch64-arm/bin/set_socket_buffer_size.sh"))
    {
        cout << "set_soket_buffer failed" << endl;
    }
    else cout << "set_soket_buffer" << endl;

    if (system("echo 'urp11' | sudo -S /opt/pleora/ebus_sdk/linux-aarch64-arm/bin/set_usbfs_memory_size.sh"))
    {
        cout << "set_usbfs_memory_size failed" << endl;
    }
    else cout << "set_usbfs_memory_size" << endl;
}

void MainWindow::CamInitialize(const char* Mac, const char* IpAdr)
{
    PvDeviceGEV* lDeviceSetIp = NULL;
    PvResult lResult;

    /*
    Requirements. 1: Force GigE Device IP Address.
    Change the IP Configuration of a device. Set default gateway parameter.
    */
    /* Todo */
    lResult = lDeviceSetIp->PvDeviceGEV::SetIPConfiguration(Mac,IpAdr,"255.255.255.0");

    if (!lResult.IsOK()) cout << lResult.GetCodeString().GetAscii() << endl;

}






void MainWindow::on_record_clicked()
{

    if(mCamera->mRecording==true)
    {
        mCamera->mRecording=false;
    }
    else
    {
        mCamera->mRecording=true;
    }


    if(mCamera2->mRecording==true)
    {
        mCamera2->mRecording=false;
    }
    else
    {
        mCamera2->mRecording=true;
    }



}

void MainWindow::on_decord_clicked()
{
    mCamera->Decode();
    mCamera2->Decode();




}


void MainWindow::on_capture_clicked()
{
    QImage qimg;
    QImage qimg2;

    qimg=mCamera->capture();
    qimg2=mCamera2->capture();




    QString currentDateTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");

    QString snapshotFileName_rgb = "/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/rgb/" + currentDateTimeString + "RGB.bmp";
    qimg.save(snapshotFileName_rgb, "bmp");

    QString snapshotFileName_thermal = "/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/thermal/" + currentDateTimeString + "Thermal.bmp";
    qimg2.save(snapshotFileName_thermal, "bmp");



}


void MainWindow::on_color_display_clicked()
{
    if (mCamera->mAcquisition) {
                mCamera->mAcquisition = false;

                mCamera->quit();
                mCamera->wait();

                if (!mCamera->DisConnect()) {
                    cout << "Disconnection failed" << endl;
                }

                ui->color_display->setText("Color display Off");
                ui->color_display->setStyleSheet("background-color: red");
            }
        else {


                if (mCamera->Connect(mCamMac.toStdString().c_str())) {
                    cout << "Connec CamThread:ted" << endl;

                    mCamera->mAcquisition = true;
                    mCamera->start();

                    ui->color_display->setText("Color display On");
                    ui->color_display->setStyleSheet("background-color: red");
                }
            }
}

void MainWindow::on_thermal_display_clicked()
{

    if (mCamera2->mAcquisition) {
                mCamera2->mAcquisition = false;

                mCamera2->quit();
                mCamera2->wait();

                if (!mCamera2->DisConnect()) {
                    cout << "Disconnection failed" << endl;
                }

                ui->thermal_display->setText("Thermal display Off");
                ui->color_display->setStyleSheet("background-color: red");
            }
        else {


                if (mCamera2->Connect(mCamMac2.toStdString().c_str())) {
                    cout << "Connected" << endl;

                    mCamera2->mAcquisition = true;
                    mCamera2->start();

                    ui->thermal_display->setText("Thermal display On");
                }
            }
}
