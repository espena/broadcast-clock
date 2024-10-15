# Broadcast clock

**Digital precision studio/broadcast master clock with WiFi configuration, NTP client/server and GPS time sync.**

![Home made broadcast clock](/hardware/gfx/prototype_programming.jpg "Broadcast studio clock")

## Details

You'll find a complete project description on [my personal home page](https://espenandersen.no/esp32-broadcast-clock/ "Broadcast clock with ESP32 and NTP/GPS time receiver").

The enclosure is an 25x25 cm [IKEA "Sannahed"](https://www.ikea.com/us/en/p/sannahed-frame-black-60459118/) photo frame, which is deep enough to encapsulate the circuitry. I replaced the provided plexi glass with a dark acrylic glass plate.

There are no traditional buttons to control the clock. Instead, it has a browser based web configurator. When powered on, the clock will expose a dedicated wifi network for 30 seconds. Connect to the network in order to access the clock's control panel.

The clock supports time synchronization over the web (NTP) or via a range of GNSS satellite systems (GPS/QZSS, GLONASS, BeiDou, Galileo). It acts as a highly accurate NTP time server for other clocks on your LAN.

LED brightness is auto-adjusted to ambient light conditions. This feature can be overridden in the control panel.

It also has a stopwatch and a countdown timer that is operated from the browser interface.
