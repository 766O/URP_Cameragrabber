#include "camthread.h"

using namespace std;

CamThread::CamThread(QObject *parent) : QThread(parent)
{
    mDevice = NULL;
    mDeviceGEV = NULL;
    mStream = NULL;
    mStreamGEV = NULL;
    mPipeline = NULL;

    ///////////////////////



    mAcquisition = false;
    mRecording = false;
}

void CamThread::run()
{
    cout << "Run" << endl;

    if ( mDeviceGEV == NULL ) cout << "mDeviceGEV NULL..." << endl;
    if ( mStreamGEV == NULL ) cout << "mStreamGEV NULL..." << endl;
    if ( mPipeline == NULL ) cout << "mPipeline NULL..." << endl;



    AcquireImages( mDeviceGEV, mPipeline, mStreamGEV );

}
/*
void CamThread::AcquireImages(PvDeviceGEV *Device, PvPipeline *Pipeline, PvStreamGEV *Stream)
{



    mFileStream=fopen("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_rgb.bin","wb");
    mFileStream2=fopen("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_thermal.bin","wb");


    // Get device parameters need to control streaming
    PvGenParameterArray *lDeviceParams = Device->GetParameters();


    // Map the AcquisitionStart(start) and AcquisitionStop(stop) commands
    PvGenCommand *lStart = dynamic_cast<PvGenCommand *>( lDeviceParams->Get( "AcquisitionStart" ) );
    PvGenCommand *lStop = dynamic_cast<PvGenCommand *>( lDeviceParams->Get( "AcquisitionStop" ) );

    // Enable PvStream and send the AcquisitionStart
    cout << "Enabling streaming and sending AcquisitionStart command." << endl;
    Device->StreamEnable();
    lStart->Execute();

    cout << endl << "<Start>" << endl;

    PvResult Result;

    PvBuffer* Buffer;
    PvBuffer* Buffer2;




    // Think about the role of the "mAcquisition"
    while( mAcquisition )
    {
        QImage qimg;
        Buffer = NULL;
        Buffer2=NULL;


        if (Stream->IsOpen() && Pipeline->IsStarted())
        {
            // RetrieveNextBuffer( &lBuffer, timeout, &lOperationResult )
            Result = Pipeline->RetrieveNextBuffer( &Buffer, 0xFFFFFFFF, &Result);
            Result = Pipeline->RetrieveNextBuffer( &Buffer2, 0xFFFFFFFF, &Result);

            if( !Result.IsOK() ) continue;
        }

        uint32_t width = Buffer->GetImage()->GetWidth();
        uint32_t height = Buffer->GetImage()->GetHeight();

        if ( width != 0 )
        {
            uint32_t size = Buffer->GetSize();

            cv::Mat img_C1( height, width, CV_8UC1 );

            memcpy( img_C1.data, Buffer->GetDataPointer(), size );

            if ( width > 320 )  // RGB
            {
                cv::Mat img( 964, 1288, CV_8UC3 );
                cv::cvtColor( img_C1, img, cv::COLOR_BayerGB2BGR);



                if ( mRecording )
                {
                    fwrite( img.data, sizeof(uchar), img.cols * img.rows * 3, mFileStream );
                    //cout << "rgb_record" << endl;
                }


                qimg = mat_to_qimage_cpy( img, QImage::Format_RGB888 );

            }
            else // Thermal
            {

               if ( mRecording )
               {
                   fwrite( img_C1.data, sizeof(uchar), img_C1.cols * img_C1.rows, mFileStream2 );
                   //cout << "thermal_record" << endl;
               }


                qimg = mat_to_qimage_cpy( img_C1, QImage::Format_Grayscale8 );
            }

            emit Display( qimg );
            Result = Pipeline->ReleaseBuffer( Buffer );
            if (!Result.IsOK()) cout << "Can't ReleaseBuffer" << endl;

        }
    }

    lStop->Execute();
    Device->StreamDisable();
    Stream->AbortQueuedBuffers();

}
*/

