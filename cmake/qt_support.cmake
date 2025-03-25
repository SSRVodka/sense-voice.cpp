
macro(svcore_qt_build)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# export symbols
add_compile_definitions(ASRLIB_EXPORT)

set(SV_MOC_H ${PROJECT_SOURCE_DIR}/sense-voice/include/asr_handler.hpp)

target_sources(${PROJ_LIB_NAME} PUBLIC ${SV_MOC_H})

set_target_properties(${PROJ_LIB_NAME} PROPERTIES
    VERSION ${PROJ_LIB_VERSION}_qt5
    SOVERSION ${PROJ_LIB_VERSION}
)

target_link_libraries(${PROJ_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

# use auto-moc here to avoid problems as a subproject
set_target_properties(${PROJ_LIB_NAME} PROPERTIES AUTOMOC ON)

endmacro(svcore_qt_build)
