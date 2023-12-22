TEMPLATE = app
CONFIG += c++17
QT += core network gui widgets
CONFIG += no_keywords
TARGET = ip-camera

QMAKE_LFLAGS += -Wl,-rpath-link,/root/rpi-qt/sysroot/usr/lib/aarch64-linux-gnu/

# Point your PKG_CONFIG_PATH environment variable to the
# libcamera install path libcamera.pc file ($prefix/lib/pkgconfig/libcamera.pc)
#LIBS += -lstdc++

LIBS += -L/root/rpi-qt/sysroot/lib/aarch64-linux-gnu
LIBS += -lcamera -lcamera-base
LIBS += -levent_pthreads

# Define the include directories for the external libraries
#INCLUDEPATH += /usr/local/include/libcamera
INCLUDEPATH += /root/rpi-qt/sysroot/usr/include/libcamera
INCLUDEPATH += /root/rpi-qt/sysroot/usr/include/event2

SOURCES += main.cpp \
    LibCamera.cpp

HEADERS += LibCamera.h

target.path = /home/pi/dual-cam
INSTALLS += target


