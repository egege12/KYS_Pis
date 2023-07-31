cmake_minimum_required(VERSION 3.16)

project(KYS_Pis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt5 REQUIRED COMPONENTS QuickControls2)
find_package(Qt5 REQUIRED COMPONENTS Quick)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5 COMPONENTS Core SerialPort REQUIRED)

add_executable(appKYS_Pis
    qml.qrc
    main.cpp
    endPointsClass.h
    workerObject.h
    workerObject.cpp
)

set_target_properties(appKYS_Pis PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set_target_properties(appKYS_Pis PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


target_link_libraries(appKYS_Pis
    PRIVATE Qt5::Quick
)
target_link_libraries(appKYS_Pis PRIVATE Qt5::Multimedia Qt5::Core Qt5::SerialPort)
install(TARGETS appKYS_Pis
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(appKYS_Pis)
    qt_finalize_executable(appKYS_Pis)
endif()
