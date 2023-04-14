## [SA:MP / Open.MP] Textdraw Streamer
[![GitHub Release](https://img.shields.io/github/release/nexquery/samp-textdraw-streamer.svg)](https://github.com/nexquery/samp-textdraw-streamer/releases/latest) [![Download](https://img.shields.io/github/downloads/nexquery/samp-textdraw-streamer/total?color=blue)](https://github.com/nexquery/samp-textdraw-streamer/releases/latest) [![License](https://img.shields.io/github/license/nexquery/samp-textdraw-streamer?color=blue)](https://github.com/nexquery/samp-textdraw-streamer)

## Foreword
This plugin is inspired by the streamer plugin. Previously people used a lot of CreatePlayerTextDraw under OnPlayerConnect, they were reaching the limits of text drawing because they used it too much. Because they had reached the limit, they could not display the text drawings properly and were looking for a solution. I decided to make such an add-on because I was having a lot of trouble because of this problem.

## Supports
The plugin now supports [open.mp](https://github.com/openmultiplayer/open.mp/releases) versions.

## Arrangements
You will need to change some natives as the plugin has undergone radical changes. If you haven't used these natives before, it should work fine when you install the plugin normally. Also add format support for all texts.

## The Most Important Part
Always add the textdraw-streamer library to the bottom of the available libraries.
```c
#include <open.mp>
#include <mysql>
#include <sscanf2>
#include <weapon-config>
#include <textdraw-streamer>
```

## Callbacks
```c
public OnCancelDynamicTextDraw(playerid)
{
    return 0;
}

public OnClickDynamicTextDraw(playerid, Text:textid)
{
    return 0;
}

public OnClickDynamicPlayerTextDraw(playerid, PlayerText:textid)
{
    return 0;
}
```

## Compilation
Install gcc and g++, make and cmake. On Ubuntu you would do that like so:
```
sudo apt-get install gcc g++ make cmake
```
If you're on a 64-bit system you'll need additional packages for compiling for 32-bit:
```
sudo apt-get install gcc-multilib g++-multilib
```
Finally:
```
cd src
mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
```
