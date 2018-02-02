TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lGLEW -lglfw -lfreeimage -lfreetype
INCLUDEPATH += /usr/include/freetype2/
SOURCES += main.c

HEADERS += \
    init.h \
    texture.h \
    shader.h \
    menu.h \
    renderer.h \
    input.h \
    cursor.h \
    text.h \
    cvar.h \
    fps.h \
    context_functions.h
