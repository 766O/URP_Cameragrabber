#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>

#include <sys/stat.h>
#include <sys/stat.h>

#include "camthread.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_mInit_clicked();
    void on_mInit_2_clicked();

    void on_mConnect_clicked();
    void on_mConnect_2_clicked();


    void Display_CAM( QImage img );
    void Display_CAM2( QImage img );



    void on_color_display_clicked();

    void on_thermal_display_clicked();



    void on_record_clicked();

    void on_decord_clicked();


    void on_capture_clicked();

private:
    Ui::MainWindow *ui;

    void ShellScript();
    void CamInitialize(const char* Mac, const char* IpAdr);

    bool mDecoding;

    FILE* mFileStream;

    QString mCamMac;
    QString mCamIP;

    QString mCamMac2;
    QString mCamIP2;

    CamThread* mCamera;
    CamThread* mCamera2;
};

#endif // MAINWINDOW_H
