# Broadcast clock

**Digital precision studio/broadcast clock with WiFi configuration, NTP and GPS time sync.**

![Home made broadcast clock](/hardware/gfx/prototype_programming.jpg "Broadcast studio clock")

The enclosure is an 25x25 cm [IKEA "Sannahed"](https://www.ikea.com/us/en/p/sannahed-frame-black-60459118/) photo frame, which is deep enough to contain the circuitry. I replaced the provided plexi glass with a dark acrylic glass plate.

There are no traditional buttons to control the clock. Instead, it has a browser based web configurator. When powered on, the clock will expose a dedicated wifi network for 30 seconds. Connect to the network in order to access the clock's control panel.

The clock supports time synchronization over the web (NTP) or via a range of GNSS satellite systems (GPS/QZSS, GLONASS, BeiDou, Galileo).

LED brightness auto-adjusts to ambient light conditions. This can be overridden in the control panel.
