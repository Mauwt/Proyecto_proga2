cmake_minimum_required(VERSION 3.24)
project(Proyecto_Progra2)

set(CMAKE_CXX_STANDARD 17)

#add_executable(Proyecto_Progra2 main.cpp source/CAlumno.cpp headers/CAlumno.h source/CMenu.cpp headers/CMenu.h source/CSeccion.cpp headers/CSeccion.h source/CEvaluacion.cpp headers/CEvaluacion.h)

file(GLOB_RECURSE SRC_FILES source/*.cpp)
add_executable(Proyecto_Progra2 main.cpp  ${SRC_FILES})
include_directories( include/)
target_include_directories(Proyecto_Progra2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers )