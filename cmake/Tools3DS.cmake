############################################################################
# Various macros for 3DS homebrews tools
#
# -----------------------------------------------------------------------------
# Texture (tex3ds) support
#
# This module provides helpers for converting tex3ds source files (.t3s)
# into Nintendo 3DS texture binaries (.t3x). The generated textures can be
# either embedded into the executable as binary objects or placed into RomFS
# for runtime loading (e.g. via citro2d).
#
# Tools:
#   TEX3DS
#     Path to the tex3ds executable. If not set, it will be searched for in ${DEVKITPRO/tools/bin.
#
# Output layout:
#   Embedded mode:
#     - .t3x files are converted and embedded as binary objects
#     - Corresponding headers are generated in the build directory
#     - Symbols follow the standard bin2o naming scheme
#
#   RomFS mode:
#     - .t3x files are generated under: ${CMAKE_BINARY_DIR}/romfs/gfx
#     - Textures are loaded at runtime using paths such as: romfs:/gfx/<name>.t3x
#
# Macros and functions:
#   add_t3x(OUTPUT INPUT)
#     Compile a single .t3s file into a .t3x file and generate its header.
#
#   generate_t3xs(t3s_files...)
#     Compile one or more .t3s files into .t3x S
#     graphics directory.
#
#   add_t3x_library(target t3s_files...)
#     Compile and embed .t3x files into a binary library suitable for linking
#     into an executable.
#
#   target_embed_t3x(target t3s_files...)
#     Convenience macro to embed one or more textures directly into a target
# -----------------------------------------------------------------------------
#
#
# add_3dsx_target
# ^^^^^^^^^^^^^^^
#
# This macro has two signatures :
#
# ## add_3dsx_target(target [NO_SMDH])
#
# Adds a target that generates a .3dsx file from `target`. If NO_SMDH is specified,
# no .smdh file will be generated.
#
# You can set the following variables to change the SMDH file :
#
# * APP_TITLE is the name of the app stored in the SMDH file (Optional)
# * APP_DESCRIPTION is the description of the app stored in the SMDH file (Optional)
# * APP_AUTHOR is the author of the app stored in the SMDH file (Optional)
# * APP_ICON is the filename of the icon (.png), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - $(target).png
#     - icon.png
#     - $(libctru folder)/default_icon.png
#
# ## add_3dsx_target(target APP_TITLE APP_DESCRIPTION APP_AUTHOR [APP_ICON])
#
# This version will produce the SMDH with the values passed as arguments.
# The APP_ICON is optional and follows the same rule as the other version of
# `add_3dsx_target`.
#
# add_cia_target(target RSF IMAGE SOUND [APP_TITLE APP_DESCRIPTION APP_AUTHOR [APP_ICON]])
# ^^^^^^^^^^^^^^
#
# Same as add_3dsx_target but for CIA files.
#
# * RSF is the .rsf file to be given to makerom.
# * IMAGE is either a .png or a cgfximage file.
# * SOUND is either a .wav or a cwavaudio file.
#
# add_cci_target(target RSF IMAGE SOUND [APP_TITLE APP_DESCRIPTION APP_AUTHOR [APP_ICON]])
# ^^^^^^^^^^^^^^
#
# Same as add_cia_target but for CCI files.
#
# add_netload_target(name target_or_file)
# ^^^^^^^^^^^^^^^^^^
#
# Adds a target `name` that sends a .3dsx using the homebrew launcher netload
# system (3dslink).
# * `target_or_file` is either the name of a target (on which you used
#   add_3dsx_target) or a file name.
#
# add_binary_library(target input1 [input2 ...])
# ^^^^^^^^^^^^^^^^^^
#
# /!\ Requires ASM to be enabled ( `enable_language(ASM)` or `project(yourprojectname C CXX ASM)`)
#
# Converts the files given as input to arrays of their binary data. This is useful
# to embed resources into your project.
# For example, logo.bmp will generate the array `u8 logo_bmp[]` and its size
# `logo_bmp_size`. By linking this library, you will also have access to a
# generated header file called `logo_bmp.h` which contains the declarations you
# need to use it.
#
# Note : All dots in the filename are converted to `_`, and if it starts with a
# number, `_` will be prepended.
# For example `8x8.gas.tex` would give the name `_8x8_gas_tex`.
#
# target_embed_file(target input1 [input2 ...])
# ^^^^^^^^^^^^^^^^^
#
# This is the same as:
# add_binary_library(tempbinlib input1 [input2 ...])
# target_link_libraries(target tempbinlib)
#
# add_shbin(output input [entrypoint] [shader_type])
# ^^^^^^^^^
#
# Assembles the shader given as `input` into the file `output`. No file extension
# is added.
# You can choose the shader assembler by setting SHADER_AS to `picasso` or `nihstro`.
#
# If `nihstro` is set as the assembler, entrypoint and shader_type will be used.
# - entrypoint is set to `main` by default
# - shader_type can be either VSHADER or GSHADER. By default it is VSHADER.
#
# generate_shbins(input1 [input2 ...])
# ^^^^^^^^^^^^^^^
#
# Assemble all the shader files given as input into .shbin files. Those will be
# located in the folder `shaders` of the build directory.
# The names of the output files will be
# `<name of input without shortest extension>.shbin`. `shader.pica` will output
# `shader.shbin` but `shader.vertex.pica` will output `shader.vertex.shbin`.
#
# add_shbin_library(target input1 [input2 ...])
# ^^^^^^^^^^^^^^^^^
#
# /!\ Requires ASM to be enabled ( `enable_language(ASM)` or `project(yourprojectname C CXX ASM)`)
#
# This is the same as:
# generate_shbins(source/shader.vertex.pica)
# add_binary_library(target ${CMAKE_CURRENT_BINARY_DIR}/shaders/shader.vertex.shbin)
#
# This is the function to be used to reproduce devkitArm makefiles behaviour.
# For example, add_shbin_library(shaders data/my1stshader.vsh.pica) will generate
# the target library `shaders` and you will be able to use the shbin in your
# program by linking it, including `my1stshader_pica.h` and using
# `my1stshader_pica[]` and `my1stshader_pica_size`.
#
# target_embed_shader(target input1 [input2 ...])
# ^^^^^^^^^^^^^^^^^^^
#
# This is the same as:
# add_shbin_library(tempbinlib input1 [input2 ...])
# target_link_libraries(target tempbinlib)
#
############################################################################

