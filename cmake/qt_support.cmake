
macro(svcore_qt_build)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SV_MOC_H ${PROJECT_SOURCE_DIR}/sense-voice/include/asr_handler.hpp)
QT5_WRAP_CPP(SV_MOCd ${SV_MOC_H})

target_sources(${PROJ_LIB_NAME} PUBLIC ${SV_MOC_H} ${SV_MOCd})

set_target_properties(${PROJ_LIB_NAME} PROPERTIES
    VERSION ${PROJ_LIB_VERSION}_qt5
    SOVERSION ${PROJ_LIB_VERSION}
)

target_link_libraries(${PROJ_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)


endmacro(svcore_qt_build)
