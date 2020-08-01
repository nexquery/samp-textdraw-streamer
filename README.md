### Textdraw Streamer
This plugin removes the PlayerTextdraw limit. All you have to do is install the plugin.

### Why This Plugin?
This add-on is designed to avoid pawn loads. It is as fast as possible because it is designed with C ++.

### Bug?
As a result of the tests I have done, I have not encountered a bug. If you find an error, feel free to report it.

### Setup
Simply add the TD-Streamer library to the very beginning of the game mode you are using.

_Example:_
```c++
#include <a_samp>
#include <TD-Streamer>

other libraries...
```
Then all you have to do is change the name OnPlayerClickPlayerTextDraw to ClickDynamicPlayerTextdraw.

```c++
public ClickDynamicPlayerTextdraw(playerid, PlayerText: playertextid)
{
	return 0;
}
```
