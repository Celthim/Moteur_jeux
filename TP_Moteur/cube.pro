QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    calendar.cpp \
    mainwindow.cpp \
    quadtree.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    calendar.h \
    mainwindow.h \
    quadtree.h \
    vertexdata.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=