if(NOT 3DS)
  message(FATAL_ERROR "Those tools can only be used if you are using the 3DS toolchain file. Please erase this build directory or create another one, and then use -DCMAKE_TOOLCHAIN_FILE=DevkitArm3DS.cmake when calling cmake for the 1st time. For more information, see the Readme.md for more information.")
endif()

get_filename_component(__tools3dsdir ${CMAKE_CURRENT_LIST_FILE} PATH) # Used to locate files to be used with configure_file

message(STATUS "Looking for 3ds tools...")

##############
## 3DSXTOOL ##
##############
if(NOT _3DSXTOOL)
  # message(STATUS "Looking for 3dsxtool...")
  find_program(_3DSXTOOL 3dsxtool ${DEVKITARM}/bin)
  if(_3DSXTOOL)
    message(STATUS "3dsxtool: ${_3DSXTOOL} - found")
  else()
    message(WARNING "3dsxtool - not found")
  endif()
endif()


##############
## SMDHTOOL ##
##############
if(NOT SMDHTOOL)
  # message(STATUS "Looking for smdhtool...")
  find_program(SMDHTOOL smdhtool ${DEVKITARM}/bin)
  if(SMDHTOOL)
    message(STATUS "smdhtool: ${SMDHTOOL} - found")
  else()
    message(WARNING "smdhtool - not found")
  endif()
endif()

################
## BANNERTOOL ##
################
if(NOT BANNERTOOL)
  # message(STATUS "Looking for bannertool...")
  find_program(BANNERTOOL bannertool ${DEVKITARM}/bin)
  if(BANNERTOOL)
    message(STATUS "bannertool: ${BANNERTOOL} - found")
  else()
    message(WARNING "bannertool - not found")
  endif()
endif()

set(FORCE_SMDHTOOL FALSE CACHE BOOL "Force the use of smdhtool instead of bannertool")

#############
## MAKEROM ##
#############
if(NOT MAKEROM)
  # message(STATUS "Looking for makerom...")
  find_program(MAKEROM makerom ${DEVKITARM}/bin)
  if(MAKEROM)
    message(STATUS "makerom: ${MAKEROM} - found")
  else()
    message(WARNING "makerom - not found")
  endif()
endif()

#############
### TEX3DS ##
#############
if (NOT TEX3DS)
  # message(STATUS "Looking for tex3ds...")
  find_program(TEX3DS NAMES tex3ds HINTS ${DEKITPRO}/tools/bin)
  if (TEX3DS)
    message(STATUS "tex3ds: ${TEX3DS} - found")
  else()
    message(WARNING "tex3ds - not found")
  endif()
endif()

#############
##  STRIP  ##
#############
if(NOT STRIP)
  # message(STATUS "Looking for strip...")
  find_program(STRIP arm-none-eabi-strip ${DEVKITARM}/bin)
  if(STRIP)
    message(STATUS "strip: ${STRIP} - found")
  else()
    message(WARNING "strip - not found")
  endif()
endif()



#############
##  BIN2S  ##
#############
if(NOT BIN2S)
  # message(STATUS "Looking for bin2s...")
  find_program(BIN2S bin2s ${DEVKITARM}/bin)
  if(BIN2S)
    message(STATUS "bin2s: ${BIN2S} - found")
  else()
    message(WARNING "bin2s - not found")
  endif()
endif()

###############
##  3DSLINK  ##
###############
if(NOT _3DSLINK)
  # message(STATUS "Looking for 3dslink...")
  find_program(_3DSLINK 3dslink ${DEVKITARM}/bin)
  if(_3DSLINK)
    message(STATUS "3dslink: ${_3DSLINK} - found")
  else()
    message(WARNING "3dslink - not found")
  endif()
endif()

#############
## PICASSO ##
#############
if(NOT PICASSO_EXE)
  # message(STATUS "Looking for Picasso...")
  find_program(PICASSO_EXE picasso ${DEVKITARM}/bin)
  if(PICASSO_EXE)
    message(STATUS "Picasso: ${PICASSO_EXE} - found")
    set(SHADER_AS picasso CACHE STRING "The shader assembler to be used. Allowed values are 'none', 'picasso' or 'nihstro'")
  else()
    message(STATUS "Picasso - not found")
  endif()
endif()


#############
## NIHSTRO ##
#############

if(NOT NIHSTRO_AS)
  # message(STATUS "Looking for nihstro...")
  find_program(NIHSTRO_AS nihstro ${DEVKITARM}/bin)
  if(NIHSTRO_AS)
    message(STATUS "nihstro: ${NIHSTRO_AS} - found")
    set(SHADER_AS nihstro CACHE STRING "The shader assembler to be used. Allowed values are 'none', 'picasso' or 'nihstro'")
  else()
    message(STATUS "nihstro - not found")
  endif()
endif()

set(SHADER_AS none CACHE STRING "The shader assembler to be used. Allowed values are 'none', 'picasso' or 'nihstro'")

###############################
###############################
########    MACROS    #########
###############################
###############################


###################
### EXECUTABLES ###
###################


function(__add_smdh target APP_TITLE APP_DESCRIPTION APP_AUTHOR APP_ICON)
  if(BANNERTOOL AND NOT FORCE_SMDHTOOL)
    set(__SMDH_COMMAND ${BANNERTOOL} makesmdh -s ${APP_TITLE} -l ${APP_DESCRIPTION}  -p ${APP_AUTHOR} -i ${APP_ICON} -o ${CMAKE_CURRENT_BINARY_DIR}/${target})
  else()
    set(__SMDH_COMMAND ${SMDHTOOL} --create ${APP_TITLE} ${APP_DESCRIPTION} ${APP_AUTHOR} ${APP_ICON} ${CMAKE_CURRENT_BINARY_DIR}/${target})
  endif()
  add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target}
                        COMMAND ${__SMDH_COMMAND}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                        DEPENDS ${APP_ICON}
                        VERBATIM
    )
endfunction()

