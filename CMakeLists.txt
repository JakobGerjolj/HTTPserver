cmake_minimum_required(VERSION 3.16)

project(HTTPserver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS HttpServer)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appHTTPserver
    main.cpp
)

qt_add_qml_module(appHTTPserver
    URI HTTPserver
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    SOURCES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHTTPserver PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHTTPserver
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHTTPserver
    PRIVATE Qt6::Quick
    Qt6::Network
    Qt6::WebSockets
    Qt6::HttpServer
)

include(GNUInstallDirs)
install(TARGETS appHTTPserver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
