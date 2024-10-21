cmake_minimum_required(VERSION 3.19)
project(SNIES_extractor_V2)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_executable(SNIES_extractor_V2 src/Settings.h src/ProgramaAcademico.h src/ProgramaAcademico.cpp src/Consolidado.h src/Consolidado.cpp src/GestorCsv.h src/GestorCsv.cpp src/SNIESController.h src/SNIESController.cpp src/View.h src/View.cpp src/main.cpp)