function(add_3dsx_target target)
  get_filename_component(target_we ${target} NAME_WE)
  set(_3DSXTOOL_ARGS "$<TARGET_FILE:${target}>" "${CMAKE_CURRENT_BINARY_DIR}/${target_we}.3dsx")
  set(_3DSXTOOL_DEPS ${target})

  if((NOT (${ARGC} GREATER 1 AND "${ARGV1}" STREQUAL "NO_SMDH") ) OR (${ARGC} GREATER 3) )
    if(${ARGC} GREATER 3)
      set(APP_TITLE ${ARGV1})
      set(APP_DESCRIPTION ${ARGV2})
      set(APP_AUTHOR ${ARGV3})
    endif()
    if(${ARGC} EQUAL 5)
      set(APP_ICON ${ARGV4})
    endif()
    if(NOT APP_TITLE)
      set(APP_TITLE ${target})
    endif()
    if(NOT APP_DESCRIPTION)
      set(APP_DESCRIPTION "Built with devkitARM & libctru")
    endif()
    if(NOT APP_AUTHOR)
      set(APP_AUTHOR "Unspecified Author")
    endif()
    if(NOT APP_ICON)
      if(EXISTS ${target}.png)
        set(APP_ICON ${target}.png)
      elseif(EXISTS icon.png)
        set(APP_ICON icon.png)
      elseif(CTRULIB)
        set(APP_ICON ${CTRULIB}/default_icon.png)
      else()
        message(FATAL_ERROR "No icon found ! Please use NO_SMDH or provide some icon.")
      endif()
    endif()
    if( NOT ${target_we}.smdh)
      __add_smdh(${target_we}.smdh ${APP_TITLE} ${APP_DESCRIPTION} ${APP_AUTHOR} ${APP_ICON})
    endif()

    list(APPEND _3DSXTOOL_ARGS "--smdh=${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh")
    list(APPEND _3DSXTOOL_DEPS "${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh")
  else()
    message(STATUS "No smdh file will be generated")
  endif()

  if (DEFINED _3DSXTOOL_ROMFS)
    if (TARGET "${_3DSXTOOL_ROMFS}")
      get_target_property(_folder "${_3DSXTOOL_ROMFS}" ASSET_FOLDER)
      if (NOT _folder)
        message(FATAL_ERROR "add_3dsx_target: not a valid asset target")
      endif()
      list(APPEND _3DSXTOOL_ARGS "--romfs=${_folder}")
      list(APPEND _3DSXTOOL_DEPS ${_3DSXTOOL_ROMFS} $<TARGET_PROPERTY:${_3DSXTOOL_ROMFS},ASSET_FILES>)
    else()
      get_filename_component(_3DSXTOOL_ROMFS "${_3DSXTOOL_ROMFS}" ABSOLUTE)
      if (NOT IS_DIRECTORY "${_3DSXTOOL_ROMFS}")
        message(FATAL_ERROR "add_3dsx_target: cannot find romfs dir: ${_3DSXTOOL_ROMFS}")
      endif()
      list(APPEND _3DSXTOOL_ARGS "--romfs=${_3DSXTOOL_ROMFS}")
    endif()
  endif()

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.3dsx
                        COMMAND ${_3DSXTOOL} ${_3DSXTOOL_ARGS}
                        DEPENDS ${_3DSXTOOL_DEPS}
                        COMMENT "Building ${target_we}.3dsx"
                        VERBATIM
    )
  add_custom_target(${target_we}_3dsx ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.3dsx)
  set_target_properties(${target} PROPERTIES LINK_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=3dsx.specs")
endfunction()

function(__add_ncch_banner target IMAGE SOUND)
  if(IMAGE MATCHES ".*\\.png$")
    set(IMG_PARAM -i ${IMAGE})
  else()
    set(IMG_PARAM -ci ${IMAGE})
  endif()
  if(SOUND MATCHES ".*\\.wav$")
    set(SND_PARAM -a ${SOUND})
  else()
    set(SND_PARAM -ca ${SOUND})
  endif()
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target}
                        COMMAND ${BANNERTOOL} makebanner -o ${CMAKE_CURRENT_BINARY_DIR}/${target} ${IMG_PARAM} ${SND_PARAM}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                        DEPENDS ${IMAGE} ${SOUND}
                        VERBATIM
    )
endfunction()

