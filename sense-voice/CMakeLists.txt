
set(PROJ_LIB_NAME svcore)
set(PROJ_LIB_MAJOR_VERSION 1)
set(PROJ_LIB_MINOR_VERSION 1)
set(PROJ_LIB_VERSION "${PROJ_LIB_MAJOR_VERSION}.${PROJ_LIB_MINOR_VERSION}")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SV_MOC_H include/asr.hpp)
QT5_WRAP_CPP(SV_MOCd ${SV_MOC_H})

aux_source_directory(src SV_SRCS)

if (BUILD_SHARED_LIBS)
    add_library(${PROJ_LIB_NAME} SHARED ${SV_SRCS} ${SV_MOCd} ${SV_MOC_H})
else()
    add_library(${PROJ_LIB_NAME} STATIC ${SV_SRCS} ${SV_MOCd} ${SV_MOC_H})
endif(BUILD_SHARED_LIBS)

set_target_properties(${PROJ_LIB_NAME} PROPERTIES
    VERSION ${PROJ_LIB_VERSION}
    SOVERSION ${PROJ_LIB_VERSION}
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    list(APPEND ggml stdc++fs)
endif()

add_subdirectory(third-party/ggml)

target_include_directories(${PROJ_LIB_NAME} PUBLIC include)
target_include_directories(${PROJ_LIB_NAME} PRIVATE src)
target_link_libraries(${PROJ_LIB_NAME} ggml)
# Link Qt libraries
target_link_libraries(${PROJ_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)


# CLI Demo

add_executable(sense-voice-cli main.cc)
target_link_libraries(sense-voice-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(sense-voice-cli PUBLIC include)
target_link_libraries(sense-voice-cli Qt5::Core Qt5::Widgets Qt5::Gui)

# Test

add_executable(test-with-cli test/test.cpp)
target_link_libraries(test-with-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(test-with-cli PUBLIC include)
target_link_libraries(test-with-cli Qt5::Core Qt5::Widgets Qt5::Gui)

