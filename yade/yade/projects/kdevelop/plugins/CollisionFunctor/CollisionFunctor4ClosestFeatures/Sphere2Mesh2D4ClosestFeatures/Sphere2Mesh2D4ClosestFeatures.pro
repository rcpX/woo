# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/CollisionFunctor/CollisionFunctor4ClosestFeatures/Sphere2Mesh2D4ClosestFeatures
# Target is a library:  

LIBS += -lMesh2D \
        -lSphere \
        -lM3D \
        -lConstants \
        -lSerialization \
        -lClosestFeatures \
        -rdynamic 
INCLUDEPATH = ../../../../plugins/GeometricalModel/Mesh2D \
              ../../../../plugins/GeometricalModel/Sphere \
              ../../../../plugins/InteractionModel/ClosestFeatures \
              ../../../../yade \
              ../../../../toolboxes/Math/M3D \
              ../../../../toolboxes/Math/Constants \
              ../../../../toolboxes/Libraries/Serialization 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../plugins/GeometricalModel/Mesh2D/$(YADEDYNLIBPATH) \
               ../../../../plugins/GeometricalModel/Sphere/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Math/M3D/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Math/Constants/$(YADEDYNLIBPATH) \
               ../../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../../plugins/InteractionModel/ClosestFeatures/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Sphere2Mesh2D4ClosestFeatures.hpp 
SOURCES += Sphere2Mesh2D4ClosestFeatures.cpp 
