# Project declaration
TEMPLATE = lib
CONFIG += plugin debug_and_release

# Target name
TARGET = $$qtLibraryTarget(ParametersWidgets)

# Qt modules required
QT += widgets designer

# Files declaration
HEADERS += \
    Config.h \
    EulerFrameParameter.h \
    EulerFrameParameterWidget.h \
    GroupParameter.h \
    IParametrable.h \
    Matrix4x4Parameter.h \
    Matrix4x4ParameterWidget.h \
    ParameterWidget.h \
    ParametersWidgetCollectionPlugin.h \
    ParametersWidgetCollection_global.h \
    ParameterBase.h \
    ListParameterBase.h \
    BoolParameter.h \
    BoolParameterWidget.h \
    NumericalParameter.h \
    NumericalParameterWidget.h \
    StringParameter.h \
    StringParameterWidget.h \
    ListParameter.h \
    ListParameterWidget.h \
    ParametersView.h \
    BoolParameterWidgetPlugin.h \
    NumericalParameterWidgetPlugin.h \
    StringParameterWidgetPlugin.h \
    ListParameterWidgetPlugin.h \
    ParametersViewPlugin.h \
    UnknownParameterWidget.h \
    Vector3DParameter.h \
    Vector3DParameterWidget.h

SOURCES += \
    Config.cpp \
    EulerFrameParameter.cpp \
    EulerFrameParameterWidget.cpp \
    GroupParameter.cpp \
    ListParameterBase.cpp \
    Matrix4x4Parameter.cpp \
    Matrix4x4ParameterWidget.cpp \
    ParameterBase.cpp \
    BoolParameter.cpp \
    BoolParameterWidget.cpp \
    NumericalParameter.cpp \
    NumericalParameterWidget.cpp \
    ParameterWidget.cpp \
    ParametersWidgetCollectionPlugin.cpp \
    StringParameter.cpp \
    StringParameterWidget.cpp \
    ListParameterWidget.cpp \
    ParametersView.cpp \
    BoolParameterWidgetPlugin.cpp \
    NumericalParameterWidgetPlugin.cpp \
    StringParameterWidgetPlugin.cpp \
    ListParameterWidgetPlugin.cpp \
    ParametersViewPlugin.cpp \
    UnknownParameterWidget.cpp \
    Vector3DParameter.cpp \
    Vector3DParameterWidget.cpp

#RESOURCES +=
#LIBS        += -L. -lListParameterWidget -lParametersView -lBoolParameterWidget -lStringParameterWidget -lNumericalParameterWidget

# For installation as a Qt Designer plugin
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

# Exporting symbols to Windows (required with MSVC)
DEFINES += PARAMETERSWIDGETCOLLECTION_LIBRARY

# For installation as a Qt Designer plugin in the Designer of Qt Qt Creator
# Not do here. Let the installer doing it
#CONFIG(ReleaseBuild) {
#    QMAKE_POST_LINK += $$quote(cmd /C copy /Y \"$$OUT_PWD\\release\\$${TARGET}.dll\" \"C:\\Qt\\Tools\\QtCreator\\bin\\plugins\\designer\\\")
#}
