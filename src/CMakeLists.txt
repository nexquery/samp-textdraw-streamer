project(textdraw-streamer)

set(CMAKE_SUPPRESS_REGENERATION true)

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
  Item.cpp
  Natives.cpp
  precompiler.cpp
  Servis.cpp
  SlotManager.cpp
  Makro.h
  main.cpp
  textdraw-streamer.def
  sampgdk.c
  sampgdk.h
)