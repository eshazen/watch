# Smart Watch

Parts?

* MCU:  ATMega1281-16AUR (64-TQFP)
* RTCs: 
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

Wifi?

ESP-01 [data](https://www.microchip.ua/wireless/esp01.pdf)

Power:  
* 170mA working worst case
* 0.9mA "light sleep"
* 10uA "deep sleep"

Datasheet says "...sleep 300s and waking up to connect to the AP
(taking about 0.3~1s), the overall average current is less than 1mA.

So we're looking at ~1mA minimum average power with capability to
deliver ~200mA.  For few days running it would be nice to have
~100mAh.

It seems that on ESP-01 modules you need to wire pin 8 to nRESET so it
can self-wake out of deep sleep.  Otherwise you can just call
ESP.deepSleep(0) and then use the MCU to pulse reset to wake it up.
(see
[note](https://www.tech-spy.co.uk/2019/04/enable-deep-sleep-esp-01/))