function(add_cia_target target RSF IMAGE SOUND )
  get_filename_component(target_we ${target} NAME_WE)
  if(${ARGC} GREATER 6)
    set(APP_TITLE ${ARGV4})
    set(APP_DESCRIPTION ${ARGV5})
    set(APP_AUTHOR ${ARGV6})
  endif()
  if(${ARGC} EQUAL 8)
    set(APP_ICON ${ARGV7})
  endif()
  if(NOT APP_TITLE)
    set(APP_TITLE ${target})
  endif()
  if(NOT APP_DESCRIPTION)
    set(APP_DESCRIPTION "Built with devkitARM & libctru")
  endif()
  if(NOT APP_AUTHOR)
    set(APP_AUTHOR "Unspecified Author")
  endif()
  if(NOT APP_ICON)
    if(EXISTS ${target}.png)
      set(APP_ICON ${target}.png)
    elseif(EXISTS icon.png)
      set(APP_ICON icon.png)
    elseif(CTRULIB)
      set(APP_ICON ${CTRULIB}/default_icon.png)
    else()
      message(FATAL_ERROR "No icon found ! Please use NO_SMDH or provide some icon.")
    endif()
  endif()
  if( NOT ${target_we}.smdh)
    __add_smdh(${target_we}.smdh ${APP_TITLE} ${APP_DESCRIPTION} ${APP_AUTHOR} ${APP_ICON})
  endif()
  __add_ncch_banner(${target_we}.bnr ${IMAGE} ${SOUND})

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cia
                        COMMAND ${STRIP} -o $<TARGET_FILE:${target}>-stripped $<TARGET_FILE:${target}>
                        COMMAND ${MAKEROM}     -f cia
                                            -target t
                                            -exefslogo
                                            -o ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cia
                                            -elf $<TARGET_FILE:${target}>-stripped
                                            -rsf ${RSF}
                                            -banner ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.bnr
                                            -icon ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh
                        DEPENDS ${target} ${RSF} ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.bnr ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh
                        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                        VERBATIM
    )

  add_custom_target(${target_we}_cia ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cia)
  set_target_properties(${target} PROPERTIES LINK_FLAGS "-specs=3dsx.specs")
endfunction()

function(add_cci_target target RSF IMAGE SOUND )
  get_filename_component(target_we ${target} NAME_WE)
  if(${ARGC} GREATER 6)
    set(APP_TITLE ${ARGV4})
    set(APP_DESCRIPTION ${ARGV5})
    set(APP_AUTHOR ${ARGV6})
  endif()
  if(${ARGC} EQUAL 8)
    set(APP_ICON ${ARGV7})
  endif()
  if(NOT APP_TITLE)
    set(APP_TITLE ${target})
  endif()
  if(NOT APP_DESCRIPTION)
    set(APP_DESCRIPTION "Built with devkitARM & libctru")
  endif()
  if(NOT APP_AUTHOR)
    set(APP_AUTHOR "Unspecified Author")
  endif()
  if(NOT APP_ICON)
    if(EXISTS ${target}.png)
      set(APP_ICON ${target}.png)
    elseif(EXISTS icon.png)
      set(APP_ICON icon.png)
    elseif(CTRULIB)
      set(APP_ICON ${CTRULIB}/default_icon.png)
    else()
      message(FATAL_ERROR "No icon found ! Please use NO_SMDH or provide some icon.")
    endif()
  endif()
  if( NOT ${target_we}.smdh)
    __add_smdh(${target_we}.smdh ${APP_TITLE} ${APP_DESCRIPTION} ${APP_AUTHOR} ${APP_ICON})
  endif()
  __add_ncch_banner(${target_we}.bnr ${IMAGE} ${SOUND})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cci
                        COMMAND ${STRIP} -o $<TARGET_FILE:${target}>-stripped $<TARGET_FILE:${target}>
                        COMMAND ${MAKEROM}     -f cci
                                            -target t
                                            -exefslogo
                                            -o ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cci
                                            -elf $<TARGET_FILE:${target}>-stripped
                                            -rsf ${RSF}
                                            -banner ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.bnr
                                            -icon ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh
                        DEPENDS ${target} ${RSF} ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.bnr ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.smdh
                        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                        VERBATIM
    )

  add_custom_target(${target_we}_cci ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${target_we}.cci)
  set_target_properties(${target} PROPERTIES LINK_FLAGS "-specs=3dsx.specs")
endfunction()

macro(add_netload_target name target)
  set(NETLOAD_IP "" CACHE STRING "The ip address of the 3ds when using netload.")
  if(NETLOAD_IP)
    set(__NETLOAD_IP_OPTION -a ${NETLOAD_IP})
  endif()
  if(NOT TARGET ${target})
    message("NOT ${target}")
    set(FILE ${target})
  else()
    set(FILE ${CMAKE_CURRENT_BINARY_DIR}/${target}.3dsx)
  endif()
  add_custom_target(${name}
                    COMMAND ${_3DSLINK} ${FILE} ${__NETLOAD_IP_OPTION}
                    DEPENDS  ${FILE}
    )
endmacro()

######################
###### Graphic #######
######################

