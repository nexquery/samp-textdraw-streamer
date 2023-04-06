set(CMAKE_SUPPRESS_REGENERATION true)

project(textdraw-streamer)

cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
)

add_definitions(-DSAMPGDK_AMALGAMATION)

add_samp_plugin(textdraw-streamer
	amxplugin.cpp
	main.cpp
	plugin.h
	plugincommon.h
	sampgdk.cpp
	sampgdk.h
	textdraw-streamer.def
)