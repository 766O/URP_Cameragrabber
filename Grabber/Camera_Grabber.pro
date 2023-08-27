#-------------------------------------------------
#
# Project created by QtCreator 2020-01-16T17:43:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Embedded_Grabber
TEMPLATE = app

TARGET    = QtCuda
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    camthread.cpp

HEADERS += \
        mainwindow.h \
    camthread.h

FORMS += \
        mainwindow.ui

LIBS += \
        -L/opt/pleora/ebus_sdk/linux-aarch64-arm/lib -lEbTransportLayerLib -lEbUtilsLib -lPtConvertersLib -lPtUtilsLib -lPvAppUtils \
        -lPvBase -lPvBuffer -lPvCameraBridge -lPvDevice -lPvGUI -lPvGenICam -lPvPersistence -lPvSerial -lPvStream \
        -lPvSystem -lPvTransmitter -lPvVirtualDevice -lSimpleImagingLib \
        -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio \
        -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui


INCLUDEPATH += $$/opt/pleora/ebus_sdk/linux-aarch64-arm/include
DEPENDPATH += $$/opt/pleora/ebus_sdk/linux-aarch64-arm/include



INCLUDEPATH += \
        -I/usr/include/opencv4/opencv2/

LIBS += \
        -L/usr/lib/aarch64-linux-gnu -lopencv_core -lopencv_calib3d -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_imgcodecs \
        -lopencv_highgui -lopencv_ml -lopencv_photo -lopencv_objdetect -lopencv_stitching  \
        -lopencv_video -lopencv_videoio -lopencv_imgproc





#win32:CONFIG(release, debug|release): LIBS += -L$$/usr/local/lib/python3.6/dist-packages/torch/lib/release/ -lc10_cuda
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/local/lib/python3.6/dist-packages/torch/lib/debug/ -lc10_cuda
#else:unix: LIBS += -L$$/usr/local/lib/python3.6/dist-packages/torch/lib/ -lc10 -lc10_cuda -lcaffe2 -lcaffe2_detectron_ops_gpu \
#        -lcaffe2_gpu -lcaffe2_module_test_dynamic -lcaffe2_observers -lfoxi -lfoxi_dummy -lonnxifi -lonnxifi_dummy \
#        -lshm -lthnvrtc -ltorch -ltorch_python

#INCLUDEPATH += $$/usr/local/lib/python3.6/dist-packages/torch/include
#DEPENDPATH += $$/usr/local/lib/python3.6/dist-packages/torch/include


#INCLUDEPATH += $$/usr/local/lib/python3.6/dist-packages/torch/include/torch/csrc/api/include
#DEPENDPATH += $$/usr/local/lib/python3.6/dist-packages/torch/include/torch/csrc/api/include



INCLUDEPATH += $$/usr/include/python3.6
DEPENDPATH += $$/usr/include/python3.6

INCLUDEPATH += $$/usr/local/cuda/include
DEPENDPATH += $$/usr/local/cuda/include

########################cuda
#CUDA_SOURCES += correlation_cuda_kernel.cu

# Path to cuda toolkit install
CUDA_DIR = /usr/local/cuda
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64
# GPU architecture
CUDA_ARCH = sm_60
# NVCC flags
NVCCFLAGS = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
# Path to libraries
LIBS += -lcudart -lcuda
# join the includes in a line
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS $$CUDA_INC $$LIBS ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
cuda.dependcy_type = TYPE_C
cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS      ${QMAKE_FILE_NAME}

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cuda

