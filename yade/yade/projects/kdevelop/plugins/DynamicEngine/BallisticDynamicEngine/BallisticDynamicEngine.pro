# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/DynamicEngine/BallisticDynamicEngine
# Target is a library:  

LIBS += -lRigidBody \
        -rdynamic 
INCLUDEPATH = ../../../plugins/Body/RigidBody \
              ../../../toolboxes/Math 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../plugins/Body/RigidBody/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += BallisticDynamicEngine.hpp 
SOURCES += BallisticDynamicEngine.cpp 
