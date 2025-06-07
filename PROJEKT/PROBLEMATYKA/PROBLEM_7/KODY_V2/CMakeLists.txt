cmake_minimum_required(VERSION 3.19)
project(HoBeerSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Svg SvgWidgets)

qt_standard_project_setup()

set(IS_GUI_BUILD OFF)
if (DEFINED ENV{GUI_MODE})
    set(IS_GUI_BUILD ON)
endif()

set(SOURCES
    main.cpp
    mainwindow.cpp
    min_cost_max_flow.cpp
    algorytmy_tekstowe.cpp
    graf_budowa.cpp
    dropbutton.cpp
    huffman.cpp
    graphwidget.cpp
    wypukla_otoczka.cpp
)

if(WIN32)
    set(WINDOWS_ICON_RESOURCE resources.rc)
endif()

if(IS_GUI_BUILD)
    set(EXTRA_ARGS WIN32 MACOSX_BUNDLE)
else()
    set(EXTRA_ARGS)
endif()

qt_add_executable(HoBeerSystem
    ${EXTRA_ARGS}
    ${SOURCES}
    ${WINDOWS_ICON_RESOURCE}
)

target_sources(HoBeerSystem PRIVATE
    mainwindow.h
    graf_budowa.h
    dropbutton.h
    algorytmy_tekstowe.h
    reprezentacja_danych.h
    min_cost_max_flow.h
    wypukla_otoczka.h
    huffman.h
    graphwidget.h
)

qt_add_translations(
    TARGETS HoBeerSystem
    TS_FILES HoBeerSystem_pl_PL.ts
)

target_link_libraries(HoBeerSystem
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Svg
        Qt6::SvgWidgets
)

include(GNUInstallDirs)
install(TARGETS HoBeerSystem
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET HoBeerSystem
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
