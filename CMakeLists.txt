cmake_minimum_required(VERSION 3.16)

project(Tasker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tasker main.cpp
    taskslist.h taskslist.cpp
    task.h task.cpp
    taskclass.h taskclass.cpp)

include(GNUInstallDirs)
install(TARGETS Tasker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
