
macro(svcore_qt_build)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# export symbols (not appear in parent project)
add_compile_definitions(ASRLIB_EXPORT)

# compile-time macro (to be visible to parent projects)
target_compile_definitions(${PROJ_LIB_NAME} PUBLIC ASRLIB_USE_QT5=ON)

set(SV_MOC_H ${PROJECT_SOURCE_DIR}/sense-voice/include/asr_handler.hpp)

target_sources(${PROJ_LIB_NAME} PUBLIC ${SV_MOC_H})

set_target_properties(${PROJ_LIB_NAME} PROPERTIES
    VERSION ${PROJ_LIB_VERSION}.qt5
    SOVERSION ${PROJ_LIB_VERSION}
)

target_link_libraries(${PROJ_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

# use auto-moc here to avoid problems as a subproject
set_target_properties(${PROJ_LIB_NAME} PROPERTIES AUTOMOC ON)

endmacro(svcore_qt_build)