function(generate_t3xs targetName)
  set(__t3s_files ${ARGN})

  if(NOT DEFINED ROMFS_DIR)
    set(ROMFS_DIR "${CMAKE_CURRENT_BINARY_DIR}/romfs")
  endif()
  file(MAKE_DIRECTORY ${ROMFS_DIR})

  if(NOT DEFINED GFXBUILD_DIR)
    set(GFXBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/romfs/gfx")
  endif()
  file(MAKE_DIRECTORY ${GFXBUILD_DIR})

  message(STATUS "generate_t3sx: Generating GFX in ${GFXBUILD_DIR}")
  set(__t3x_outputs)

  foreach(__t3s ${__t3s_files})
    get_filename_component(__name_we ${__t3s} NAME_WE)

    set(__out ${GFXBUILD_DIR}/${__name_we}.t3x)
    list(APPEND __t3x_outputs ${__out})

    add_t3x(${__out} ${__t3s})
  endforeach()

  message(STATUS "generate_t3sx: GFX Outputs ${__t3x_outputs}")

  # Create a real custom target that wraps all those outputs
  add_custom_target(${targetName} ALL
        DEPENDS ${__t3x_outputs}
    )

  # Store properties for use by add_3dsx_target
  set_target_properties(${targetName} PROPERTIES
        ASSET_FOLDER "${ROMFS_DIR}"
        ASSET_FILES "${__t3x_outputs}"
    )
endfunction()

function(add_t3x_library libtarget)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gfx)

  set(__T3X_FILES)

  foreach(__t3s ${ARGN})
    get_filename_component(__name_we ${__t3s} NAME_WE)
    set(__t3x ${CMAKE_CURRENT_BINARY_DIR}/gfx/${__name_we}.t3x)

    add_t3x(${__t3x} ${__t3s})
    list(APPEND __T3X_FILES ${__t3x})
  endforeach()

  add_binary_library(${libtarget} ${__T3X_FILES})
endfunction()

macro(target_embed_t3x _target)
  if(NOT ${ARGC} GREATER 1)
    message(FATAL_ERROR "target_embed_t3x : no input files")
  endif()

  get_filename_component(__1st_file ${ARGV1} NAME)
  add_t3x_library(__${_target}_embed_${__1st_file} ${ARGN})
  target_link_libraries(${_target} __${_target}_embed_${__1st_file})
endmacro()

######################
### File embedding ###
######################

macro(add_binary_library libtarget)
  if(NOT ${ARGC} GREATER 1)
    message(FATAL_ERROR "add_binary_library : Argument error (no input files)")
  endif()
  get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
  if(NOT ENABLED_LANGUAGES MATCHES ".*ASM.*")
    message(FATAL_ERROR "You have to enable ASM in order to use add_binary_library (or any target_embed_* which relies on it). Use enable_language(ASM) in your CMakeLists. Currently enabled languages are ${ENABLED_LANGUAGES}")
  endif()


  foreach(__file ${ARGN})
    get_filename_component(__file_wd ${__file} NAME)
    string(REGEX REPLACE "[^A-Za-z0-9_./-]" "" __BIN_FILE_NAME ${__file_wd})
    string(REGEX REPLACE "[./-]" "_" __BIN_FILE_NAME ${__BIN_FILE_NAME})
    string(REGEX REPLACE "^([0-9])" "_\\1" __BIN_FILE_NAME ${__BIN_FILE_NAME}) # add '_' if the file name starts by a number

    #Generate the header file
    configure_file(${__tools3dsdir}/bin2s_header.h.in ${CMAKE_CURRENT_BINARY_DIR}/${libtarget}_include/${__BIN_FILE_NAME}.h)
  endforeach()

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/binaries_asm)
  # Generate the assembly file, and create the new target
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/binaries_asm/${libtarget}.s
                        COMMAND ${BIN2S} ${ARGN} > ${CMAKE_CURRENT_BINARY_DIR}/binaries_asm/${libtarget}.s
                        DEPENDS ${ARGN}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

  add_library(${libtarget} ${CMAKE_CURRENT_BINARY_DIR}/binaries_asm/${libtarget}.s)
  target_include_directories(${libtarget} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${libtarget}_include)
endmacro()

macro(target_embed_file _target)
  if(NOT ${ARGC} GREATER 1)
    message(FATAL_ERROR "target_embed_file : Argument error (no input files)")
  endif()
  get_filename_component(__1st_file_wd ${ARGV1} NAME)
  add_binary_library(__${_target}_embed_${__1st_file_wd} ${ARGN})
  target_link_libraries(${_target} __${_target}_embed_${__1st_file_wd})
