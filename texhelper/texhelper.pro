#-------------------------------------------------
#
# Project created by QtCreator 2012-11-06T15:57:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = texhelper
CONFIG   += console
CONFIG   -= app_bundle


TEMPLATE = app


SOURCES += main.cpp \
    ../algorithms/anyoption.cpp \
    ../algorithms/texweaver.cpp \
    ../algorithms/textile.cpp

HEADERS += \
    ../algorithms/anyoption.h \
    ../algorithms/texweaver.h \
    ../algorithms/textile.h

win32 {
    OPENCVDIR = "../libs/opencv242"
    exists($$OPENCVDIR) {
        DEFINES += USEOPENCV
        INCLUDEPATH += \
            $${OPENCVDIR}/include
        DEPENDPATH += \
            $${OPENCVDIR}/include
        CONFIG(release, debug|release) {
            LIBS += -L$${OPENCVDIR}/lib \
                -lopencv_core242 \
                -lopencv_features2d242 \
                -lopencv_flann242 \
                -lopencv_gpu242 \
                -lopencv_highgui242 \
                -lopencv_imgproc242 \
                -lopencv_legacy242 \
                -lopencv_ml242 \
                -lopencv_nonfree242 \
                -lopencv_objdetect242 \
                -lopencv_photo242 \
                -lopencv_stitching242 \
                -lopencv_ts242 \
                -lopencv_video242 \
                -lopencv_videostab242
        } else {
            LIBS += -L$${OPENCVDIR}/lib \
                -lopencv_core242d \
                -lopencv_features2d242d \
                -lopencv_flann242d \
                -lopencv_gpu242d \
                -lopencv_highgui242d \
                -lopencv_imgproc242d \
                -lopencv_legacy242d \
                -lopencv_ml242d \
                -lopencv_nonfree242d \
                -lopencv_objdetect242d \
                -lopencv_photo242d \
                -lopencv_stitching242d \
                -lopencv_ts242d \
                -lopencv_video242d \
                -lopencv_videostab242d
        }
        message("OpenCV libraries found in $${OPENCVDIR}")
    } else {
        message("OpenCV libraries not found.")
    }
}

