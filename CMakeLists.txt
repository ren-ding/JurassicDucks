
#####       Build file for JurassicDucks

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

# The app
project(JurassicDucks)


# QT
set(QT_USE_QTOPENGL TRUE)
# This is necessary on MS Windows, doesn't hurt on others
set(QT_USE_QTMAIN TRUE)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

# OpenGL
find_package(OpenGL REQUIRED)


set(main_SRC
    main.cpp
    jduckswindow.cpp
    jduckswidget.cpp
    jdUtility.cpp
    jduck.cpp
    jducks.cpp
    jdcamera.cpp
    jdalgorithm.cpp
    jdplayer.cpp
    jdlight.cpp
    jdtext.cpp
    jdreaderwriter.cpp
    jdflockdialog.cpp
    jdgpushader.cpp
    jdmap.cpp
    jdtile.cpp
    jdtree.cpp
    jdtrees.cpp
)
# For a QT app we have to run MOC over headers too
set(main_QTCLASS
    jduckswindow.h
    jduckswidget.h
    jdUtility.h
    jduck.h
    jducks.h
    jdcamera.h
    jdalgorithm.h
    jdplayer.h
    jdlight.h
    jdtext.h
    jdreaderwriter.h
    Vec2.h
    Vec3.h
    Vec4.h
    headers.h
    jdfactors.h
    jdflockdialog.h
    jdgpushader.h
    jdmap.h
    jdtile.h
    jdtree.h
    jdtrees.h
)
qt4_wrap_cpp(main_MOC ${main_QTCLASS})


if (APPLE)
    set(EXE_TYPE MACOSX_BUNDLE)
else ()
    set(EXE_TYPE WIN32)
endif ()

add_executable(JurassicDucks ${EXE_TYPE}
	${main_SRC}
	${main_MOC}
)

target_link_libraries(JurassicDucks ${QT_LIBRARIES})

include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(JurassicDucks ${OPENGL_LIBRARIES})


