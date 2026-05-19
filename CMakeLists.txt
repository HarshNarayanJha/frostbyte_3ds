cmake_minimum_required(VERSION 3.19.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/DevkitArm3DS.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(frostbyte_3ds VERSION 0.0.1)
enable_language(ASM C CXX)

set(EXTRA_CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

# remove this flag, causing lsp issues
# [ 25%] Linking CXX executable 3ds_template
# /opt/devkitpro/devkitARM/bin/../lib/gcc/arm-none-eabi/15.1.0/../../../../arm-none-eabi/bin/ld: cannot find 3dsx_crt0.o: No such file or directory
# collect2: error: ld returned 1 exit status
string(REPLACE "-mword-relocations" "" CMAKE_CXX_FLAGS_FILTERED "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_FILTERED} ${DKA_SUGGESTED_CXX_FLAGS_FILTERED} ${EXTRA_CMAKE_CXX_FLAGS}")

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(RES_DIR ${CMAKE_CURRENT_LIST_DIR}/res)

set(GRAPHICS_DIR ${CMAKE_CURRENT_LIST_DIR}/gfx)
set(ROMFS_DIR ${CMAKE_BINARY_DIR}/romfs)
set(GFXBUILD_DIR ${ROMFS_DIR}/gfx)
set(_3DSXTOOL_ROMFS "romfs_assets")

set(APP_BANNER ${RES_DIR}/banner.png)
set(APP_AUDIO ${RES_DIR}/audio.wav)
set(APP_ICON ${RES_DIR}/icon.png)
set(APP_RSF ${RES_DIR}/frostbyte_3ds.rsf)
set(APP_TITLE "Frostbyte 3DS")
set(APP_AUTHOR "harshnj")
set(APP_DESCRIPTION "Save your Christmas! Collect the Snowflakes")

# Note that you must copy the cmake folder and the DevkitArm3DS.cmake file in this directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake) # Add the cmake folder to the modules paths, so that we can use the tools and find_package for ctrulib
include(Tools3DS) # Include all the macros and tools needed for 3ds development.

find_package(CITRO2D REQUIRED)
find_package(CITRO3D REQUIRED)
find_package(CTRULIB REQUIRED)


# later
file(GLOB_RECURSE SOURCE_FILES
    ${SRC_DIR}/*
    # ${INCLUDE_DIR}/*
)


# set(SOURCE_FILES src/main.cpp)

# this generates the .t3x's inside the romfs/gfx folder and also makes sure romfs is included in the binaries
# for that, _3DSXTOOL_ROMFS needs to be set to a target name
# ROMFS_DIR, GFXBUILD_DIR are used inside
generate_t3xs(${_3DSXTOOL_ROMFS}
    ${GRAPHICS_DIR}/sprites.t3s
)

add_executable(frostbyte_3ds ${SOURCE_FILES})
target_link_libraries(frostbyte_3ds 3ds::citro2d 3ds::citro3d 3ds::ctrulib)
target_compile_definitions(frostbyte_3ds PRIVATE)
# target_include_directories(frostbyte_3ds PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# make sure the generated texture headers can be included
target_include_directories(frostbyte_3ds PRIVATE
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/gfx
)

add_3dsx_target(frostbyte_3ds)
add_cci_target(frostbyte_3ds ${APP_RSF} ${APP_BANNER} ${APP_AUDIO})
# add_cia_target(frostbyte_3ds ${APP_RSF} ${APP_BANNER} ${APP_AUDIO})
add_netload_target(netload frostbyte_3ds)
set_property(TARGET frostbyte_3ds PROPERTY CXX_STANDARD 20)
