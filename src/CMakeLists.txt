set(CMAKE_SUPPRESS_REGENERATION true)

project(textdraw-streamer)

cmake_minimum_required(VERSION 2.8)
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

add_samp_plugin(textdraw-streamer
	amxplugin.cpp
	compilation_date.hpp
	main.cpp
	natives.hpp
	natives_data.cpp
	natives_global.cpp
	natives_player.cpp
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
