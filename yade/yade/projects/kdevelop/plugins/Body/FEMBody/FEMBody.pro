# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Body/FEMBody
# Target is a library:  

LIBS += -lAABB \
        -lPolyhedron \
        -rdynamic 
INCLUDEPATH = ../../../plugins/GeometricalModel/Polyhedron \
              ../../../plugins/BoundingVolume/AABB \
              ../../../toolboxes/Math 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../plugins/BoundingVolume/AABB/$(YADEDYNLIBPATH) \
               ../../../plugins/GeometricalModel/Polyhedron/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += FEMBody.hpp 
SOURCES += FEMBody.cpp 
