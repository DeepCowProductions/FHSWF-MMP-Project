QT += qml quick widgets opengl multimedia

CONFIG += c++11

SOURCES += src/main.cpp \
    src/glcore/glbody.cpp \
    src/glcore/glcolorrgba.cpp \
    src/glcore/glesrenderer.cpp \
    src/glcore/glitem.cpp \
    src/glcore/glpoint.cpp \
    src/glcore/myglitem.cpp \
    src/glcore/objloader.cpp \
    src/glcore/shaderdebugger.cpp \
    src/globjects/glcube.cpp \
    src/globjects/glfrustum.cpp \
    src/globjects/glmouseray.cpp \
    src/globjects/glspaceship.cpp \
    src/globjects/glsphere.cpp \
    src/sound/soundengine.cpp \
    src/game/gameengine.cpp \
    src/game/gamesceen.cpp \
    src/globjects/glskybox.cpp \
    src/globjects/glskysphere.cpp \
    src/game/glskysphererenderer.cpp \
    src/glcore/skyboxrenderer.cpp \
    src/game/bullet.cpp \
    src/game/gameentity.cpp \
    src/game/smallenemy.cpp \
    src/globjects/glbullet.cpp \
    src/game/spaceship.cpp

RESOURCES += qml.qrc \
    shaders.qrc \
    sounds.qrc \
    models.qrc \
    fonts.qrc \
    textures.qrc \
    img.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/glcore/glbody.h \
    src/glcore/glcolorrgba.h \
    src/glcore/gldefines.h \
    src/glcore/glesrenderer.h \
    src/glcore/glitem.h \
    src/glcore/glpoint.h \
    src/glcore/myglitem.h \
    src/glcore/objloader.h \
    src/glcore/shaderdebugger.h \
    src/globjects/glcube.h \
    src/globjects/glfrustum.h \
    src/globjects/glmouseray.h \
    src/globjects/glspaceship.h \
    src/globjects/glsphere.h \
    src/sound/soundengine.h \
    src/game/gameengine.h \
    src/game/gamesceen.h \
    src/globjects/glskybox.h \
    src/globjects/glskysphere.h \
    src/game/glskysphererenderer.h \
    src/glcore/skyboxrenderer.h \
    src/game/bullet.h \
    src/game/gameentity.h \
    src/game/smallenemy.h \
    src/globjects/glbullet.h \
    src/globjects/spaceship.h
