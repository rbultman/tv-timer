# tv-timer
A timer that only powers the TV for an amount of time per day.

## Usage

Set the time and date.  When you want to watch TV, move the
encoder to bring up the menu and select "Start Watching".
When you want to stop watching move the encoder to bring up
the menu and select "Stop Watching".  If the watch timer
expires while watching, the TV will turn off and the watch
time will beging to recharge.

As long as there is some time on the watch timer, you can
start watching TV but only for the amount of time currently
in the watch timer.

## Design

This project makes use of the follwing hardware:
- [Renesas GR-Peach board](https://os.mbed.com/platforms/Renesas-GR-PEACH/)
- [DS3231 RTC breakout board from Adafruit](https://www.adafruit.com/product/3013)
- [Battery charger](https://www.adafruit.com/product/1904)
- [Newhaven LCD with RGB backlight](https://www.newhavendisplay.com/nhdc12864a1zfsrgbfbwht1-p-3896.html)
- [Encoder from Adafruit](https://www.adafruit.com/product/377)

[mbed-os]() was used for the development.  Graphics were handled by a forked version of the 
[lvgl graphics system](https://github.com/rbultman/lvgl) and [drivers](https://github.com/rbultman/lv_drivers).

### States
1. Setup - Set date and time
2. Not Watching - Watch time is recharged
3. Watching - Watch time is counting down

### Screens
**State: Setup**

*Description*\
Allows the date and time to be set on the RTC.  This state
will be entered at power up if the RTC has not been initialized.

*Prerequisite*\
Read the current time and date from the RTC to be used to populate
the setting screens.  Has a flag for indicating that the RTC is
not initialized.

Screen 1 - Set Date
- Set the month, day, and year
- Has a next button which advances to the set time screen
- If the RTC has been initialized, has a cancel button which allows
the setting process to be canceled.

Screen 2 - Set Time
- Set the hour, minute, and AM/PM
- Has a save button which causes the time to be written to the RTC
- Has a previous button which returns to the Set Date screen.

**State: Not Watching:**

*Description*\
The date and time are shown.  The current amount of watch time
is displayed.  This states manages the recharge time based on the
setting of alarm 2.

Screen 3 - Show time and date
- Shows the time, date, and available watch time.
- Advances to the menu if the encoder is moved or clicked. 

Screen 4 - Menu
- Shows menu options: start watching, setup, cancel
- Advances to the watching screen if start watching is selected.
alarm 1 is started with the amount of watching time.
- Advances to the setup screen if setup is selected.
- Returns to showing the date and time if cancel is selected.

**State: Watching**

*Description*\
Shows the amount of time remaining on the watch timer.

*Prerequisite*\
Alarm 1 has been set on the RTC.

Screen 5 - Watching
- Shows the current time of day and the time remaining on the watch timer
- Advances to the menu if the encoder is moved or clicked. 

Screen 6 - Menu
- Show menu options: stop watching, cancel
- Stops the watch timer, and sets alarm 2 if stop watching is selected.
- Returns to the watching screen if cancel is selected.

### Notes
1. If alarm 1 is enabled, it indicates that the TV is currently being watched.
2. If alarm 2 is enabled, it indicates that the timer is currently recharging.
3. If neither alarm 1 or alarm 2 are enabled it indicates that the watch timer
is full.
4. The relay shall be on during the watching state and off otherwise.
5. The backlight shall only remain on for 1 minute after the last movement of 
the encoder.
