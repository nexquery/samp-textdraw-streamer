[![GitHub Release](https://img.shields.io/github/release/BenBurak/Textdraw-Streamer.svg)](https://github.com/BenBurak/Textdraw-Streamer/releases/latest) [![Download](https://img.shields.io/github/downloads/BenBurak/Textdraw-Streamer/total?color=blue)](https://github.com/BenBurak/Textdraw-Streamer/releases/latest) [![License](https://img.shields.io/github/license/BenBurak/Textdraw-Streamer?color=blue)](https://github.com/BenBurak/Textdraw-Streamer)

### Textdraw Streamer
This plugin removes the PlayerTextdraw limit. All you have to do is install the plugin.

### Why This Plugin?
This add-on is designed to avoid pawn loads. It is as fast as possible because it is designed with C++.

### Bug?
As a result of the tests I have done, I have not encountered a bug. If you find an error, feel free to report it.

### Setup
Simply add the textdraw-streamer library to the very beginning of the game mode you are using.

_Example:_
```c++
#include <a_samp>
#include <textdraw-streamer>

other libraries...
```

### If You Are Using Weapon Config

_Example:_
```c++
#include <a_samp>
#include <weapon-config>
#include <textdraw-streamer>

other libraries...
```

Then all you have to do is use one of the following callbacks.

```c++
public ClickDynamicPlayerTextdraw(playerid, PlayerText: playertextid)
{
	return 0;
}

public OnPlayerClickDynamicTextdraw(playerid, PlayerText: playertextid)
{
	return 0;
}

public OnDynamicPlayerTextdrawClicked(playerid, PlayerText: playertextid)
{
	return 0;
}
```

### How can I compile the plugin?
```
cd src
mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
make
```
