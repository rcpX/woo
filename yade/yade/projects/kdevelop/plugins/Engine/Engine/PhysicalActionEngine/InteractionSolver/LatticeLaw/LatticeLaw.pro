# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Engine/Engine/PhysicalActionEngine/InteractionSolver/LatticeLaw
# Target is a library:  

LIBS += -lParticleParameters \
        -lLatticeBeamParameters \
        -lLatticeNodeParameters \
        -lForce \
        -rdynamic 
INCLUDEPATH += $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../../../plugins/Data/Body/PhysicalParameters/ParticleParameters/$(YADEDYNLIBPATH) \
               ../../../../../../plugins/Data/Body/PhysicalParameters/LatticeBeamParameters/$(YADEDYNLIBPATH) \
               ../../../../../../plugins/Data/Body/PhysicalParameters/LatticeNodeParameters/$(YADEDYNLIBPATH) \
               ../../../../../../plugins/Data/PhysicalAction/Force/$(YADEDYNLIBPATH) \
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
HEADERS += LatticeLaw.hpp 
SOURCES += LatticeLaw.cpp 