endmacro()

###################
##### SHADERS #####
###################

macro(add_shbin OUTPUT INPUT )

  if(SHADER_AS STREQUAL "picasso")

    if(${ARGC} GREATER 2)
      message(WARNING "Picasso doesn't support changing the entrypoint or shader type")
    endif()
    add_custom_command(OUTPUT ${OUTPUT} COMMAND ${PICASSO_EXE} -o ${OUTPUT} ${INPUT} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

  elseif(SHADER_AS STREQUAL "nihstro")
    if(NOT NIHSTRO_AS)
      message(SEND_ERROR "SHADER_AS is set to nihstro, but nihstro wasn't found. Please set NIHSTRO_AS.")
    endif()
    if(${ARGC} GREATER 2)
      if(${ARGV2} EQUAL GSHADER)
        set(SHADER_TYPE_FLAG "-g")
      elseif(NOT ${ARGV2} EQUAL VSHADER)
        set(_ENTRYPOINT ${ARGV2})
      endif()
    endif()
    if(${ARGC} GREATER 3)
      if(${ARGV2} EQUAL GSHADER)
        set(SHADER_TYPE_FLAG "-g")
      elseif(NOT ${ARGV3} EQUAL VSHADER)
        set(_ENTRYPOINT ${ARGV3})
      endif()
    endif()
    if(NOT _ENTRYPOINT)
      set(_ENTRYPOINT "main")
    endif()
    add_custom_command(OUTPUT ${OUTPUT} COMMAND ${NIHSTRO_AS} ${INPUT} -o ${OUTPUT} -e ${_ENTRYPOINT} ${SHADER_TYPE_FLAG} WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

  else()
    message(FATAL_ERROR "Please set SHADER_AS to 'picasso' or 'nihstro' if you use the shbin feature.")
  endif()

endmacro()


##################
#### TEXTURES ####
##################

macro(add_t3x OUTPUT INPUT)
  if(NOT TEX3DS)
    message(FATAL_ERROR "tex3ds not found, cannot build textures")
  endif()

  get_filename_component(_name_we ${INPUT} NAME_WE)

  add_custom_command(
        OUTPUT ${OUTPUT} ${CMAKE_CURRENT_BINARY_DIR}/${_name_we}.hpp
        COMMAND ${TEX3DS}
            -i ${INPUT}
            -o ${OUTPUT}
            -H ${CMAKE_CURRENT_BINARY_DIR}/${_name_we}.hpp
        DEPENDS ${INPUT}
        COMMENT "Generating tex3ds: ${_name_we}.t3x"
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        VERBATIM
    )
endmacro()


# Get filename without shortest extension
macro(get_filename_wse VAR FileName)
  get_filename_component(${VAR} "${FileName}" NAME)
  string(REGEX REPLACE "\\.[^.]*$" "" ${VAR} "${${VAR}}")
endmacro()

function(generate_shbins)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)
  foreach(__shader_file ${ARGN})
    get_filename_wse(__shader_file_we "${__shader_file}")
    #Generate the shbin file
    add_shbin(${CMAKE_CURRENT_BINARY_DIR}/shaders/${__shader_file_we}.shbin ${__shader_file})
  endforeach()
endfunction()

function(add_shbin_library libtarget)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/shaders)
  set(__SHADERS_BIN_FILES)
  foreach(__shader_file ${ARGN})
    get_filename_wse(__shader_file_we "${__shader_file}")
    #Generate the shbin file
    list(APPEND __SHADERS_BIN_FILES ${CMAKE_CURRENT_BINARY_DIR}/shaders/${__shader_file_we}.shbin)
    add_shbin(${CMAKE_CURRENT_BINARY_DIR}/shaders/${__shader_file_we}.shbin ${__shader_file})
  endforeach()
  add_binary_library(${libtarget} ${__SHADERS_BIN_FILES})
endfunction()


macro(target_embed_shader _target)
  if(NOT ${ARGC} GREATER 1)
    message(FATAL_ERROR "target_embed_shader : Argument error (no input files)")
  endif()
  get_filename_component(__1st_file_wd ${ARGV1} NAME)
  add_shbin_library(__${_target}_embed_${__1st_file_wd} ${ARGN})
  target_link_libraries(${_target} __${_target}_embed_${__1st_file_wd})
endmacro()
