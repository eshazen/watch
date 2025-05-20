# V1.0 build log

Some issues from looking things over before assembly:

* I(Q) of the regulator may be an issue.  Spec'd at 70uA.
For a 100mAh battery math says ~1500 hours so maybe fine.
* Not sure the RFM69 radio is really useful.  Ideally WiFi
so can connect at home and on campus periodically.

An alternative would be to use an ESP8266 ESP-12F module
(24x16mm).  (the RFM69 site is 16x16mm).

Or another alternative would be to carry in my backpack
or pocket a "bridge" device with WiFi and an RFM69.
It could even have GPS so it knows it's location.

First step is to assemble a board and get the display,
RTC, buttons etc working.