void CamThread::AcquireImages(PvDeviceGEV *Device, PvPipeline *Pipeline, PvStreamGEV *Stream)
{



    mFileStream=fopen("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_rgb.bin","wb");
    mFileStream2=fopen("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_thermal.bin","wb");


    // Get device parameters need to control streaming
    PvGenParameterArray *lDeviceParams = Device->GetParameters();


    // Map the AcquisitionStart(start) and AcquisitionStop(stop) commands
    PvGenCommand *lStart = dynamic_cast<PvGenCommand *>( lDeviceParams->Get( "AcquisitionStart" ) );
    PvGenCommand *lStop = dynamic_cast<PvGenCommand *>( lDeviceParams->Get( "AcquisitionStop" ) );

    // Enable PvStream and send the AcquisitionStart
    cout << "Enabling streaming and sending AcquisitionStart command." << endl;
    Device->StreamEnable();
    lStart->Execute();

    cout << endl << "<Start>" << endl;

    PvResult Result;

    PvBuffer* Buffer;




    // Think about the role of the "mAcquisition"
    while( mAcquisition )
    {
        QImage qimg;
        Buffer = NULL;



        if (Stream->IsOpen() && Pipeline->IsStarted())
        {
            // RetrieveNextBuffer( &lBuffer, timeout, &lOperationResult )
            Result = Pipeline->RetrieveNextBuffer( &Buffer, 0xFFFFFFFF, &Result);


            if( !Result.IsOK() ) continue;
        }

        uint32_t width = Buffer->GetImage()->GetWidth();
        uint32_t height = Buffer->GetImage()->GetHeight();







        if ( width != 0 )
        {
            uint32_t size = Buffer->GetSize();



            cv::Mat img_C1( height, width, CV_8UC1 );

            memcpy( img_C1.data, Buffer->GetDataPointer(), size );

            if ( width > 320 )  // RGB
            {
                cv::Mat img( 964, 1288, CV_8UC3 );
                cv::cvtColor( img_C1, img, cv::COLOR_BayerGB2BGR);



                if ( mRecording )
                {
                    fwrite( img.data, sizeof(uchar), img.cols * img.rows * 3, mFileStream );
                    //cout << "rgb_record" << endl;
                }


                qimg = mat_to_qimage_cpy( img, QImage::Format_RGB888 );

            }
            else // Thermal
            {

               if ( mRecording )
               {
                   fwrite( img_C1.data, sizeof(uchar), img_C1.cols * img_C1.rows, mFileStream2 );

               }


                qimg = mat_to_qimage_cpy( img_C1, QImage::Format_Grayscale8 );
            }

            emit Display( qimg );
            Result = Pipeline->ReleaseBuffer( Buffer );
            if (!Result.IsOK()) cout << "Can't ReleaseBuffer" << endl;

        }
    }

    lStop->Execute();
    Device->StreamDisable();
    Stream->AbortQueuedBuffers();

}



QImage CamThread::Decode() {




    QFile binaryFile("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_rgb.bin");
    QFile binaryFile2("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test_thermal.bin");



    if (!binaryFile.open(QIODevice::ReadOnly))
                {
                    cout << "ddddd." << endl;
                }
    if (!binaryFile2.open(QIODevice::ReadOnly))
                {
                    cout << "ddddd." << endl;
                }



    QByteArray array = binaryFile.readAll();
    QByteArray array2 = binaryFile2.readAll();

    int image_total= array.size()/3686400;
    int image_total2=array2.size()/(320*256);

     cout << image_total << endl;
     cout << image_total2 << endl;



    for(int i=0; i<image_total;i++){

        QImage img ((const uchar*)(array.data())+i*1280*960*3 ,1280,960,QImage::Format_RGB888);

       // cout << i  << endl;
        cout << "th rgb_image save! " << endl;

        img.save("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/rgb/"+ QString::number((i))+"decode_rgb.bmp" );


    }

    for(int i=0; i<image_total2;i++){

        QImage img ((const uchar*)(array2.data())+i*320*256*1 ,320,256 ,QImage::Format_Grayscale8);

      //  cout << i  << endl;
        cout << "th thermal_image save! " << endl;

        img.save("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/thermal/"+ QString::number((i))+"decode_thermal.bmp" );


    }

}

