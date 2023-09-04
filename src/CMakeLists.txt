cmake_minimum_required(VERSION 3.5)

project(toDoApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    todoapp.cpp
    todoapp.h
    todoapp.ui
    task.h
    task.cpp
    editdialog.cpp
    editdialog.h
    editdialog.ui
)

add_library(
    "rs_task"
    ${PROJECT_SOURCES}
)

target_link_libraries(
    "rs_task"
    PUBLIC Qt6::Widgets
)

qt_add_executable(toDoApp
    MANUAL_FINALIZATION
    main.cpp
)

target_link_libraries(toDoApp PRIVATE rs_task)

set_target_properties(toDoApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS toDoApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(tests)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(toDoApp)
endif()