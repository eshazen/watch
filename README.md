# Smart Watch

Imagining a device similar to a smart watch, but not intended to
connect to a phone and generate alerts.  Instead, I'd like:

* Large, easy-to-read e-ink time display
* Auxiliary info (possibly selected using button):
   * Multiple timezones
   * Alarm/timer time
   * Weather info
   * Any other not-quite realtime info pushed via WiFi

The idea would be that the watch has WiFi but only powers up every 10min or
so and tries to connect to the last AP, otherwise tries a short list of AP.
Some fairly smart algorithm should recognize when not near an AP and give up,
checking at longer intervals.  A button press should be available to force
WiFi update.

Ordered a black/red display from buydisplay.com.  This works ok but has
a ~15s refresh time and doesn't support fast/partial refresh.  My bad!

Ordered another from waveshare which is monochrome and does support
partial refresh.  Holding off on buying anything else until the display
part is working reasonably.

## Doco

* Display: [Mfgr page](https://www.buydisplay.com/red-1-54-inch-e-ink-display-module-200x200-for-arduino-raspberry-pi)
* eInk.md

## Parts?

* MCU:  ATMega1281-16AUR (64-TQFP)
   * Chosen for it's 8K RAM size so it can hold a 200x200 bitmap for the display
* RTC: 
   * Nisshinbo R2043T-E2-F (2129-R2043T-E2-FCT-ND).  10-VFSOP
   * Nisshinbo R2025S-E2-FE (2129-R2025S-E2-FECT-ND).  14-SOIC
* Thru pin socket
   * Mill-Max 0305-2-15-80-47-27-10-0  (0305-2-15-80-47-27-10-0)
* Side-mount switch
   * Panasonic EVQ-P4MB3K (P15507CT-ND)
* Battery Holder for CR1216
   * Linx BAT-HLD-012-SMT (BAT-HLD-012-SMT-ND)
* or Lipo battery.  There seem to be 100mAh batts 18x14.7mm which are
  cheap ($16/4 on Amazon with a little USB charger thing).  These are
  3.7V so we need a small-ish 3.3V LDO.
* WiFi
   * ESP-01 [data](https://www.microchip.ua/wireless/esp01.pdf)

ESP-01 Power Consumption:  
* 170mA working worst case
* 0.9mA "light sleep"
* 10uA "deep sleep"

Datasheet says "...sleep 300s and waking up to connect to the AP
(taking about 0.3~1s), the overall average current is less than 1mA.
Not clear how this is affected if multiple AP must be tried.  Need
to get some ESP-01 and play with them.

So we're looking at ~1mA minimum average power with capability to
deliver ~200mA.  For few days running it would be nice to have
~100mAh.

It seems that on ESP-01 modules you need to wire pin 8 to nRESET so it
can self-wake out of deep sleep.  Otherwise you can just call
ESP.deepSleep(0) and then use the MCU to pulse reset to wake it up.
(see
[note](https://www.tech-spy.co.uk/2019/04/enable-deep-sleep-esp-01/))

