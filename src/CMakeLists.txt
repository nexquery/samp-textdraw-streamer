set(CMAKE_SUPPRESS_REGENERATION true)

# CMake 4 removed compatibility with a < 3.5 minimum, which "2.8" was.
cmake_minimum_required(VERSION 3.10)

project(textdraw-streamer C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt
)

add_definitions(-DSAMPGDK_AMALGAMATION)
add_definitions(-DFMT_HEADER_ONLY)

if(MSVC)
  # service.cpp guards fmt::sprintf with try/catch so a malformed script format
  # string cannot propagate out; that needs unwind semantics rather than relying
  # on /EHsc arriving via CMake's default flags.
  add_compile_options(/EHsc)
endif()

if(UNIX AND NOT APPLE)
  # Keep the .so loadable on older hosts than the one that built it.
  #
  # Two separate glibc traps, both decided by the *build* machine:
  #
  # 1. glibc 2.38 + GCC 13 redirect plain strtol/sscanf to __isoc23_* symbols
  #    tagged GLIBC_2.38. Compiling the C sources as C17 keeps the old
  #    unversioned names. This matters when building on a current distro; on an
  #    older one it is simply a no-op.
  #
  # 2. glibc 2.34 merged libpthread/libdl/librt into libc, so sampgdk's
  #    dlopen/pthread calls pick up GLIBC_2.34. No flag avoids that one -- it
  #    requires building against an older glibc, which is why CI builds inside
  #    a Debian 11 (glibc 2.31) container.
  add_compile_options($<$<COMPILE_LANGUAGE:C>:-std=gnu17>)
endif()

add_samp_plugin(textdraw-streamer
	amxplugin.cpp
	compilation_date.hpp
	main.cpp
	natives.hpp
	natives_data.cpp
	natives_global.cpp
	natives_player.cpp
	natives_plugin.cpp
	plugin.h
	plugin_version.hpp
	plugincommon.h
	sampgdk.cpp
	sampgdk.hpp
	service.cpp
	service.hpp
	slot_manager.cpp
	slot_manager.hpp
	textdraw_data.cpp
	textdraw_data.hpp
	textdraw-streamer.def
)

if(UNIX AND NOT APPLE)
  # libstdc++ and libgcc are the other moving target: static-link them so the
  # host does not need a runtime as new as the build machine's either.
  set_property(TARGET textdraw-streamer APPEND_STRING PROPERTY
               LINK_FLAGS " -static-libstdc++ -static-libgcc")
endif()
