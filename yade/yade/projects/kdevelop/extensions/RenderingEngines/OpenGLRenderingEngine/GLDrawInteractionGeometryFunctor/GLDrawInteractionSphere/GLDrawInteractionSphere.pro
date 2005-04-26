# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./extensions/RenderingEngines/OpenGLRenderingEngine/GLDrawInteractionGeometryFunctor/GLDrawInteractionSphere
# Target is a library:  

LIBS += -lInteractingSphere \
        -rdynamic 
INCLUDEPATH = $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../../plugins/Body/InteractingGeometry/InteractingSphere/$(YADEDYNLIBPATH) \
               ../../../../../plugins/Geometry/CollisionGeometry/InteractingSphere/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += GLDrawInteractionSphere.hpp 
SOURCES += GLDrawInteractionSphere.cpp 
