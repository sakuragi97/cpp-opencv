QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colordetector.cpp \
    colordetectorcontroller.cpp \
    histogram1d.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow2.cpp \
    morphofeatures.cpp

HEADERS += \
    colordetector.h \
    colordetectorcontroller.h \
    histogram1d.h \
    mainwindow.h \
    mainwindow2.h \
    morphofeatures.h

FORMS += \
    mainwindow.ui \
    mainwindow2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_calib3d480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_core480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_dnn480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_features2d480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_flann480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_gapi480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_highgui480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_imgcodecs480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_imgproc480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_ml480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_objdetect480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_photo480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_stitching480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_video480.dll
LIBS += C:\\OpenCV\\opencv\\build\\install\\x64\\mingw\\bin\\libopencv_videoio480.dll

INCLUDEPATH += C:\\OpenCV\\opencv\\build\\include
DEPENDPATH += C:\\OpenCV\\opencv\\build\\include

RESOURCES += \
    resource.qrc
