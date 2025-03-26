macro(pybind11_build)

set(PROJ_PYBIND11_LIB_NAME "_asr_module")

add_subdirectory(third-party/pybind11)

# compile-time macro (to be visible to parent projects)
target_compile_definitions(${PROJ_LIB_NAME} PUBLIC ASRLIB_USE_PYBIND11=ON)

pybind11_add_module(${PROJ_PYBIND11_LIB_NAME} ${PROJECT_SOURCE_DIR}/asr_module/wrapper.cpp)
target_link_libraries(${PROJ_PYBIND11_LIB_NAME} PUBLIC svcore)
# TODO: remove it. !Expedient for python package (ONLY linux)
set_target_properties(svcore PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")
set_target_properties(${PROJ_PYBIND11_LIB_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")

endmacro(pybind11_build)