QImage CamThread::AcquireImages_capture(PvDeviceGEV *Device, PvPipeline *Pipeline, PvStreamGEV *Stream)
{
    // Get device parameters need to control streaming
    PvGenParameterArray *lDeviceParams = Device->GetParameters();



    // Enable PvStream and send the AcquisitionStart
    cout << "Enabling streaming and sending AcquisitionStart command." << endl;
    Device->StreamEnable();


    cout << endl << "<Start>" << endl;

    PvResult Result;

    PvBuffer* Buffer=nullptr;

    QImage qimg;

    // Think about the role of the "mAcquisition"





        if (Stream->IsOpen() && Pipeline->IsStarted())
        {
            // RetrieveNextBuffer( &lBuffer, timeout, &lOperationResult )
            Result = Pipeline->RetrieveNextBuffer( &Buffer, 0xFFFFFFFF, &Result);

            if(!Result.IsOK())
            {
                cout << "fail" <<endl;
                return QImage();
            }


        }
        else
        {
            cout << "Stream not open" <<endl;
            return QImage();
        }

        uint32_t width = Buffer->GetImage()->GetWidth();
        uint32_t height = Buffer->GetImage()->GetHeight();

        if ( width != 0 )
        {
            uint32_t size = Buffer->GetSize();

            cv::Mat img_C1( height, width, CV_8UC1 );

            memcpy( img_C1.data, Buffer->GetDataPointer(), size );

            if ( width > 320 )  // RGB
            {
                cv::Mat img( 964, 1288, CV_8UC3 );
                cv::cvtColor( img_C1, img, cv::COLOR_BayerGB2BGR);

                if ( mRecording ) fwrite( img.data, sizeof(uchar), img.cols * img.rows * 3, mFileStream );

                qimg = mat_to_qimage_cpy( img, QImage::Format_RGB888 );

            }
            else // Thermal
            {
               if ( mRecording ) fwrite( img_C1.data, sizeof(uchar), img_C1.cols * img_C1.rows, mFileStream );

                qimg = mat_to_qimage_cpy( img_C1, QImage::Format_Grayscale8 );
            }



            Result = Pipeline->ReleaseBuffer( Buffer );
            if (!Result.IsOK()) cout << "Can't ReleaseBuffer" << endl;
        }





    Device->StreamDisable();
    Stream->AbortQueuedBuffers();

    return qimg;
}



QImage CamThread::capture()
{

    cout << "capture function start" <<endl;
    QImage qimg=AcquireImages_capture(mDeviceGEV,mPipeline,mStreamGEV);

    return qimg;
}

bool CamThread::Connect(const char* Mac)
{
    mDevice = ConnectToDevice(Mac);//ebus


    /*
    Requirements. 2: cast mDevice to GigE vision class (see ConnectToDevice requirements).
    ○ Hint: use mDevice, dynamic_cast<>
    */
    /* Todo */
    mDeviceGEV = dynamic_cast<PvDeviceGEV*>(mDevice);
    if ( mDevice != NULL )
    {
        mStream = OpenStream( mDeviceGEV->GetIPAddress() );

        if (mStream != NULL)
        {
            mStreamGEV = ConfigureStream(mDevice, mStream);

            mPipeline = MakePipeline( mDeviceGEV, mStream );

            if ( mPipeline == NULL ) return false;

        }
        else
        {
            cout << "Disable to stream from camera" << endl;

            return false;
        }
    }
    else
    {
        cout << "Disable to connect to camera" << endl;
        return false;
    }

    return true;
}




bool CamThread::DisConnect()
{
    /*
    If user force quit the connection, some errors might be occured (i.e. -connection error between the camera and user platform).
    "Disassembly is done incode b reverse order of assembly."
    */
    
    /*
    Requirements. 8: DIsconnect (free PvPipeline, PvStream, PvDevice memory)
    ○ Hint: Free the memory in the order of mPipeline, mStream(PvStream), mDevice(PvDevice).
    ○ mPipeline = new PvPipeline(aStream). new <-> delete (dynamic memory allocation).
    */
    if ( mPipeline != NULL )
    {
        cout << "Delete Pipeline" << endl;
        delete mPipeline;

        if ( mStream != NULL )
        {
            cout << "Closing stream" << endl;
            mStream->Close();
            PvStream::Free( mStream );

            if ( mDevice != NULL )
            {
                cout << "Disconnecting device" << endl;
                mDevice->Disconnect();
                PvDevice::Free( mDevice );
            }
            else   return false;
        }
        else return false;

    }
    else return false;

    return true;
}

