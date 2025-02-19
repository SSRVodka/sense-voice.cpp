
option(USE_QT "sense voice: use Qt Framework or not"      OFF)

set(PROJ_LIB_NAME svcore)
set(PROJ_LIB_MAJOR_VERSION 1)
set(PROJ_LIB_MINOR_VERSION 1)
set(PROJ_LIB_VERSION "${PROJ_LIB_MAJOR_VERSION}.${PROJ_LIB_MINOR_VERSION}")

if (USE_QT)
message(STATUS "use Qt Framework (USE_QT=ON)")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SV_MOC_H include/asr.hpp)
QT5_WRAP_CPP(SV_MOCd ${SV_MOC_H})

aux_source_directory(src SV_SRCS)

else()
message(STATUS "not using Qt Framework (USE_QT=OFF)")
set(SV_MOC_H "")
set(SV_MOCd "")
set(SV_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/asr_handler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fftsg.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/log-mel-filter-bank.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-cmvn.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-decoder.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-encoder.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-encoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-frontend.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice-frontend.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sense-voice.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/silero-vad.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/silero-vad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ThreadPool.h
)

endif(USE_QT)

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

if (USE_QT)
# Link Qt libraries
target_link_libraries(${PROJ_LIB_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

endif(USE_QT)

# CLI Demo

add_executable(sense-voice-cli main.cc)
target_link_libraries(sense-voice-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(sense-voice-cli PUBLIC include)

if (USE_QT)
target_link_libraries(sense-voice-cli Qt5::Core Qt5::Widgets Qt5::Gui)
endif(USE_QT)

# Test

add_executable(test-with-cli test/test.cpp)
target_link_libraries(test-with-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(test-with-cli PUBLIC include)

if (USE_QT)
target_link_libraries(test-with-cli Qt5::Core Qt5::Widgets Qt5::Gui)
endif(USE_QT)

