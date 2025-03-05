
option(USE_QT "sense voice: use Qt Framework or not"      OFF)

set(PROJ_LIB_NAME svcore)
set(PROJ_LIB_MAJOR_VERSION 1)
set(PROJ_LIB_MINOR_VERSION 1)
set(PROJ_LIB_VERSION "${PROJ_LIB_MAJOR_VERSION}.${PROJ_LIB_MINOR_VERSION}")

if (USE_QT)
    message(STATUS "use Qt Framework (USE_QT=ON)")
    include(${PROJECT_SOURCE_DIR}/cmake/qt_support.cmake)
else()
    message(STATUS "not using Qt Framework (USE_QT=OFF)")
endif(USE_QT)

aux_source_directory(src SV_SRCS)

if (BUILD_SHARED_LIBS)
    add_library(${PROJ_LIB_NAME} SHARED ${SV_SRCS})
else()
    add_library(${PROJ_LIB_NAME} STATIC ${SV_SRCS})
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


# Build library for Qt
if (USE_QT)
    svcore_qt_build()
    # Add macro for compilation
    add_compile_definitions(USE_QT5)
endif(USE_QT)

# Build pybind11 library
if (BUILD_PYBIND11)
    include(${PROJECT_SOURCE_DIR}/cmake/pybind11.cmake)
    pybind11_build()
    add_compile_definitions(USE_PYBIND11)
endif(BUILD_PYBIND11)

# CLI Demo

add_executable(sense-voice-cli main.cc)
target_link_libraries(sense-voice-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(sense-voice-cli PUBLIC include)


# Test

add_executable(test-with-cli test/test.cpp)
target_link_libraries(test-with-cli ${PROJ_LIB_NAME} ggml)
target_include_directories(test-with-cli PUBLIC include)