PvDevice* CamThread::ConnectToDevice( const char* aConnectionID)
{
    PvDevice *lDevice;
    PvResult lResult;

    cout << "Connecting to device." << endl;

    /*
    Requirements. 3: Connect to the GigE Vision or USB3 Vision device (using the static factory method).
    ○ GigE Vision and USB3 Vision are represented by the PvDeviceGEV and PvDeviceU3V classe and share a parent class, PvDevice.
    */    
    /* Todo */
    lDevice = PvDevice::CreateAndConnect(aConnectionID,&lResult);
    if ( lDevice == NULL )
    {
        cout << "Unable to connect to device: "
        << lResult.GetCodeString().GetAscii()
        << " ("
        << lResult.GetDescription().GetAscii()
        << ")" << endl;
    }


    return lDevice;
    //A pointer to the PvDevice object is returned to main() and can now be used to control the device and
    //initiate streaming
}

PvStream* CamThread::OpenStream( const PvString &aConnectionID )
{
    PvStream *lStream;
    PvResult lResult;

    // Open stream to the GigE Vision
    cout << "Opening stream from device." << endl;

    /*
    Requirements. 4: Open PvStream. PvStream initiates PvBuffer.
    ○ Hint: See the CamThread::ConnectToDevice()
    */ 
    /* Todo */
    lStream =  PvStream::CreateAndOpen( aConnectionID, &lResult );

    //A pointer to the PvStream object is returned to main() and can now be used to receive images as PvBuffer
    //objects.
    
    if ( lStream == NULL )
    {
        cout << "Unable to stream from device. "
            << lResult.GetCodeString().GetAscii()
            << " ("
            << lResult.GetDescription().GetAscii()
            << ")"
            << endl;
    }

    return lStream;
}

PvStreamGEV* CamThread::ConfigureStream( PvDevice *aDevice, PvStream *aStream  )
{
    /* If using a GigE Vision device, configure GigE Vision-specific streaming parameters 
    (set a destination IP address for the image stream, PvBuffer).
    */
    PvStreamGEV* lStreamGEV = NULL;
    
    /*
    Requirements. 5: cast PvDevice to GigE Vision class (PvDeviceGEV).
    ○ Hint: PvDevice(parent) to PvDevicGEV(child)
    */
    /* Todo */
    PvDeviceGEV* lDeviceGEV = dynamic_cast<PvDeviceGEV *>( aDevice );
    
    if ( lDeviceGEV != NULL )
    {
        /*
        Requirements. 6: cast PvStream to GigE Vision class (PvStreamGEV).
        ○ Hint: PvStream(parent) to PvStreamGEV(child)
        */  
        /* Todo */
        lStreamGEV =static_cast<PvStreamGEV *>( aStream );

        /*
        If you want optimal performance over Gibabit Ethernet, 
        it is necessary to negotiate the possible packet size for the connection (NegotiatePacketSize: soft-code).
        Or not, if you prefer to set the packet size based on your system, use hard-code.
        */
        lDeviceGEV->NegotiatePacketSize();

        /*
        Requirements. 7: Configure device streaming destination
        ○ Hint: SetStreamDestination( PvStream Local IP Address, PvStreamGEV Local Port )
        */
        /* Todo */
        lDeviceGEV-> SetStreamDestination( lStreamGEV->GetLocalIPAddress(), lStreamGEV->GetLocalPort() );
    }

    return lStreamGEV;
}

