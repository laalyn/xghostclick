# XGHOSTCLICK

## about
XGHOSTCLICK is an autoclicker that sends inputs on the X Server level, triggered with your set keybinds. It runs on a humanizing algorithm to make it virtually undetectable for server sided anticheats, and not for client-sided anticheats. <br><br>*but seriously, client-sided anticheats on LINUX!?*

## backstory
I'm tired of getting comboed to death. Every other autoclicker out there is only for Windows (disgusting!) and either don't do anything to make it undetected, or use a *very* preliminary randomizing/humanizing/obfuscating algorithm (simple random delay between a fixed range). If I were hosting a server I'd detect and ban all of them in seconds!<br><br>
So, I decided to make one myself. What I ended up with looks so damn close to legitimate clicking that I can't even tell myself! You can go to Rimu's clicking speed test and compare the graphs for yourself.

## warning
You'll still get ratted out if you use this tool improperly. Using a bad config, autoclicking for too long, and moving your mouse too fast while autoclicking will surely cause that. Oh, and did I forget to mention that this tool wasn't designed for use with client-sided anticheats?

## prerequisites
Make sure you're running X, not Wayland. Then check if you have the X utilities `xinput` and `xdotool` installed. If not, go and install them.

## using this tool
Before your first run, build with `./build.sh`. Invoke the program with `./launch path_to_config`, where `path_to_config` is the relative path to your config file.

## configuring
A config is just a `.txt` file, since I'm too stoopid to use JSON or anything fancier. Since this program isn't installed globally, I recommend storing your configs under `configs/` in the project root. The build script makes the folder just for you, and it's also gitignored! <br><Br>
You define global settings with `!GLOBAL setting value`, and a keybind to specified autoclicker parameters with `!ENTRY trigger state type id , state type id , ... ; value value ...`. Everything else is treated as a comment.<br>
#### Global settings: 
* Verbosity `verbosity value`
  * Sets verbosity of program. val is a number from 0-100, where higher numbers amount to higher verbosity. Defaults to 0.<br><br>
* Precision `precision value`
  * Sets precision of timing used in program in microseconds. If set to 0, the program attempts to use the highest precision, resulting in the highest CPU usage. Defaults to 0. Remember that USB devices usually poll 1000 times per second, so the precision of that is 1ms, or 1000 microseconds.<br><br>
* Keyboard id: `keyboard_id value`
  * Sets the id of keyboard to listen for with `xinput`. It is recommended to not set this value in the config file, so the interactive setter will set this at runtime. This is because XInput id's change when a device is unplugged and plugged in again, and you'll probably forget to update the values when it does.<br><br>
* Pointer id: `pointer_id value`
  * Sets the id of pointer (mouse) to listen for with `xinput`. It is recommended to not set this value in the config file, so the interactive setter will set this at runtime. This is because XInput id's change when a device is unplugged and plugged in again, and you may forget to update the values when it does.<br><br>
* Example: `!GLOBAL verbosity 10`, to set verbosity to the highest.
#### Entry parameters: 
* Trigger type: `trigger`
  * Can be `toggle` or `hold`. Toggle activates on key/button press, and deactivates only when the key/button goes up and is pressed again.<br><br>
* Key matching (so you can invoke the autoclicker): `state type id , state type id , ... ; `
  * Note: commas and semicolons must have a space before and after it.
  * Simple key matching. Will only trigger if all states are matched. You can achieve Trigger on key/button down (while some other keys/buttons are not pressed), but you cannot achieve Trigger on click up.
  * `state` can be `down` or `up`.
  * `type` specifies type type, and can be `key` or `button` (from keyboard or mouse, respectively).
  * `id` specifies what key/button to check. It's an id from `xinput --query-state`.
  * Add as many of these as you like, but make sure to end with a semicolon.<br><br>
* Autoclicker parameters: `value value ...`
  * 1st value: Type of input for autoclicker to send. Can be `key` or `button`.
  * 2nd value: Input id as seen by `xinput --query-state`.
  * 3rd and 4th value: defines range of minimum cps for autoclicker to send.
  * 5th and 6th value: defines range of maximum cps for autoclicker to send.
  * 7th and 8th value: defines range of the minimum allowed difference between the next generated minimum cps and the current one, based off of delay in milliseconds. (Yes, this is delay, not cps.)
  * 9th and 10th value: defines range of the minimum allowed difference between the next generated maximum cps and the current one, based off of delay in milliseconds. (Yes, this is delay, not cps.)
  * 11th and 12th value: defines range of the minimum allowed difference between the next generated time to click and the current one, based off of delay in milliseconds. (Remember, working with delay.)
  * 13th and 14th value: defines range of the amount of time where the key/button is down during the delay period, based off of a percentage of the delay period.
  * 15th and 16th value: defines range of the minimum allowed difference between the next generated amount of time where the key/button is down and the current one, based off of a percentage of the delay period.
  * 17th and 18th value: defines range of when to regenerate min and max cps' based off of how many clicks got clicked before the regeneration.
  * 19th and 20th value: defines range of the minimum allowed difference between the next generated time to regenerate min and max cps' based of of how many clicks got clicked before the regeneration.
  * 21st and 22nd value: defines range of when to terminate the regeneration process based off of how many iterations already occured during the process. <br><br>
* IMPORTANT: You will probably need to compensate for the extra delay caused by slower timing. Keep scaling the ranges and numbers while testing to see if it looks better. <br><br>
* Example: `!ENTRY toggle down key 66 ; button 1 9 19 31 47 11 19 13 21 9 25 31 69 9 25 35 70 2 6 90 150` makes you a semi-sweat pvper every time you toggle with CAPS_LOCK, clicking 8-12 cps assuming timing is set at 10ms.
  
### enjoy <3
