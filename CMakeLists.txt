cmake_minimum_required(VERSION 3.22)
project(pathtracer_simple)

set(CMAKE_CXX_STANDARD 20)
# We don't need that stuff, we only want to compile the core library, see the OpenVDB components section at
# https://www.openvdb.org/documentation/doxygen/build.html for more information
set(OPENVDB_BUILD_BINARIES OFF)
set(OPENVDB_CORE_STATIC OFF)

if(WIN32)
    # Not yet tested/verified, the final binary is getting to larg for the assembler
    # so we have to increase the optimization level
    # Also make sure to reduce the number of processes, this is memory hungry
    # https://digitalkarabela.com/mingw-w64-how-to-fix-file-too-big-too-many-sections/
    # https://stackoverflow.com/questions/14125007/gcc-string-table-overflow-error-during-compilation
    # -O1 and -O2 are not enough, haven't tested -Os yet
    message(STATUS "Windows detected, enabling large file support")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Os -Wa,-mbig-obj")
endif()

include(FetchContent)

file(GLOB_RECURSE APP_SRC
        src/*.cpp
        src/*.c
)

add_executable(pathtracer_simple ${APP_SRC})


# OpenVDB
# There exists also a package, libopenvdb-dev, but haven't got it to work yet
#find_package(OpenVDB REQUIRED)

FetchContent_Declare(
        openvdb
        GIT_REPOSITORY https://github.com/AcademySoftwareFoundation/openvdb.git
        GIT_TAG v11.0.0
)
message(STATUS "Fetching OpenVDB from repo")
FetchContent_MakeAvailable(openvdb)

message(STATUS "Linking")
target_link_libraries(pathtracer_simple openvdb)

