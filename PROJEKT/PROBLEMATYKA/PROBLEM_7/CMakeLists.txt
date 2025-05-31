cmake_minimum_required(VERSION 3.19)
project(Projekt_V2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

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
)

if(IS_GUI_BUILD)
    set(EXTRA_ARGS WIN32 MACOSX_BUNDLE)
else()
    set(EXTRA_ARGS)
endif()

qt_add_executable(Projekt_V2
    ${EXTRA_ARGS}
    ${SOURCES}

)

target_sources(Projekt_V2 PRIVATE
    mainwindow.h
    graf_budowa.h
    dropbutton.h
    algorytmy_tekstowe.h
    reprezentacja_danych.h
    min_cost_max_flow.h
    wypukla_otoczka.h
    huffman.h
)

qt_add_translations(
    TARGETS Projekt_V2
    TS_FILES Projekt_V2_pl_PL.ts
)

target_link_libraries(Projekt_V2
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Projekt_V2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Projekt_V2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