PvPipeline *CamThread::MakePipeline( PvDeviceGEV *aDevice, PvStream *aStream)
{
    PvResult lResult;

    //Get payload (pixel bit-depth) size from device.
    uint32_t lSize = aDevice->GetPayloadSize();

    PvPipeline *mPipeline;

    mPipeline = new PvPipeline(aStream);

    // Set size and count.
    mPipeline->SetBufferSize(static_cast<uint32_t>(lSize)); // aDevice payload
    mPipeline->SetBufferCount( 16 );
    lResult = mPipeline->Start();
    if (!lResult.IsOK())
    {
        cout << "Unable to start pipeline" << endl;
    }

    // Avoid receiving images with errors.
    PvGenBoolean *lRequestMissingPackets = dynamic_cast<PvGenBoolean *>(aStream->GetParameters()->GetBoolean("RequestMissingPackets"));
    if ((lRequestMissingPackets != NULL) && lRequestMissingPackets->IsAvailable())
    {
        // Disabling request missing packets. lResult =
        lRequestMissingPackets->SetValue(false);
    }

    return mPipeline;
}

void CamThread::CaptureAndAppendImages(uint32_t capture_cnt)
{

     FILE *file;

     file=fopen("/home/nano2/Desktop/build-Camera_Grabber-Desktop-Debug/test2.bin","wb");


    PvGenParameterArray *deviceParams = mDeviceGEV->GetParameters();
    PvGenCommand *startAcquisition = dynamic_cast<PvGenCommand *>(deviceParams->Get("AcquisitionStart"));
    PvGenCommand *stopAcquisition = dynamic_cast<PvGenCommand *>(deviceParams->Get("AcquisitionStop"));

    cout << "Enabling streaming and sending AcquisitionStart command." << endl;
    mDeviceGEV->StreamEnable();
    startAcquisition->Execute();
    PvBuffer* Buffer=nullptr;

    cout << endl << "<Start>" << endl;

    for (int i=0;i<capture_cnt;i++)
    {
        PvResult result;
        PvBuffer *buffer = nullptr;



        if (mStreamGEV->IsOpen() && mPipeline->IsStarted())
        {
            result = mPipeline->RetrieveNextBuffer(&buffer, 0xFFFFFFFF, &result);

            if (!result.IsOK())
            {
                cout << "Failed to retrieve buffer." << endl;
                continue;
            }
        }

        uint32_t width = buffer->GetImage()->GetWidth();
        uint32_t height = buffer->GetImage()->GetHeight();

        if (width != 0)
        {
            uint32_t size = buffer->GetSize();
            cv::Mat img_C1( height, width, CV_8UC1 );
            memcpy( img_C1.data, Buffer->GetDataPointer(), size );

            if ( width > 320 )  // RGB
            {
                cv::Mat img( 964, 1288, CV_8UC3 );
                cv::cvtColor( img_C1, img, cv::COLOR_BayerGB2BGR);

               fwrite( img.data, sizeof(uchar), img.cols * img.rows * 3, file );



            }
            else // Thermal
            {
               fwrite( img_C1.data, sizeof(uchar), img_C1.cols * img_C1.rows, file );


            }




            result = mPipeline->ReleaseBuffer(buffer);
            if (!result.IsOK())
            {
                cout << "Failed to release buffer." << endl;
            }

        }
    }


    fclose(file);

    cout << "Capture and append completed." << endl;
}



QImage CamThread::mat_to_qimage_cpy(cv::Mat const &mat,
                         QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows,mat.step, format).copy();
}

cv::Mat CamThread::qimage_to_mat_cpy(QImage const &img, int format)
{
    /*
    Requirements. 10: qimage -> opencv matrix
    ○ Hint: https://stackoverflow.com/questions/11886123/how-to-convert-qimage-to-opencv-mat 
    */
    return cv::Mat (img.height(), img.width(), CV_8UC3, (cv::Scalar*)img.scanLine(0)).clone();

}



QImage CamThread::Buffer_to_qimage_cpy(PvBuffer* const &buffer, QImage::Format format, uint32_t size)
{

    //Requirements. 9: Buffer to qimage (copy).
    //○ Hint: const_cast<>(buffer->GetDataPointer()). Think about "How to get image width, height from buffer?"
    uint32_t lwidth = 0, lheight = 0;
    lwidth=buffer->GetImage()->GetWidth();
    lheight=buffer->GetImage()->GetHeight();


    return QImage(const_cast<uint8_t*>(buffer->GetDataPointer()),lwidth ,lheight , format).copy();

}

