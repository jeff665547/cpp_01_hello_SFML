cmake_minimum_required(VERSION 3.18)
project(HELLO_SFML CXX)
include(GNUInstallDirs)

if (UNIX)
    file(RELATIVE_PATH relativeRpath
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    )
    set(run_time_exe_dir $<IF:$<PLATFORM_ID:Darwin>,@loader_path,$ORIGIN>)
    set(CMAKE_INSTALL_RPATH "${run_time_exe_dir}" "${run_time_exe_dir}/${relativeRpath}")
endif (UNIX)

option(INSTALL_DEPS "Automatically install the binary file of the shared or static library" ON)

find_package(SFML COMPONENTS graphics CONFIG REQUIRED)

add_executable(main)
target_sources(main
    PRIVATE
        src/main.cpp
)

target_link_libraries(main
    PRIVATE
    sfml-graphics
)

target_compile_features(main
    PRIVATE
        cxx_std_17
)

include(CTest)
add_subdirectory(tests)

# Install the main application (.exe) to the specified directory.
install(TARGETS main
    EXPORT example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the relocatable resource.
set(export_dest_dir "${CMAKE_INSTALL_PREFIX}")
install(
    DIRECTORY resource
    DESTINATION ${export_dest_dir}
)

# Install the binary file of the shared library (e.g. *.dll).
if(INSTALL_DEPS)
    configure_file(
        "cmake/${CMAKE_HOST_SYSTEM_NAME}/bundle.cmake.in" 
        "${CMAKE_BINARY_DIR}/bundle.cmake" @ONLY
    )
    install(
        SCRIPT "${CMAKE_BINARY_DIR}/bundle.cmake"
    )
endif()


# CMake commands: 
# Shared library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-linux-dynamic" -DVCPKG_OVERLAY_TRIPLETS="../../vcpkg-custom-triplets"
# Shared library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
# Static library (UNIX): cmake .. -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-linux-static" -DVCPKG_OVERLAY_TRIPLETS="../../vcpkg-custom-triplets"
# Static library (WIN): cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=../install -DCMAKE_TOOLCHAIN_FILE="../../vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-static"
# cmake --build . --target install