#ifndef CAMTHREAD_H
#define CAMTHREAD_H

#include <QObject>

#include <QThread>
#include <QImage>
#include <QMutex>
#include<QFileDialog>


#include <PvDevice.h>
#include <PvDeviceGEV.h>
#include <PvStream.h>
#include <PvStreamGEV.h>
#include <PvBuffer.h>
#include <PvBufferConverter.h>
#include <PvSystem.h>
#include <PvTypes.h>
#include <PvInterface.h>
#include <PvPixelType.h>
#include <PvBufferWriter.h>
#include <PvPipeline.h>
#include <PvBufferLib.h>
#include <PvPixelType.h>
#include <PvResult.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>


class CamThread : public QThread
{
    Q_OBJECT
public:
    explicit CamThread(QObject *parent = nullptr);

    bool mAcquisition;
    bool mAcquisition2;
    bool mRecording=false;

    const char* mFilePath;

    FILE* mFileStream;
    FILE* mFileStream2;

    PvDevice* mDevice;
    PvDeviceGEV* mDeviceGEV;
    PvStream* mStream;
    PvStreamGEV* mStreamGEV;
    PvPipeline* mPipeline;

    PvDevice* mDevice2;
    PvDeviceGEV* mDeviceGEV2;
    PvStream* mStream2;
    PvStreamGEV* mStreamGEV2;
    PvPipeline* mPipeline2;

    PvBuffer* lBuffer;

    bool start_record=0;


    bool Connect(const char* Mac);

    bool DisConnect();

    QImage mat_to_qimage_cpy(cv::Mat const &mat, QImage::Format format);
    cv::Mat qimage_to_mat_cpy(QImage const &img, int format);
    QImage Buffer_to_qimage_cpy(PvBuffer* const &buffer, QImage::Format format, uint32_t size);
    QImage capture();
    QImage Decode();
    void CaptureAndAppendImages(uint32_t captureCount);

private:
    void run();

    PvStreamGEV* ConfigureStream( PvDevice *aDevice, PvStream *aStream );
    PvDevice* ConnectToDevice( const char* aConnectionID);
    PvStream* OpenStream( const PvString &aConnectionID );
    PvPipeline* MakePipeline( PvDeviceGEV *aDevice, PvStream *aStream );

    QImage AcquireImages_capture( PvDeviceGEV* Device, PvPipeline* Pipeline, PvStreamGEV* Stream);
    void AcquireImages( PvDeviceGEV* Device, PvPipeline* Pipeline, PvStreamGEV* Stream);

signals:
    void Display( QImage img );

public slots:
};

#endif // CAMTHREAD_H
