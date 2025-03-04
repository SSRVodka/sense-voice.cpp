
macro(svcore_qt_build)

set(PROJ_QT_LIB_NAME ${PROJ_LIB_NAME}_qt5)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SV_MOC_H qt_support/asr.hpp)
QT5_WRAP_CPP(SV_MOCd ${SV_MOC_H})

if (BUILD_SHARED_LIBS)
    add_library(${PROJ_QT_LIB_NAME} SHARED ${SV_SRCS} ${SV_MOC_H} ${SV_MOCd})
else()
    add_library(${PROJ_QT_LIB_NAME} STATIC ${SV_SRCS} ${SV_MOC_H} ${SV_MOCd})
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJ_QT_LIB_NAME} PROPERTIES
    VERSION ${PROJ_LIB_VERSION}
    SOVERSION ${PROJ_LIB_VERSION}
)

target_include_directories(${PROJ_QT_LIB_NAME} PUBLIC include)
target_include_directories(${PROJ_QT_LIB_NAME} PRIVATE src)
target_include_directories(${PROJ_QT_LIB_NAME} PUBLIC qt_support)
target_link_libraries(${PROJ_QT_LIB_NAME} ggml)
target_link_libraries(${PROJ_QT_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)


endmacro(svcore_qt_build)
