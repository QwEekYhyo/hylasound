cmake_minimum_required(VERSION 3.16)

project(hylasound LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Multimedia
    LinguistTools
)

qt_standard_project_setup(
    I18N_SOURCE_LANGUAGE en
    I18N_TRANSLATED_LANGUAGES fr
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)
file(GLOB_RECURSE TS_FILES translations/*.ts)

include_directories(include)

if (WIN32)
    set(app_icon_resource_win32 resources/icon.rc)
    qt_add_executable(hylasound ${SOURCES} ${HEADERS} resources/soundboard.qrc ${app_icon_resource_win32})
else()
    qt_add_executable(hylasound ${SOURCES} ${HEADERS} resources/soundboard.qrc)
endif()

set(TRANSLATIONS_QM_DIR ${CMAKE_BINARY_DIR}/translations)
set_source_files_properties(${TS_FILES}
    PROPERTIES OUTPUT_LOCATION ${TRANSLATIONS_QM_DIR})

qt_add_translations(
    TARGETS hylasound
    TS_FILES ${TS_FILES}
    TS_FILE_DIR translations
    INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES}
    SOURCES ${SOURCES}
    QM_FILES_OUTPUT_VARIABLE qm_files
)
install(FILES ${qm_files} DESTINATION ${TRANSLATIONS_QM_DIR})

target_link_libraries(hylasound PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

set_target_properties(hylasound PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
    MACOSX_BUNDLE_BUNDLE_NAME "HylaSound"
)

install(TARGETS hylasound
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (WIN32 OR APPLE)
    qt_generate_deploy_app_script(
        TARGET hylasound
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
        NO_TRANSLATIONS
    )
    install(SCRIPT ${deploy_script})
endif()
