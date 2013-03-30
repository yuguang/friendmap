APP_NAME = friendtrackerUI

QT += core network

INCLUDEPATH += ../src ${QNX_TARGET}/usr/include/qt4/QtCore
DEPENDPATH += ../src ${QNX_TARGET}/usr/include/qt4/QtCore

CONFIG += qt warn_on cascades10
LIBS += -lbbsystem -lbbplatformbbm -lQtLocationSubset -lbbdata -lbbpim -lbbcascadesmultimedia -lbbcascadespickers -lbb
LIBS += -lbbutility -lbbcascadesmaps -lGLESv1_CM

include(config.pri)
