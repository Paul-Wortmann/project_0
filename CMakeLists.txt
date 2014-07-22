Project ("Project 0")
cmake_minimum_required (VERSION 2.8)

Set (PACKAGE "PROJECT_0")
Set (VERSION "0.0.1")


# Default definitions
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -Wshadow -Woverloaded-virtual -Wunreachable-code")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-math-errno -fno-exceptions -ffast-math")
  set(CMAKE_LD_FLAGS "-fwhole-program")
endif (NOT MSVC)

if (CMAKE_CXX_COMPILER MATCHES "clang")
  # clang needs lstdc++ linked explicitly:
  set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -lstdc++")
elseif (NOT MSVC)
  # assume gcc:
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-enforce-eh-specs")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g0")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -g0")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -pg")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-pg")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "-pg")
  set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "-pg")
endif()

set(BINDIR  "games"             CACHE STRING "Directory from CMAKE_INSTALL_PREFIX where game executable will be installed.")
set(DATADIR "share/games/project_0" CACHE STRING "Directory from CMAKE_INSTALL_PREFIX where game data files will be installed.")

If(NOT IS_ABSOLUTE "${DATADIR}")
	add_definitions(-DDATA_INSTALL_DIR="${CMAKE_INSTALL_PREFIX}/${DATADIR}")
Else(NOT IS_ABSOLUTE "${DATADIR}")
	add_definitions(-DDATA_INSTALL_DIR="${DATADIR}")
EndIf(NOT IS_ABSOLUTE "${DATADIR}")

# Detect missing dependencies

Include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
If (NOT SDL2_FOUND)
    Message (ERROR "Couldn't find SDL2 development files. On Debian-based systems (such as Ubuntu) you should install the 'libsdl2-dev' package.")
Else (NOT SDL2_FOUND)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
EndIf (NOT SDL2_FOUND)

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
If (NOT SDL2IMAGE_FOUND)
    Message (ERROR "Couldn't find SDL2-image development files. On Debian-based systems (such as Ubuntu) you should install the 'libsdl2-image-dev' package.")
Else (NOT SDL2IMAGE_FOUND)
    INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
EndIf (NOT SDL2IMAGE_FOUND)

PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
If (NOT SDL2MIXER_FOUND)
    Message (ERROR "Couldn't find SDL2-mixer development files. On Debian-based systems (such as Ubuntu) you should install the 'libsdl2-mixer-dev' package.")
Else (NOT SDL2MIXER_FOUND)
    INCLUDE_DIRECTORIES(${SDL2MIXER_INCLUDE_DIRS})
EndIf (NOT SDL2MIXER_FOUND)

 PKG_SEARCH_MODULE(SDL2NET REQUIRED SDL2_net)
 If (NOT SDL2NET_FOUND)
     Message (ERROR "Couldn't find SDL2_net development files. On Debian-based systems (such as Ubuntu) you should install the 'libsdl2-net-dev' package.")
 Else (NOT SDL2NET_FOUND)
     INCLUDE_DIRECTORIES(${SDL2NET_INCLUDE_DIRS})
 EndIf (NOT SDL2NET_FOUND)

PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
If (NOT SDL2TTF_FOUND)
    Message (ERROR "Couldn't find SDL2-ttf development files. On Debian-based systems (such as Ubuntu) you should install the 'libsdl2-ttf-dev' package.")
Else (NOT SDL2TTF_FOUND)
    INCLUDE_DIRECTORIES(${SDL2TTF_INCLUDE_DIRS})
EndIf (NOT SDL2TTF_FOUND)

#PKG_SEARCH_MODULE(PHYSFS REQUIRED PhysFS)
#If (NOT PHYSFS_FOUND)
#    Message (ERROR "Couldn't find PhysicsFS development files. On Debian-based systems (such as Ubuntu) you should install the 'libphysfs-dev' package.")
#Else (NOT PHYSFS_FOUND)
#    INCLUDE_DIRECTORIES(${PHYSFS_INCLUDE_DIRS})
#EndIf (NOT PHYSFS_FOUND)

find_package(PhysFS REQUIRED)
if (PHYSFS_FOUND)
  INCLUDE_DIRECTORIES(${PHYSFS_INCLUDE_DIR})
  link_directories(${PHYSFS_LIBRARY})
Else (PHYSFS_FOUND)
   Message (FATAL_ERROR "Couldn't find libphysfs development files. On Debian-based systems (such as Ubuntu) you should install the 'libphysfs-dev' package.")
endif (PHYSFS_FOUND)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
  link_directories(${OPENGL_LIBRARIES})
Else (OPENGL_FOUND)
  Message (FATAL_ERROR "Couldn't find OpenGl development files. On Debian-based systems (such as Ubuntu) you should install the OpenGL development package.")
endif (OPENGL_FOUND)

PKG_SEARCH_MODULE(GLEW REQUIRED glew)
If (NOT GLEW_FOUND)
    Message (ERROR "Couldn't find glew development files. On Debian-based systems (such as Ubuntu) you should install the 'libglew-dev' package.")
Else (NOT GLEW_FOUND)
    INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
    #link_directories(${GLEW_LIBRARIES})
EndIf (NOT GLEW_FOUND)

include_directories(/usr/include)

# Sources

Set (PROJECT_0_SOURCES

    ./src/game.cpp
    ./src/main.cpp
    ./src/core/core.cpp
    ./src/core/graphics_engine/graphics_engine.cpp
    ./src/core/graphics_engine/graphics_engine_GL.cpp
    ./src/core/graphics_engine/graphics_engine_GLES.cpp
    ./src/core/graphics_engine/graphics_engine_GL_legacy.cpp
    ./src/core/graphics_engine/graphics_engine_vao_manager.cpp
    ./src/core/map/loader_tmx.cpp
    ./src/core/map/map.cpp
    ./src/core/other/command_line_parser.cpp
    ./src/core/other/config.cpp
    ./src/core/other/file.cpp
    ./src/core/other/io_manager.cpp
    ./src/core/other/log.cpp
    ./src/core/other/misc.cpp
    ./src/core/other/physics.cpp
    ./src/core/other/timer.cpp
    ./src/core/resource_management/font_manager.cpp
    ./src/core/resource_management/music_manager.cpp
    ./src/core/resource_management/object_manager.cpp
    ./src/core/resource_management/sound_manager.cpp
    ./src/core/resource_management/sprite_sheet_manager.cpp
    ./src/core/resource_management/texture_manager.cpp
)

# Add icon and file info to executable for Windows systems
IF (WIN32)
  SET(PROJECT_0_SOURCES
    ${PROJECT_0_SOURCES}
    ./source/icon.rc
    )
ENDIF (WIN32)

Add_Executable (project_0 ${PROJECT_0_SOURCES})

link_directories( /path/to/PHYSFSlibs/)

Target_Link_Libraries (project_0 ${CMAKE_LD_FLAGS}  ${PHYSFS_LIBRARY} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2NET_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})


